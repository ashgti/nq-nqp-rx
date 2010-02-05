#include <iostream>
#include "node.h"
#include "codegen.h"
#include "grammar.tab.hpp"

using namespace std;

extern int yyparse();
extern FILE *yyin;


int
main(int argc, char **argv) {
  ++argv, --argc;  /* skip over program name */
  if (argc > 0)
    yyin = fopen(argv[0], "r");
  else
    yyin = stdin;

  llvm::InitializeNativeTarget();
  NBlock *root = new NBlock();
  yy::parser parser(*root);
  parser.parse();

  std::cout << root << endl;

  CodeGenContext context;
  context.generateCode(*root);
  context.runCode();

  return 0;  
}
