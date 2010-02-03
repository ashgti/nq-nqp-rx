%{

#include <string>
#include "node.h"
#include "grammar.hpp"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

extern "C" int yywrap() { return 1; }

%}

%%

[ \t\n]     ;
[0-9]+      { SAVE_TOKEN; printf("Got a digit"); return T_DIGIT; }
";"         return TOKEN(T_SEMICOLON);
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

[$@%&]      SAVE_TOKEN; return T_SIGIL;
[\w]+       { SAVE_TOKEN; printf("Got an ID"); return T_ID; }

%%

