
%option noyywrap
%{
#include <cstdlib>
#include <string>
#include "node.h"
#include "grammar.tab.hpp"

#define YY_DECL int yylex(yy::parser::semantic_type *yylval, \
  yy::parser::location_type *yylloc)
#define SAVE_TOKEN yylval->string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval->token = t)
#define YY_USER_ACTION yylloc->columns(yyleng);

typedef yy::parser::token token;

%}

%%

%{
     // start where previous token ended
     yylloc->step ();
%}

[ \t\n]     ;
[0-9]+      { SAVE_TOKEN; return token::T_DIGIT; }
";"         return TOKEN(token::T_SEMICOLON);
"{"         return TOKEN(token::T_LBRACE);
"}"         return TOKEN(token::T_RBRACE);
"."         return TOKEN(token::T_DOT);
"("         return TOKEN(token::T_LPAREN);
")"         return TOKEN(token::T_RPAREN);
","         return TOKEN(token::T_COMMA);
"="         return TOKEN(token::T_EQUAL);
":="        return TOKEN(token::T_BIND);
"=="        return TOKEN(token::T_CEQ);
"!="        return TOKEN(token::T_CNE);
"my"        return TOKEN(token::T_MY);

[$@%&]      SAVE_TOKEN; return token::T_SIGIL;
[a-zA-Z]+   { SAVE_TOKEN; return token::T_ID; }
.           { printf("Unknown Token."); }

%%

