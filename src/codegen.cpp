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

//  Args = vector<const Type*>(1, Type::getInt64Ty(getGlobalContext()));
//  FT = FunctionType::get(GenericPointerType, Args, true);
//  Function::Create(FT, Function::ExternalLinkage, "_say", module);

  FT = FunctionType::get(GenericPointerType, false);
  Function::Create(FT, Function::ExternalLinkage, "vm_stack_push", module);

  FT = FunctionType::get(GenericPointerType, false);
  Function::Create(FT, Function::ExternalLinkage, "vm_stack_pop", module);

  FT = FunctionType::get(GenericPointerType, false);
  Function::Create(FT, Function::ExternalLinkage, "vm_stack_top", module);

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
  if (type.name.compare("int") == 0) {
    return  Type::getInt64Ty(getGlobalContext());
  }
  else if (type.name.compare("double") == 0) {
    return Type::getDoubleTy(getGlobalContext());
  }
  return Type::getVoidTy(getGlobalContext());
}

/* -- Code Generation -- */

Value* IntegerConstant::codeGen(CodeGenContext& context)
{
  std::cout << "Creating integer: " << value << endl;

  // return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value, true);

  Function *construct_int = context.module->getFunction("construct_int");

  if (construct_int == NULL) {
    std::cerr << "Bad construct int" << endl;
  }

  std::vector<Value*> ArgsV;

  ArgsV.push_back(ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value, true));

  cout << "value is: " << value << endl;

  CallInst *call = CallInst::Create(construct_int, ArgsV.begin(), ArgsV.end(), "calltmp", context.currentBlock());  
  // Builder.CreateCall(construct_int, ArgsV.begin(), ArgsV.end(), "calltmp");

  return call;
}

Value* DoubleConstant::codeGen(CodeGenContext& context)
{
  std::cout << "Creating double: " << value << endl;
  return ConstantFP::get(Type::getDoubleTy(getGlobalContext()), value);
}

Value* StringConstant::codeGen(CodeGenContext& context) {
  std::cout << "Not yet Implemented" << endl;
  return NULL;
}

Value* Identifier::codeGen(CodeGenContext& context)
{
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
  /* 
   To call a function do: 

   P6opaque *sub_obj = stack->find(id.name.c_str()); 
   method = sub_obj->method_table->GetOrCreateValue("postcircumfix:<( )>); 

   if (method) {
    switch (method->sub_type) {
      case sub:
        sub_entry->sub(__ARGS__);
        break;
    }
   }
   else {
    thorw error;
   } 
   */

  Function *function = context.module->getFunction(id.name.c_str());
  // Stash stack = Kernel::top();
  // P6opaque *func = stash->find(id.name);
  // Function *function = context.module->getFunction(id.name.c_str());
  //if (function == NULL) {
  //  std::cerr << "no such function " << id.name << endl;
  //}

  //Function *kernel_top = context.module->getFunction("kernel_top");

  //CallInst *call = CallInst::Create(kernel_top, ArgsV.begin(), ArgsV.end(), "", context.currentBlock());

  std::vector<Value*> args;
  ExpressionList::const_iterator it;

  for (it = arguments->begin(); it != arguments->end(); it++) {
    args.push_back((**it).codeGen(context));
  }
  CallInst *call = CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
  std::cout << "Creating method call: " << id.name << endl;
  return call;
}

Value* BasicOp::codeGen(CodeGenContext& context) {
  std::cout << "Creating binary operation " << op << endl;
  Instruction::BinaryOps instr;
  switch (op) {
    case token::T_PLUS:
      instr = Instruction::Add;
      break;
    case token::T_MINUS:
      instr = Instruction::Sub;
      break;
    case token::T_MUL:
      instr = Instruction::Mul;
      break;
    case token::T_DIV:
      instr = Instruction::SDiv;
      break;
    /* TODO comparison */
    default: { 
      /* not implemented */
      return NULL;
    }
  }

  return BinaryOperator::Create(instr, lhs.codeGen(context), 
    rhs.codeGen(context), "", context.currentBlock());
}

Value* Assignment::codeGen(CodeGenContext& context) {
  std::cout << "Creating assignment for " << lhs.name << endl;
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
  AllocaInst *alloc = new AllocaInst(Type::getInt64Ty(getGlobalContext()), id.name.c_str(), context.currentBlock());
  context.locals()[id.name] = alloc;
  if (assignmentExpr != NULL) {
    Assignment assn(id, assignment, *assignmentExpr);
    assn.codeGen(context);
  }
  return alloc; 
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

