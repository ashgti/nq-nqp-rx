%{

#include "Node.hpp"
#include <cstdlib>

%}

%defines
%locations
%error-verbose

%define namespace "nqp"

%parse-param { NBlock * &root_node }
/*  %lex-param   { NBLock &ctx } */

%union {
  std::string *string;
  unsigned int token;
  NBlock *block;
  NStatement *stmt;
  NVariableDeclaration *var_decl;
  std::vector<NExpression*> *exprvec;
  NIdentifier *ident;
}

/* ID of a var, func, class, etc.  */
%token <string> T_ID T_DIGIT T_RBLOCK T_STRINGC

/* variable sigil type */
%token <token> T_SIGIL T_TWIGIL T_SCALAR_SIGIL T_LIST_SIGIL T_HASH_SIGIL T_CODE_SIGIL

/* variable scope identifier my, our, has */
%token <token> T_MY T_OUR T_HAS

/* assignment = := ::= */
%token <token> T_EQ T_BIND T_RO_BIND

/* package identifiers */
%token <token> T_PACKAGE T_MODULE T_CLASS T_GRAMMAR T_ROLE

/* method identifiers sub, method, submethod, etc. */
%token <token> T_SUB T_METHOD T_SUBMETHOD T_SPLAT

/* Regex related things
/* regex, token, rule */
%token <token> T_REGEX T_TOKEN T_RULE

/* slashes for regex: / \ */
%token <token> T_SLASH T_BSLASH

/* specials */
%token <token> T_LAMBDA T_LAMBDA_RW

/* some default operators */
/* 
  naming schema:
    T means token
    C means comparison
    N means numeric
    S means string
 */
/* numerics: */
/* == != < > <= >= */
%token <token> T_CN_EQ T_CN_NEQ T_CN_LT T_CN_GT T_CN_LTE T_CN_GTE T_CN_EQL
/* string ops: */
/* eq ne lt le gt ge */
%token <token> T_CS_EQ T_CS_NEQ T_CS_LT T_CS_GT T_CS_LTE T_CS_GTE T_CS_EQL
/* other operatos */
/* ~~ === eqv ! ** */
%token <token> T_SMARTMATCH T_TRIPLE_EQ T_EQV T_NOT T_REPEATER
/* math ops */
/* + - * / % */
%token <token> T_PLUS T_MINUS T_MUL T_DIV T_MOD
/* string ops */
/* ~ */
%token <token> T_STITCH

/* control structure tokens */
%token <token> T_IF T_ELSE T_UNLESS T_FOR T_WHILE T_RETURN
%token T_LBRACE T_RBRACE T_LPAREN T_RPAREN T_COMMA T_SEMICOLON T_DOT

%type <block> prog stmts
%type <stmt> stmt var_declarator func_declarator regex_declarator infix
%type <ident> variable
/* control structures */
%type <exprvec> args_list
%type <stmt> stmt_control if_stmt unless_stmt for_stmt while_stmt
%type <token> comparison

/* Operator precedence for mathematical operators */
%left T_PLUS T_MINUS
%left T_MUL T_DIV

%start prog

%{
extern int yylex(nqp::parser::semantic_type* yylval,
       nqp::parser::location_type* yylloc);
%}

%initial-action {
 // Filename for locations here
 // @$.begin.filename = @$.end.filename = new std::string("my file");
}
%%

prog : stmts { root_node = $1; }
     ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_declarator { /* $$ = new NVariableDeclaration(); */ }
     | package_declarator { printf("Packages NYI."); }
     | func_declarator { printf("func_decl NYI."); }
     | regex_declarator { printf("regex NYI."); }
     | stmt_control { printf("stmt_contrl NYI."); }
     | T_RETURN expr { printf("Return statement NYI."); }
     | expr { printf("expression"); }
     | T_SEMICOLON { /* noop */ }
     ;

func_ident : T_ID { printf("function ID NYI.\n"); }
           | T_CODE_SIGIL T_ID { printf("func_ident with & NYI."); }
           ;

package_declarator : T_PACKAGE T_ID xblock { } 
                   | T_MODULE T_ID xblock { } 
                   | T_CLASS T_ID xblock { printf("Starting a class\n"); } 
                   | T_GRAMMAR T_ID xblock { } 
                   | T_ROLE T_ID xblock { }
                   ;

func_declarator  : T_SUB func_ident signature xblock { printf("sub NYI."); }
                 | T_METHOD func_ident signature xblock { printf("method NYI."); }
                 | T_SUBMETHOD func_ident signature xblock { printf("submethod NYI."); }
                 ;

/*
    [
    | $<proto>=[proto] [regex|token|rule]
      <deflongname>
      '{' '<...>' '}'<?ENDSTMT>
    | $<sym>=[regex|token|rule]
      <deflongname>
      <.newpad>
      [ '(' <signature> ')' ]?
      {*} #= open
      '{'<p6regex=.LANG('Regex','nibbler')>'}'<?ENDSTMT>
    ]
*/
regex_declarator : regex_type_identifier func_ident rblock { printf("Regex needs work... NYI."); }
                 ;

regex_type_identifier : T_TOKEN | T_REGEX | T_RULE 
                      ;

rblock : T_LBRACE '<...>' T_RBRACE { }
       | T_LBRACE T_RBLOCK T_RBRACE { }
       ;

signature : T_LPAREN param_list T_RPAREN { printf("signature NYI."); }
          ;

param_list : /* blank */
           | parameter { printf("param_list NYI."); }
           | param_list T_COMMA parameter { printf("param_list NYI."); }
           ;

parameter : param_var { }
          | T_SPLAT param_var /* slurpy? */ { } 
          | param_var '?' { }
          /* | param_var '!' { } not sure if this is needed */
          | named_param { }
          | T_SPLAT named_param { }
          ;

param_var : variable { }
          ;

named_param : ':' param_var { }
            ;


var_declarator  : T_MY variable {  }
                | T_MY variable assignment expr { }
                ;

variable : T_SIGIL T_ID { }
         ;

stmt_control : if_stmt { }
             | unless_stmt { }
             | for_stmt { }
             | while_stmt { }
             ;

if_stmt : T_IF expr xblock  { }
        ;

unless_stmt : T_UNLESS expr xblock { printf("unless NYI."); }

for_stmt : T_FOR expr xblock { }
        /* | expr T_FOR expr {} */
         ;

while_stmt : T_WHILE expr xblock { }
           ;

methodop : func_ident T_LPAREN args_list T_RPAREN { }
         | variable T_DOT func_ident T_LPAREN args_list T_RPAREN { }
         | T_ID T_DOT func_ident T_LPAREN args_list T_RPAREN { /* this ones for Class.methods() */ }
         ;

args_list : /* blank args */ {}
          | expr { }
          | args_list T_COMMA expr { }
          ;

xblock : T_LBRACE T_RBRACE { printf("xblock with no contents\n"); }
       | T_LBRACE stmts T_RBRACE { printf("xblock with contents\n"); }
       ;

expr : variable { }
     | variable infix expr { }
     | number { }
     | number infix expr { }
     | stringc { }
     | methodop { }
     | T_LPAREN expr T_RPAREN {}
     ;

number : T_DIGIT { }
       | T_DIGIT T_DOT T_DIGIT { }
       ;

infix : assignment { }
      | comparison { }
      | math_ops { }
      | string_ops { }
      | other_ops { }
      ;

stringc : T_STRINGC { }
        ;

assignment : T_BIND
           | T_RO_BIND
           ;

other_ops : T_SMARTMATCH | T_TRIPLE_EQ | T_EQV | T_NOT | T_REPEATER
          ;

math_ops : T_PLUS | T_MINUS | T_MUL | T_DIV
         ;

string_ops : T_STITCH
           ;


comparison : T_CN_EQ | T_CN_NEQ | T_CN_LT | T_CN_GT | T_CN_LTE | T_CN_GTE 
           | T_CN_EQL | T_CS_EQ | T_CS_NEQ | T_CS_LT | T_CS_GT | T_CS_LTE 
           | T_CS_GTE | T_CS_EQL
           ;
%%

namespace nqp {
  void parser::error(location const &loc, const std::string& s) {
    std::cerr << "\n\nerror at " << loc << ": " << s << std::endl;
    exit(-1);
  }
}
