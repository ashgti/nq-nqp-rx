#ifndef SRC_CODEGEN_H
#define SRC_CODEGEN_H

#include <stack>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/PassManager.h>
#include <llvm/Instructions.h>
#include <llvm/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace nqp {

class NBlock;

class CodeGenBlock {
 public:
  BasicBlock *block;
  std::map<std::string , Value*> locals;
};

class CodeGenContext {
 private:
  std::stack<CodeGenBlock *> blocks;
  Function *mainFunction;
  LLVMContext &context;

 public:
  Module *module;
  CodeGenContext(LLVMContext &context);

  void generateCode(Block& root);
  GenericValue runCode();
  std::map<std::string , Value*>& locals() { return blocks.top()->locals; }
  BasicBlock *currentBlock() { return blocks.top()->block; }
  void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
  void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};

} // end namespace nqp

#endif // SRC_CODEGEN_H
