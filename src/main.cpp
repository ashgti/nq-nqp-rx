#include <iostream>
#include <cstdio>
#include "Node.hpp"
#include "Codegen.hpp"
#include "Parser/Grammar.hpp"

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
  nqp::Block *root;
  nqp::parser parser(root);
  parser.parse();

  std::cerr << "Root:\n\n" << root->str("") << "\n";
  
  nqp::CodeGenContext context(getGlobalContext());
  context.generateCode(*root);
  context.runCode();

  return 0;  
}

