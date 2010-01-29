%{

#include <string>
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap() { }

%}

DIGIT [0-9]
SIGIL [$%@&]

%%

{DIGIT}+    { SAVE_TOKEN; printf("Got a digit"); return TDIGIT; }
"my"        return TOKEN(TMY);
"{"         return TOKEN(TLBRACE);
"}"         return TOKEN(TRBRACE);
"."         return TOKEN(TDOT);
"("         return TOKEN(TLPAREN);
")"         return TOKEN(TRPAREN);
","         return TOKEN(TCOMMA);
"="         return TOKEN(TEQUAL);
":="        return TOKEN(TBIND);
"=="        return TOKEN(TCEQ);
"!="        return TOKEN(TCNE);

{SIGIL}     SAVE_TOKEN; return TSIGIL;
[:alpha:][:alnum:] SAVE_TOKEN; return TID;

.           printf("Unknown token!\n"); yyterminate();

%%

main(int argc, char **argv) {
  ++argv, --argc;  /* skip over program name */
  if (argc > 0)
    yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
  yylex();
}
