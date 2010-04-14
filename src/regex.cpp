#include "Regex.hpp" 
#include <iostream>

using namespace std;

namespace nqp {

namespace Regex {

Cursor::Cursor() {
  
}

bool Cursor::compile() {
  // cin.getChar();
  return true;
}

} // end namespace nqp::Regex

// nqp::Grammar
Grammar::Grammar() {
  cout << "Reading Grammar... \n";
}

void Grammar::compile() {
  while (!cin.eof()) {
    string ;
    cin >> stuff;
    if (stuff != "") {
      cout << "Got something " << endl;
    }
  }
}

} // end namespace nqp

int main(int argc, char **argv) {
  try {
    nqp::Grammar *parser = new nqp::Grammar();
    parser->compile();
  }
  catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << '\n';
    return -1;
  }
  catch (...) {
    std::cerr << "\n*** UNEXPECTED ERROR ***\n";
    return -1;
  }
  return 1;  
}
