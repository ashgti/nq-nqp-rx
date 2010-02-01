#include <stack>
#include <llvm/Value.h>
#include <llvm/Module.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/LLVMContext.h>

using namespace llvm;

class NBlock;

class CodeGenBlock {
public:
    BasicBlock *block;
    std::map<std::string , Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGenBlock *> blocks;
    Function *mainFunction;

public:
    LLVMContext &Context;
    Module *module;
    CodeGenContext();

    void generateCode(NBlock& root);
    GenericValue runCode();
    std::map<std::string , Value*>& locals() { return blocks.top()->locals; }
    BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};

