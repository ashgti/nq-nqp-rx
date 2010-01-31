%{

#include <string>
#include "node.h"
#include "parser.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

extern "C" int yywrap() { return 1; }

%}

DIGIT [0-9]
SIGIL [$%@&]

%%

{DIGIT}+    { SAVE_TOKEN; printf("Got a digit"); return T_DIGIT; }
"my"        return TOKEN(T_MY);
"{"         return TOKEN(T_LBRACE);
"}"         return TOKEN(T_RBRACE);
"."         return TOKEN(T_DOT);
"("         return TOKEN(T_LPAREN);
")"         return TOKEN(T_RPAREN);
","         return TOKEN(T_COMMA);
"="         return TOKEN(T_EQUAL);
":="        return TOKEN(T_BIND);
"=="        return TOKEN(T_CEQ);
"!="        return TOKEN(T_CNE);

{SIGIL}     SAVE_TOKEN; return T_SIGIL;
[:alpha:][:alnum:] SAVE_TOKEN; return T_ID;

.           printf("Unknown token!\n"); yyterminate();

%%

