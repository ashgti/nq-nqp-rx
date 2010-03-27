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
class ParameterDeclaration;

typedef std::vector<Statement*> StatementList;
typedef std::vector<Expression*> ExpressionList;
typedef std::vector<VariableDeclaration*> VariableList;
typedef std::vector<ParameterDeclaration*> ParameterList;

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
  IntegerConstant(long long value);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

/* Floating point number expressions */
class DoubleConstant : public Expression {
 public:
  double value;
  DoubleConstant(double value);
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
  StringConstant(const std::string& value);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();  
};

class Identifier : public Expression {
 public:
  std::string sigil;
  std::string name;
  Identifier(const std::string& sigil, const std::string& name);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class MethodCall : public Expression {
 public:
  Identifier* obj;
  Identifier& id;
  ExpressionList *arguments;
  MethodCall(Identifier& id);
  MethodCall(Identifier& id, ExpressionList* arguments);
  MethodCall(Identifier* obj, Identifier& id, ExpressionList* args);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class BasicOp : public Expression {
 public:
  Expression& lhs;
  int op;
  Expression& rhs;
  BasicOp(Expression& lhs, int op, Expression& rhs);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class Assignment : public Expression {
 public:
  Identifier& lhs;
  unsigned int type;
  Expression& rhs;
  Assignment(Identifier& lhs, unsigned int type, Expression& rhs);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class Block : public Expression {
 public:
  StatementList statements;
  Block();
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class ExpressionStatement : public Statement {
 public:
  Expression& expression;
  ExpressionStatement(Expression& expression);
  virtual std::string str();
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

class IfBlock : public Statement {
 public:
  Expression& expression;
  Block& true_block;
  IfBlock(Expression& expression, Block& true_block);
  virtual std::string str();
  virtual llvm::Value* codeGen(CodeGenContext& context);
};


class BlockReturn : public Statement {
 public:
  Expression& expression;
  BlockReturn(Expression& expression);
  virtual std::string str();
  virtual llvm::Value* codeGen(CodeGenContext& context);
};

/* 
class MuRef : public Identifier {
 public:
  MuRef() : Identifier(0, "Mu") { }
};
*/

class VariableDeclaration : public Statement {
 public:
  Identifier& id;
  int assignment;
  Expression *assignmentExpr;
  VariableDeclaration(Identifier& id);
  VariableDeclaration(Identifier& id, int assignment_token, Expression *expr);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class ParameterDeclaration : public Statement {
 public:
  VariableDeclaration& var;
  bool optional;
  bool named;
  bool slurpy;
  //ParameterDeclaration(VariableDeclaration& var, bool named, bool optional, bool slurpy) : var(var), named(named), optional(optional), slurpy(slurpy) { }
  virtual llvm::Value* codeGen(CodeGenContext& context);   
  virtual std::string str();
};

class FunctionDeclaration : public Statement {
 public:
  // const NIdentifier& type;
  Identifier& id;
  ParameterList arguments;
  Block& block;
  FunctionDeclaration(Identifier& id, 
                      ParameterList& arguments, 
                      Block& block);
  virtual llvm::Value* codeGen(CodeGenContext& context);
  virtual std::string str();
};

class PackageDeclaration : public Statement {
};

class ClassDeclaration : public PackageDeclaration {
};

} // namespace nqp

#endif // NQP_NODE_H_

