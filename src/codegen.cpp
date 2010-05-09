#include "node.h"
#include "codegen.h"
#include "parser/grammar.hpp"
#include "types.h"
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Support/IRBuilder.h>
#include <typeinfo>

typedef nqp::parser::token token;
using namespace std;
using namespace llvm;

namespace nqp {

static IRBuilder<> Builder(getGlobalContext());
static const PointerType *GenericPointerType = Type::getInt8PtrTy(getGlobalContext(), 0);

CodeGenContext::CodeGenContext(LLVMContext &context) : context(context) { 
  module = new Module(StringRef("main"), context);

  vector<const Type*> Args = vector<const Type*>(1, Type::getInt64Ty(getGlobalContext()));
  FunctionType *FT = FunctionType::get(GenericPointerType, Args, false);
  Function::Create(FT, Function::ExternalLinkage, "construct_int", module);

  Args = vector<const Type*>(1, Type::getDoubleTy(getGlobalContext()));
  FT = FunctionType::get(GenericPointerType, Args, false);
  Function::Create(FT, Function::ExternalLinkage, "construct_num", module);

  FT = FunctionType::get(GenericPointerType, false);
  Function::Create(FT, Function::ExternalLinkage, "construct_array", module);

  Args = vector<const Type*>();
  Args.push_back(GenericPointerType);
  Args.push_back(GenericPointerType);
  FT = FunctionType::get(Type::getVoidTy(getGlobalContext()), Args, false);
  Function::Create(FT, Function::ExternalLinkage, "array_push", module);

  Args = vector<const Type*>();
  Args.push_back(Type::getInt8PtrTy(getGlobalContext()));
  Args.push_back(Type::getInt64Ty(getGlobalContext()));
  FT = FunctionType::get(GenericPointerType, Args, false);
  Function::Create(FT, Function::ExternalLinkage, "construct_str", module);

  Args = vector<const Type*>();
  Args.push_back(Type::getInt8PtrTy(getGlobalContext()));
  Args.push_back(Type::getInt64Ty(getGlobalContext()));
  FT = FunctionType::get(GenericPointerType, Args, false);
  Function::Create(FT, Function::ExternalLinkage, "construct_str", module);

  FT = FunctionType::get(GenericPointerType, true);
  Function::Create(FT, Function::ExternalLinkage, "vm_dispatch", module);
}

/* Compile the AST into a module */
void CodeGenContext::generateCode(Block& root)
{
  std::cout << "Generating code...\n";
  std::cout << "Nodes: " << root.statements.size() << "\n";

  /* Create the top level interpreter function to call as entry */
  vector<const Type*> argTypes;
  FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
  mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
  BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);
  
  /* Push a new variable/block context */
  pushBlock(bblock);
  root.codeGen(*this); /* emit bytecode for the toplevel block */
  ReturnInst::Create(getGlobalContext(), bblock);
  popBlock();
  
  /* Print the bytecode in a human-readable format 
     to see if our program compiled properly
   */
  std::cout << "Code is generated.\n";
  PassManager pm;
  pm.add(createPrintModulePass(&outs()));
  pm.run(*module);
}

/* Executes the AST by running the main function */
GenericValue CodeGenContext::runCode() {
  std::cout << "Running code...\n";
  //ExistingModuleProvider *mp = new ExistingModuleProvider(module);
  ExecutionEngine *ee = ExecutionEngine::create(module, false);
  vector<GenericValue> noargs;
  GenericValue v = ee->runFunction(mainFunction, noargs);
  std::cout << "Code was run.\n";
  return v;
}

/* Returns an LLVM type based on the identifier */
static const Type *typeOf(const Identifier& type) 
{
  cout << "typeOf.? " << endl;
  if (type.name.compare("int") == 0) {
    return  Type::getInt64Ty(getGlobalContext());
  }
  else if (type.name.compare("double") == 0) {
    return Type::getDoubleTy(getGlobalContext());
  }
  return Type::getVoidTy(getGlobalContext());
}

/* -- Code Generation -- */

Value* IntegerConstant::codeGen(CodeGenContext& context) {
  std::cout << "Creating integer: " << value << endl;
  Function *construct_int = context.module->getFunction("construct_int");
  if (construct_int == NULL) {
    std::cerr << "Bad construct int" << endl;
  }
  std::vector<Value*> ArgsV;
  ArgsV.push_back(ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value, true));

  return CallInst::Create(construct_int, ArgsV.begin(), ArgsV.end(), "", context.currentBlock());
}

Value* DoubleConstant::codeGen(CodeGenContext& context) {
  std::cout << "Creating double: " << value << endl;
  Function *construct_num = context.module->getFunction("construct_num");
  if (construct_num == NULL) {
    std::cerr << "Bad construct int" << endl;
  }
  std::vector<Value*> ArgsV;
  ArgsV.push_back(ConstantFP::get(Type::getDoubleTy(getGlobalContext()), value));

  return CallInst::Create(construct_num, ArgsV.begin(), ArgsV.end(), "", context.currentBlock());
}

Value* StringConstant::codeGen(CodeGenContext& context) {
  std::cout << "Construing String: " << value << endl;

  Function *construct_str = context.module->getFunction("construct_str");
  if (construct_str == NULL) {
    std::cerr << "Bad construct int" << endl;
  }

  cout << "Value is: " << value << endl;
  
  GlobalVariable *val;
  StringMap<GlobalVariable*>::iterator iter = context.globals.find(value);
  if (iter == context.globals.end()) {
    const ArrayType *str_type = ArrayType::get(Type::getInt8Ty(getGlobalContext()),  value.length() + 1);

    std::vector<Constant *> ary_elements;
    for (unsigned int i = 1; i < value.length() - 1; i++) {
      ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), value[i]));
    }
    ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), 0));

    val = new GlobalVariable(*context.module, str_type, true, GlobalValue::InternalLinkage, ConstantArray::get(str_type, ary_elements), "");

    context.globals[value] = val;
  }
  else {
    val = iter->second;
  }

  std::vector<Value*> ArgsV;
  ArgsV.push_back(val);
  ArgsV.push_back(ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value.length() - 2));

  return CallInst::Create(construct_str, ArgsV.begin(), ArgsV.end(), "", context.currentBlock());
}

Value* Identifier::codeGen(CodeGenContext& context) {
  std::cout << "Creating identifier reference: " << name << endl;
  if (context.locals().find(name) == context.locals().end()) {
    std::cerr << "undeclared variable " << name << endl;
    return NULL;
  }
  return new LoadInst(context.locals()[name], "", false, context.currentBlock());
}

Value* BlockReturn::codeGen(CodeGenContext& context) {
  std::cout << "Creating return instruciton" << endl;

  ReturnInst *ret = ReturnInst::Create(getGlobalContext(), expression.codeGen(context));

  return ret;
}

Value* MethodCall::codeGen(CodeGenContext& context) {
  GlobalVariable *val;
  StringMap<GlobalVariable*>::iterator iter = context.globals.find(id.name);
    if (iter == context.globals.end()) {
    const ArrayType *str_type = ArrayType::get(Type::getInt8Ty(getGlobalContext()),  id.name.length() + 1);

    std::vector<Constant *> ary_elements;
    for (unsigned int i = 0; i < id.name.length(); i++) {
      ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), id.name[i]));
    }
    ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), 0));

    val = new GlobalVariable(*context.module, str_type, true, GlobalValue::InternalLinkage, ConstantArray::get(str_type, ary_elements), "");

    context.globals[id.name] = val;
  }
  else {
    val = iter->second;
  }
  
  Function *function = context.module->getFunction("vm_dispatch");

  std::vector<Value*> args;
  ExpressionList::const_iterator it;

  args.push_back(val);
  args.push_back(ConstantInt::get(Type::getInt64Ty(getGlobalContext()), arguments->size(), true));
  for (it = arguments->begin(); it != arguments->end(); it++) {
    args.push_back((*it)->codeGen(context));
  }
  CallInst *call = CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
  std::cout << "Creating method call: " << id.name << endl;
  return call;
}

Value* PrefixOp::codeGen(CodeGenContext& context) {
  string name;
  switch (op) {
    case token::T_PLUS:
      // Call prefix:<+> 
      name = "&prefix:<+>";
      break;
    case token::T_BAR:
      // Call infix:<|>
      name = "&prefix:<|>";
      break;
    case token::T_STITCH:
      // Call prefix:<~>
      name = "&prefix:<~>";
      break;
    default: { 
      /* not implemented */
      return NULL;
    }
  }

  Function *function = context.module->getFunction("vm_dispatch");

 	const ArrayType *str_type = ArrayType::get(Type::getInt8Ty(getGlobalContext()),  name.length() + 1);

	std::vector<Constant *> ary_elements;
	for (unsigned int i = 0; i < name.length(); i++) {
	  ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), name[i]));
	}
	ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), 0));

  GlobalVariable *method_name = new GlobalVariable(*context.module, str_type, true,
		  GlobalValue::InternalLinkage,
		  ConstantArray::get(str_type, ary_elements), "");

  std::vector<Value*> args;
  args.push_back(method_name);
  args.push_back(ConstantInt::get(Type::getInt64Ty(getGlobalContext()), 1, true));
  args.push_back(val.codeGen(context));

  return CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
}

Value* BinaryOp::codeGen(CodeGenContext& context) {
  std::cout << "Creating infix operation " << op << endl;
  string name;
  switch (op) {
    case token::T_PLUS:
      // Call infix:<+> 
      name = "&infix:<+>";
      break;
    case token::T_MINUS:
      // Call infix:<->
      name = "&infix:<->";
      break;
    case token::T_MUL:
      // Call infix:<*>
      name = "&infix:<*>";
      break;
    case token::T_DIV:
      // Call infix:</>
      name = "&infix:</>";
      break;
    case token::T_STITCH:
      // Call infix:<~>
      name = "&infix:<~>";
      break;
    /* TODO comparison */
    default: { 
      /* not implemented */
      return NULL;
    }
  }

  Function *function = context.module->getFunction("vm_dispatch");

 	const ArrayType *str_type = ArrayType::get(Type::getInt8Ty(getGlobalContext()),  name.length() + 1);

	std::vector<Constant *> ary_elements;
	for (unsigned int i = 0; i < name.length(); i++) {
	  ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), name[i]));
	}
	ary_elements.push_back(ConstantInt::get(Type::getInt8Ty(getGlobalContext()), 0));

  GlobalVariable *val = new GlobalVariable(*context.module, str_type, true,
		GlobalValue::InternalLinkage,
		ConstantArray::get(str_type, ary_elements), "");

  std::vector<Value*> args;
  args.push_back(val);
  args.push_back(ConstantInt::get(Type::getInt64Ty(getGlobalContext()), 2, true));
  args.push_back(lhs.codeGen(context));
  args.push_back(rhs.codeGen(context));

  return CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
}

Value* Assignment::codeGen(CodeGenContext& context) {
  if (context.locals().find(lhs.name) == context.locals().end()) {
    std::cerr << "undeclared variable " << lhs.name << endl;
    return NULL;
  }
  return new StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
}

Value* Block::codeGen(CodeGenContext& context) {
  StatementList::const_iterator it;
  Value *last = NULL;
  // create
  unsigned int count = 0;
  for (it = statements.begin(); it != statements.end(); it++) {
    std::cout << "Generating code for " << typeid(**it).name() << endl;
    last = (**it).codeGen(context);
    count++;
    std::cout << "Generatoring code for " << count << endl;
  }
  std::cout << "Creating block" << endl;
  return last;
}

Value* ExpressionStatement::codeGen(CodeGenContext& context) {
  std::cout << "Generating code for " << typeid(expression).name() << endl;
  return expression.codeGen(context);
}

Value* VariableDeclaration::codeGen(CodeGenContext& context) {
  std::cout << "Creating variable declaration " << id.name << endl;
  AllocaInst *alloc = new AllocaInst(GenericPointerType, id.name.c_str(), context.currentBlock());
  context.locals()[id.name] = alloc;
  if (assignmentExpr != NULL) {
    Assignment assn(id, assignment, *assignmentExpr);
    assn.codeGen(context);
  }
  return alloc; 
}

Value* ListDeclaration::codeGen(CodeGenContext& context) {
  std::cout << "Constructing new Array of length: " << list_values->size() << endl;
  
  Function *function = context.module->getFunction("construct_array");

  Value* new_array = CallInst::Create(function, "", context.currentBlock());

  for (ExpressionList::iterator it = list_values->begin(); it != list_values->end(); ++it) {
    function = context.module->getFunction("array_push");
    
    std::vector<Value*> args;
    args.push_back(new_array);
    args.push_back((*it)->codeGen(context));
    
    CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
  }

  return new_array;
}

Value* ParameterDeclaration::codeGen(CodeGenContext& context) {
  AllocaInst *alloc;
  return alloc;
}

Value* FunctionDeclaration::codeGen(CodeGenContext& context) {
  vector<const Type*> argTypes;
  ParameterList::const_iterator it;
  for (it = arguments.begin(); it != arguments.end(); it++) {
    //argTypes.push_back(typeOf((**it).type));
  }
  FunctionType *ftype = FunctionType::get(Type::getInt64Ty(getGlobalContext()), argTypes, false);
  Function *function = Function::Create(ftype, GlobalValue::InternalLinkage, id.name.c_str(), context.module);
  BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", function, 0);

  context.pushBlock(bblock);

  for (it = arguments.begin(); it != arguments.end(); it++) {
    (**it).codeGen(context);
  }
  
  block.codeGen(context);
  ReturnInst::Create(getGlobalContext(), bblock);

  context.popBlock();
  std::cout << "Creating function: " << id.name << endl;
  return function;
}

Value* IfBlock::codeGen(CodeGenContext& context) {
  return NULL;
}


} /* end namespace nqp */ 

