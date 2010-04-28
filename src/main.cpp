#include <iostream>
#include <cstdio>
#include "node.h"
#include "codegen.h"
#include "runtime_support.h"
#include "parser/grammar.hpp"
#include <gc/gc_cpp.h>
#include "ast_pass.h"

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

  GC_INIT();
  nqp::Block *root;
  nqp::parser parser(root);
  parser.parse();

  // nqp::TypeInferencePass(root);
  nqp_init();

  std::cerr << "Root:\n\n" << root->str("") << "\n";
  
  nqp::CodeGenContext context(getGlobalContext());
  context.generateCode(*root);
  context.runCode();

  return 0;  
}

