#include <iostream>
#include "node.hpp"
#include "codegen.hpp"
#include "parser/grammar.tab.hpp"

using namespace std;
using namespace nqp;

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
  NBlock *root;
  parser parser(root);
  parser.parse();

  CodeGenContext context;
  context.generateCode(*root);
  context.runCode();

  return 0;  
}

