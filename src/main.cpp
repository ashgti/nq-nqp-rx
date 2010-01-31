#include "node.h"
#include "parser.hpp"

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

  printf("Something?\n");
  yyparse();
}
