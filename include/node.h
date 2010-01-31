
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <llvm/Value.h>

class CodeGenContext;
class NStatement;
class NExpression;
class NVaribleDeclration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVaribleDeclration*> VariableList;

class Node {
  public:
    virtual ~Node() = 0;
    virtual llvm::Value* codeGen(CodeGenContext &context) = 0;
};

class NBlock : public Node {

};

#endif
