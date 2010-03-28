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

ParameterDeclaration::ParameterDeclaration(VariableDeclaration& var, 
                                           bool named, 
                                           bool optional, 
                                           bool slurpy) :
    var(var), named(named), optional(optional), slurpy(slurpy) {

}


FunctionDeclaration::FunctionDeclaration(Identifier& id,
                                         ParameterList& arguments, 
                                         Block& block) :
    id(id), arguments(arguments), block(block) {
}

/* str functions */

std::string Block::str(std::string prefix) {
  std::ostringstream o;
  o << prefix << "<Block ptr=\"" << this << "\">" << std::endl;
  
  StatementList::iterator it;
  for (it = statements.begin(); it != statements.end(); ++it) {
    o << (*it)->str(prefix + "\t") << "\n";
  }

  o << prefix << "</Block>";

  return o.str();
}

std::string VariableDeclaration::str(std::string prefix) {
  std::ostringstream o;
  o << prefix << "<VariableDeclaration ptr=\"" << this << "\">\n";
  o << id.str(prefix+"\t") << "\n";

  if (assignmentExpr != NULL) {
    o << prefix << "\t<Expr>\n";
    o << prefix << "length: " << assignmentExpr->compound_expr.size() << "\n";
    o << assignmentExpr->str(prefix+"\t\t") << "\n";
    o << prefix << "\t</Expr>\n";
  }

  o << prefix << "</VariableDeclaration>";

  return o.str();
}

std::string ParameterDeclaration::str(std::string prefix) {
  std::ostringstream o;
  o << "<ParameterDeclaration #" << this << "> ";
    
  if (optional) {
    o << "optional = true ";
  }

  if (named) {
    o << "named = true ";
  }

  if (slurpy) {
    o << "slury = true ";
  }

  o << "id: " << var.id.str();

  if (var.assignmentExpr != NULL) {
    o << "\n\t" << var.assignmentExpr->str();
  }

  return o.str();
}

std::string IntegerConstant::str(std::string prefix) {
  std::ostringstream o;
  
  o << prefix << "<IntegerConstant ptr=\"" << this << "\">\n";
  o << prefix << "\t<value>" << value << "</value>\n";
  o << prefix << "</IntegerConstant>";

  return o.str();
}

std::string DoubleConstant::str(std::string prefix) {
  std::ostringstream o;
  o << "<DoubleConstant #" << this << "> value: " << value;

  return o.str();
}

std::string StringConstant::str(std::string prefix) {
  std::ostringstream o;
  o << "<StringConstant #" << this << "> value: " << value;

  return o.str();
}

std::string ExpressionStatement::str(std::string prefix) {
  std::ostringstream o;
  o << prefix << "<ExpressionStatement ptr=\"" << this << "\">\n";
  o << expression.str(prefix + "\t") << "\n";
  o << prefix << "</ExpressionStatement>";

  return o.str();
}

std::string Identifier::str(std::string prefix) {
  std::ostringstream o;
  o << prefix << "<Identifier ptr=\"" << this << "\">\n";
  o << prefix << "\t<name>" << sigil << name << "</name>\n";
  o << prefix << "</Identifier>";
  return o.str();
}

std::string BasicOp::str(std::string prefix) {
  std::ostringstream o;

  o << prefix << "<BasicOp ptr=\"" << this << "\">\n";
  o << prefix << "\t<lhs>\n" << lhs.str(prefix+"\t\t") << "\n" << prefix << "\t</lhs>\n";
  o << prefix << "\t<op>" << op << "</op>\n";
  o << prefix << "\t<rhs>\n" << rhs.str(prefix+"\t\t") << "\n" << prefix << "\t</rhs>\n";
  o << prefix << "</BasicOp>";

  return o.str();
}

std::string MethodCall::str(std::string prefix) {
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

std::string Assignment::str(std::string prefix) {
  std::ostringstream o;
  o << prefix << "<Assignment ptr=\"" << this << "\">\n";
  o << prefix << "\t<lhs>\n";
  o << lhs.str(prefix + "\t\t") << "\n";
  o << prefix << "\t</lhs>\n";
  o << prefix << "\t<type>"; 
  // this is bad but the following values are copied out of the 
  //      T_BIND = 268,
  //      T_RO_BIND = 269,
  switch(type) {
    case 268:
      o << ":=";
      break;
    case 269:
      o << "::=";
      break;
  }
  o << "</type>\n";
  o << prefix << "\t<expr>\n";
  o << rhs.str(prefix + "\t\t") << "\n";
  o << prefix << "\t</expr>\n";
  o << prefix << "</Assignment>";
  return o.str();
}

std::string FunctionDeclaration::str(std::string prefix) {
  std::ostringstream o;

  o << "<FunctionDecl #" << this << "> " << id.str();

  ParameterList::iterator it;

  for (it = arguments.begin(); it != arguments.end(); ++it) {
    o << "arguements: " << (*it)->str();
  }

  o << "\n\tblockx: " << block.str();

  return o.str();
}

std::string BlockReturn::str(std::string prefix) {
  return "testing...";
}

std::string IfBlock::str(std::string prefix) {
  std::ostringstream o;

  o << prefix << "<IfBlock ptr=\"" << this << "\">\n";
  o << prefix << "\t<expr>\n";
  o << expression.str(prefix+"\t\t") << "\n";
  o << prefix << "\t</expr>\n";
  o << prefix << "\t<TrueBlock>\n";
  o << true_block.str(prefix+"\t\t") << "\n";
  o << prefix << "\t</TrueBLock>\n";
  o << prefix << "</IfBlock>";

  return o.str();
}

} // end namespace nqp

