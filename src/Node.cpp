#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <Node.hpp>

std::ostream& operator<<(std::ostream& out, nqp::Node& node) {
  out << node.str() << "\n";
  return out;
}

namespace nqp {
using namespace std;

std::string NBlock::str() {
  std::ostringstream os;
  os << "<NBlock #" << this << ">";
  return os.str();
}

void NBlock::print_tree() {
  cout << "Root Nodeblock: " << std::endl;
  NBlock::printSelf();
}

void NBlock::printSelf() {
  cout << NBlock::str() << endl;

  StatementList::iterator it;

  cout << "Contains N Statements: " << (int) statements.size() << endl;
  for (it = statements.begin(); it != statements.end(); ++it) {
    cout << "Statement: " << distance(statements.begin(), it) + 1 << endl;
    cout << (**it).str() << endl;
    //(*it)->printSelf();
  }
}

void NVariableDeclaration::printSelf() {
  cout << "Variable Node: " << this << endl;

  cout << "Id: " << id;
}

std::string NVariableDeclaration::str() {
  std::ostringstream o;
  o << "<NVariableDeclaration #" << this << "> id: " << id;
  return o.str();
}

void NIdentifier::printSelf() {
  cout << "Identifier: " << name; 
  cout << "Sigil: " << sigil;
}

std::string NIdentifier::str() {
  std::ostringstream o;
  o << "<NIdentifier #" << this << ">";
  if (sigil) {
    o << " sigil: " << sigil;
  }
  o << " name: " << name;
  return o.str();
}

} // end namespace nqp

