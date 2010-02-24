#include <iostream>
#include <vector>
#include <llvm/Value.h>

namespace nqp {

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NVariableDeclaration*> VariableList;

class Node {
  public:
    virtual ~Node() {};
    virtual llvm::Value* codeGen(CodeGenContext& context) = 0;
};

class NExpression : public Node {
};

class NStatement : public Node {
};

/* Integer expressions */
class NIntegerConstant : public NExpression {
  public:
    long long value;
    NIntegerConstant(long long value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

/* Floating point number expressions */
class NDoubleConstant : public NExpression {
public:
    double value;
    NDoubleConstant(double value) : value(value) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

/* Boolean::True and Boolean::False constant values */
class NBooleanConstant : public NExpression {
};

/* Constant String Expressions */
class NStringConstant : public NExpression {
};

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NMethodCall : public NExpression {
public:
    const NIdentifier& id;
    ExpressionList arguments;
    NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
        id(id), arguments(arguments) { }
    NMethodCall(const NIdentifier& id) : id(id) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBinaryOperator : public NExpression {
public:
    int op;
    NExpression& lhs;
    NExpression& rhs;
    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
        op(op), lhs(lhs), rhs(rhs) {  }
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

class NBlock : public NExpression {
public:
    StatementList statements;
    NBlock() { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NExpressionStatement : public NStatement {
public:
    NExpression& expression;
    NExpressionStatement(NExpression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBlockReturn : public NStatement {
  public:
    NExpression& expression;
    NBlockReturn(NExpression& expression) :
        expression(expression) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class MuRef : public NIdentifier {
 public:
  MuRef() : NIdentifier("Mu") { }
};

class NVariableDeclaration : public NStatement {
public:
    const NIdentifier& type;
    NIdentifier& id;
    NExpression *assignmentExpr;
    NVariableDeclaration(NIdentifier& id) :
        type(MuRef()), id(id) { }
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id) :
        type(type), id(id) { }
    NVariableDeclaration(const NIdentifier& type, NIdentifier& id, NExpression *assignmentExpr) :
        type(type), id(id), assignmentExpr(assignmentExpr) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NFunctionDeclaration : public NStatement {
public:
    // const NIdentifier& type;
    const NIdentifier& id;
    VariableList arguments;
    NBlock& block;
    NFunctionDeclaration(const NIdentifier& id, NBlock& block) :
        id(id), block(block) { }
    NFunctionDeclaration(const NIdentifier& id,
            const VariableList& arguments, NBlock& block) :
        id(id), arguments(arguments), block(block) { }
    virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NPackageDeclaration : public NStatement {
};

class NClassDeclaration : public NPackageDeclaration {
};

} // namespace nqp

