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
  return "function Decl";
}

std::string BlockReturn::str() {
  return "testing...";
}

} // end namespace nqp

