#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include "Node.hpp"
#include <typeinfo>
#include "Parser/Grammar.hpp"

std::ostream& operator<<(std::ostream& out, nqp::Node& node) {
  out << node.str();
  return out;
}

namespace nqp {

/* Constructors */
IntegerConstant::IntegerConstant(long long value) : value(value) {
}

DoubleConstant::DoubleConstant(double value) : value(value) {
}

StringConstant::StringConstant(const std::string& value) : 
    value(value) {
}

Identifier::Identifier(const std::string& sigil, const std::string& name) : 
    sigil(sigil), name(name) {
}

MethodCall::MethodCall(Identifier& id) : id(id) {
}

MethodCall::MethodCall(Identifier& id, ExpressionList* arguments) :
    id(id), arguments(arguments) { 
  obj = NULL; 
}

MethodCall::MethodCall(Identifier* obj, Identifier& id, ExpressionList* args) :
    obj(obj), id(id), arguments(args) { 
  obj = NULL;
}

BasicOp::BasicOp(Expression& lhs, int op, Expression& rhs) :
    lhs(lhs), op(op), rhs(rhs) {
}

Assignment::Assignment(Identifier& lhs, unsigned int type, Expression& rhs) :
    lhs(lhs), type(type), rhs(rhs) {
}

Block::Block() {
}

ExpressionStatement::ExpressionStatement(Expression& expression) :
    expression(expression) {
}

BlockReturn::BlockReturn(Expression& expression) :
    expression(expression) {
}

IfBlock::IfBlock(Expression& expression, Block& true_block) :
    expression(expression), true_block(true_block) {
}

VariableDeclaration::VariableDeclaration(Identifier& id) :
    id(id) {
}

VariableDeclaration::VariableDeclaration(Identifier& id, 
                                         int assignment_token, 
                                         Expression *expr) :
    id(id), assignment(assignment_token), assignmentExpr(expr) {
}

FunctionDeclaration::FunctionDeclaration(Identifier& id,
                                         ParameterList& arguments, 
                                         Block& block) :
    id(id), arguments(arguments), block(block) {
}

/* str functions */

std::string Block::str() {
  std::ostringstream os;
  os << "<Block #" << this << ">" << std::endl;
  
  StatementList::iterator it;
  for (it = statements.begin(); it != statements.end(); ++it) {
    os << (*it)->str() << "\n";
  }

  return os.str();
}

std::string VariableDeclaration::str() {
  std::ostringstream o;
  o << "<VariableDeclaration #" << this << "> id: " << id.str();

  if (assignmentExpr != NULL) {
    o << "\n\t" << assignmentExpr->str();
  }

  return o.str();
}

std::string ParameterDeclaration::str() {
  std::ostringstream o;
  o << "<ParameterDeclaration #" << this << "> id: "; // << var.id.str();

//  if (var.assignmentExpr != NULL) {
//    o << "\n\t" << var.assignmentExpr->str();
//  }

  return o.str();
}

std::string IntegerConstant::str() {
  std::ostringstream o;
  o << "<IntegerConstant #" << this << "> value: " << value;

  return o.str();
}

std::string DoubleConstant::str() {
  std::ostringstream o;
  o << "<DoubleConstant #" << this << "> value: " << value;

  return o.str();
}

std::string StringConstant::str() {
  std::ostringstream o;
  o << "<StringConstant #" << this << "> value: " << value;

  return o.str();
}

std::string ExpressionStatement::str() {
  std::ostringstream o;
  o << "<ExpressionStatement #" << this << "> Expression:";
  o << "\t" << expression.str() << std::endl;

  return o.str();
}

std::string Identifier::str() {
  std::ostringstream o;
  o << "<Identifier #" << this << " name: " << sigil << name << ">";
  return o.str();
}

std::string BasicOp::str() {
  std::ostringstream o;

  o << "Basic Op: " << this << " lhs: " << lhs.str() << "\n\top: " << op; 
  o << "\n\trhs: " << rhs.str(); 
  return o.str();
}

std::string MethodCall::str() {
  std::ostringstream o;

  o << "MethodCall #" << this << " on " << id.str();
  if (this->obj != NULL) {
    o << "Obj: " << obj->str();
  } 
  if (arguments != NULL) {
    ExpressionList::iterator it; 
    if (arguments->size() > 0) {
      o << "with: " << arguments->size() << " vals: " << std::endl;
      for (it = arguments->begin(); it != arguments->end(); it++) {
        o << (*it)->str() << " ";
      }
    }
  }

  o << std::endl;

  return o.str();
}

std::string Assignment::str() {
  std::ostringstream o;
  o << "<Assignment #" << this << "> " << lhs.str();
  o << "\n\ttype: "; 
  // this is bad but the following values are copied out of the 
  //      T_BIND = 268,
  //      T_RO_BIND = 269,
  if (type == 268) {
    o << ":=";
  } else if (type == 269) {
    o << "::= ";
  }
  o << "\n\texp: " << rhs.str();
  return o.str();
}

std::string FunctionDeclaration::str() {
  std::ostringstream o;

  o << "<FunctionDecl #" << this << "> " << id.str();

  ParameterList::iterator it;

  for (it = arguments.begin(); it != arguments.end(); ++it) {
    o << "arguements: " << (*it)->str();
  }

  o << "\n\tblockx: " << block.str();

  return o.str();
}

std::string BlockReturn::str() {
  return "testing...";
}

std::string IfBlock::str() {
  return "if block\n";
}

} // end namespace nqp

