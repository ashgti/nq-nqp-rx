#ifndef NQP_NODE_H_
#define NQP_NODE_H_

#include <iostream>
#include <vector>
#include <llvm/Value.h>

namespace nqp {

class CodeGenContext;
class Statement;
class Expression;
class VariableDeclaration;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Expression*> ExpressionList;
typedef std::vector<VariableDeclaration*> VariableList;

class Node {
 public:
  virtual ~Node() {};
  virtual llvm::Value* codeGen(CodeGenContext& context) = 0;
  virtual std::string str() = 0;

  friend std::ostream& operator<< (std::ostream& o, const Node& b);
};

}

inline std::ostream& operator<<(std::ostream& out, const nqp::Node& node);

namespace nqp {

class Expression : public Node {
};

class Statement : public Node {
};

/* Integer expressions */
class IntegerConstant : public Expression {
 public:
  long long value;
  IntegerConstant(long long value) : value(value) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

/* Floating point number expressions */
class DoubleConstant : public Expression {
 public:
  double value;
  DoubleConstant(double value) : value(value) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

/* Boolean::True and Boolean::False constant values */
class BooleanConstant : public Expression {
};

/* Constant String Expressions */
class StringConstant : public Expression {
 public:
  std::string value;
  StringConstant(const std::string& value) : value(value) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();  
};

class Identifier : public Expression {
 public:
  std::string sigil;
  std::string name;
  Identifier(const std::string& sigil, const std::string& name) : sigil(sigil), name(name) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class MethodCall : public Expression {
 public:
  const Identifier& id;
  ExpressionList arguments;
  MethodCall(const Identifier& id, ExpressionList& arguments) :
      id(id), arguments(arguments) { }
  MethodCall(const Identifier& id) : id(id) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BasicOp : public Expression {
 public:
  Expression& lhs;
  int op;
  Expression& rhs;
  BasicOp(Expression& lhs, int op, Expression& rhs) :
      lhs(lhs), op(op), rhs(rhs) {  }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class Assignment : public Expression {
 public:
  Identifier& lhs;
  unsigned int type;
  Expression& rhs;
  Assignment(Identifier& lhs, unsigned int type, Expression& rhs) :
    lhs(lhs), type(type), rhs(rhs) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class Block : public Expression {
 public:
  StatementList statements;
  Block() { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class ExpressionStatement : public Statement {
 public:
  Expression& expression;
  ExpressionStatement(Expression& expression) :
      expression(expression) { }
  virtual std::string str();
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class BlockReturn : public Statement {
 public:
  Expression& expression;
  BlockReturn(Expression& expression) :
      expression(expression) { }
  virtual std::string str();
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class MuRef : public Identifier {
 public:
  MuRef() : Identifier(0, "Mu") { }
};

class VariableDeclaration : public Statement {
 public:
  Identifier& id;
  int assignment;
  Expression *assignmentExpr;
  VariableDeclaration(Identifier& id) :
      id(id) { }
  VariableDeclaration(Identifier& id, int assignment_token, Expression *expr) :
      id(id), assignment(assignment_token), assignmentExpr(expr) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class FunctionDeclaration : public Statement {
 public:
  // const NIdentifier& type;
  const Identifier& id;
  VariableList arguments;
  Block& block;
  FunctionDeclaration(const Identifier& id, Block& block) :
      id(id), block(block) { }
  FunctionDeclaration(const Identifier& id,
          const VariableList& arguments, Block& block) :
      id(id), arguments(arguments), block(block) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class PackageDeclaration : public Statement {
};

class ClassDeclaration : public PackageDeclaration {
};

} // namespace nqp

#endif // NQP_NODE_H_
