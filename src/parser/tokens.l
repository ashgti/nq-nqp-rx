%option noyywrap
%{
#include <string>
#include "Node.hpp"
#include "parser/grammar.tab.hpp"

#define YY_DECL int yylex(nqp::parser::semantic_type *yylval, \
  nqp::parser::location_type *yylloc)
#define SAVE_TOKEN yylval->string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval->token = t)
#define YY_USER_ACTION yylloc->columns(yyleng);

typedef nqp::parser::token token;

%}

DQ_STRING       \"(\\.|[^"\\\n])*\"
SQ_STRING       \'[^'\n]*\'
STRINGCONSTANT  {DQ_STRING}|{SQ_STRING}
REGEX           \{(\\.|)*\}

%%

%{
     // start where previous token ended
     yylloc->step();
%}

[ \t]     ;
[0-9]+      { SAVE_TOKEN; return token::T_DIGIT; }
";"         return TOKEN(token::T_SEMICOLON);
"{"         return TOKEN(token::T_LBRACE);
"}"         return TOKEN(token::T_RBRACE);
"."         return TOKEN(token::T_DOT);
"("         return TOKEN(token::T_LPAREN);
")"         return TOKEN(token::T_RPAREN);
","         return TOKEN(token::T_COMMA);
"="         return TOKEN(token::T_EQ);
":="        return TOKEN(token::T_BIND);
"=="        return TOKEN(token::T_CN_EQ);
"!="        return TOKEN(token::T_CN_NEQ);
"+"         return TOKEN(token::T_PLUS);

"return"    return TOKEN(token::T_RETURN);

"my"        return TOKEN(token::T_MY);
"our"       return TOKEN(token::T_OUR);
"has"       return TOKEN(token::T_HAS);

"sub"       return TOKEN(token::T_SUB);
"method"    return TOKEN(token::T_METHOD);
"submethod" return TOKEN(token::T_SUBMETHOD);

[$@%&]      SAVE_TOKEN; return token::T_SIGIL;
[*\^.]      SAVE_TOKEN; return token::T_TWIGIL;
[a-zA-Z]+   { SAVE_TOKEN; return token::T_ID; }
{STRINGCONSTANT}  {SAVE_TOKEN; return token:T_STRINGC; }
[^}]*       { SAVE_TOKEN; return token:T_RBLOCK; }
.           { printf("Unknown Token. %s\n", yytext); }

%%

