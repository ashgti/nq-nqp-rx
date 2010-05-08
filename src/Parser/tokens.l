%option noyywrap stack
%{
#include <string>
#include "node.h"
#include "parser/grammar.hpp"
#include "stdio.h"

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

%x expect_regex regex comment

%%

%{
     // start where previous token ended
     yylloc->step();
%}

[ \t]             ;
"#"               { BEGIN(comment); }
<comment>{
  [^\n]*          /* ignore comments. */
}
<*>"\n"           { yylloc->lines(); /* keep track of newlines properly */ 
                    BEGIN(INITIAL);
                  }
[0-9]+            { SAVE_TOKEN; return token::T_DIGIT; }
";"               return TOKEN(token::T_SEMICOLON);
"{"               return TOKEN(token::T_LBRACE);
"}"               return TOKEN(token::T_RBRACE);
"."               return TOKEN(token::T_DOT);
"("               return TOKEN(token::T_LPAREN);
")"               return TOKEN(token::T_RPAREN);
"["               return TOKEN(token::T_RBRACKET);
"]"               return TOKEN(token::T_LBRACKET);
","               return TOKEN(token::T_COMMA);
"="               return TOKEN(token::T_EQ);
":="              return TOKEN(token::T_BIND);
"::="             return TOKEN(token::T_RO_BIND);
"+"               return TOKEN(token::T_PLUS);
"*"               return TOKEN(token::T_MUL);
"**"              return TOKEN(token::T_REPEATER);
"/"               return TOKEN(token::T_DIV); 
"%"               return TOKEN(token::T_MOD);
"=:="             return TOKEN(token::T_ID_CMP);
"<"               return TOKEN(token::T_CN_LT);
">"               return TOKEN(token::T_CN_GT);
"<="              return TOKEN(token::T_CN_LE);
">="              return TOKEN(token::T_CN_GE);
"=="              return TOKEN(token::T_CN_EQ);
"!="              return TOKEN(token::T_CN_NE);
"lt"              return TOKEN(token::T_CS_LT);
"gt"              return TOKEN(token::T_CS_GT);
"le"              return TOKEN(token::T_CS_LE);
"ge"              return TOKEN(token::T_CS_GE);
"eq"              return TOKEN(token::T_CS_EQ);
"ne"              return TOKEN(token::T_CS_NE);
"~~"              return TOKEN(token::T_SMARTMATCH);
"~"               return TOKEN(token::T_STITCH);
"|"               return TOKEN(token::T_BAR);
"^"               return TOKEN(token::T_CAROT);
"^^"              return TOKEN(token::T_REGEX_START);
"$$"              return TOKEN(token::T_REGEX_END);
"{*}"             return TOKEN(token::T_REGEX_OPEN);
"&&"              return TOKEN(token::T_REGEX_AND);
"||"              return TOKEN(token::T_BARBAR);
"//"              return TOKEN(token::T_OR_EQ);
"&"               return TOKEN(token::T_AND);
"??"              return TOKEN(token::T_INLINE_IF);
"!!"              return TOKEN(token::T_INLINE_ELSE);

"return"          return TOKEN(token::T_RETURN);
"make"            return TOKEN(token::T_MAKE);

"if"              return TOKEN(token::T_IF);
"elsif"           return TOKEN(token::T_ELSIF);
"else"            return TOKEN(token::T_ELSE);
"unless"          return TOKEN(token::T_UNLESS);
"for"             return TOKEN(token::T_FOR);
"while"           return TOKEN(token::T_WHILE);
"given"           return TOKEN(token::T_GIVEN);
"when"            return TOKEN(token::T_WHEN);

"->"              return TOKEN(token::T_LAMBDA);
"<->"             return TOKEN(token::T_LAMBDA_RW);

"..."             return TOKEN(token::T_ELLIPSES);
".."              return TOKEN(token::T_RANGE);

"my"              return TOKEN(token::T_MY);
"our"             return TOKEN(token::T_OUR);
"has"             return TOKEN(token::T_HAS);

"sub"             return TOKEN(token::T_SUB);
"method"          return TOKEN(token::T_METHOD);
"submethod"       return TOKEN(token::T_SUBMETHOD);

"regex"           return TOKEN(token::T_REGEX);
"token"           { 
  yy_push_state(expect_regex);
  return TOKEN(token::T_TOKEN);
}
<expect_regex>[a-zA-Z_][0-9a-zA-Z_]* {
  SAVE_TOKEN;
  return token::T_ID;
}
<expect_regex>"{" {
  yy_push_state(regex);
  return TOKEN(token::T_LBRACE);
}
<expect_regex>[ \t] { printf("space encountered\n");  }
<expect_regex>.   {  printf("Unknown Token. %s\n", yytext); }
<regex>{
  [^}]*           { SAVE_TOKEN; return token::T_RBLOCK; }
  "}"             {
  yy_pop_state();
  yy_pop_state();
  return TOKEN(token::T_RBRACE);
}
}
"rule"            return TOKEN(token::T_RULE);

"class"           return TOKEN(token::T_CLASS);
"package"         return TOKEN(token::T_PACKAGE);
"grammar"         return TOKEN(token::T_GRAMMAR);
"role"            return TOKEN(token::T_ROLE);
"module"          return TOKEN(token::T_MODULE);

[$@%&]            SAVE_TOKEN; return token::T_SIGIL;
[*\^.]            SAVE_TOKEN; return token::T_TWIGIL;
<*>[a-zA-Z_][0-9a-zA-Z_]* { SAVE_TOKEN; return token::T_ID; }
{STRINGCONSTANT}  { SAVE_TOKEN; return token::T_STRINGC; }
.                 { printf("Unknown Token. %s\n", yytext); }

%%

