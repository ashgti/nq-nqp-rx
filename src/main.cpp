#include <iostream>
#include "node.h"
#include "codegen.h"

using namespace std;

extern int yyparse();
extern FILE *yyin;
extern NBlock* programBlock;

int
main(int argc, char **argv) {
  ++argv, --argc;  /* skip over program name */
  if (argc > 0)
    yyin = fopen(argv[0], "r");
  else
    yyin = stdin;

  yyparse();

  std::cout << programBlock << endl;

  CodeGenContext context;
  context.generateCode(*programBlock);
  context.runCode();

  return 0;  
}
