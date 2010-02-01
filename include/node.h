// #ifndef NODE_H
// #define NODE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
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

class NExpression : public Node {
};

class NStatement : public Node {
};

class NIdentifier : public NExpression {
  std::string name;
  NIdentifier(const std::string& name) : name(name) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NAssignment : public NExpression {
public:
  NIdentifier& lhs;
  NExpression& rhs;
  NAssignment(NIdentifier& lhs, NExpression& rhs) :
      lhs(lhs), rhs(rhs) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NExpressionStatement : public NStatement {
public:
  NExpression& expression;
  NExpressionStatement(NExpression& expression) :
      expression(expression) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBlock : public Node {
public:
  StatementList statements;
  NBlock() { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NVariableDeclaration : public NStatement {
public:
  const NIdentifier& type;
  NIdentifier& id;
  NExpression *assignmentExpr;
  NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
      type(type), id(id) { }
  NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
      type(type), id(id), assignmentExpr(assignmentExpr) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NFunctionDeclaration : public NStatement {
public:
  const NIdentifier& type;
  const NIdentifier& id;
  VariableList arguments;
  NBlock& block;
  NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id,
    const VariableList& arguments, NBlock& block) :
    type(type), id(id), arguments(arguments), block(block) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};


//  #endif
