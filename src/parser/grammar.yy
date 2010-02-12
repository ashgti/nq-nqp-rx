%{

#include "node.hpp"
#include <cstdlib>

void
yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}

%}

%defines
%locations
%error-verbose

%define namespace "nqp"

%parse-param { NBlock * &root_node }
/*  %lex-param   { NBLock &ctx } */

%union {
  std::string *string;
  int token;
  NBlock *block;
  NStatement *stmt;
  NVariableDeclaration *var_decl;
  std::vector<NExpression*> *exprvec;
  NIdentifier *ident;
/*    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    NIdentifier *ident;
    NVariableDeclaration *var_decl;
    std::vector<NVariableDeclaration*> *varvec;
    std::vector<NExpression*> *exprvec; */
}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
/*
%token <string> T_ID T_SIGIL T_TWIGIL T_INTEGER T_DOUBLE T_DIGIT
%token <token> T_CEQ T_CNE T_CLT T_CLE T_CGT T_CGE T_EQUAL T_BIND
%token <token> T_MY T_OUR T_HAS
%token <token> T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_COMMA T_DOT T_SEMICOLON
%token <token> T_PLUS T_MINUS T_MUL T_DIV
%token <token> T_SUB T_SUBMETHOD T_METHOD T_MULTI
%token <token> T_RETURN
*/
/* ID of a var, func, class, etc.  */
%token <string> T_ID

/* variable sigil type */
%token <token> T_SIGIL T_SCALAR_SIGIL T_LIST_SIGIL T_HASH_SIGIL T_CODE_SIGIL

/* variable scope identifier my, our, has etc. */
%token <token> T_MY 

/* assignment = := ::= */
%token <token> T_EQ T_BIND T_RO_BIND

/* method identifiers sub, method, submethod, etc. */
%token <token> T_SUB T_SPLAT

/* some default operators */
/* 
  naming schema:
    T means token
    C means comparison
    N means numeric
    S means string
 */
/* = < > <= >= eq */
%token <token> T_C_NEQ T_CLT T_CGT T_CLTE T_CGTE T_CEQL

/* control structure tokens */
%token <token> T_IF T_ELSE T_FOR T_WHILE
%token T_LBRACE T_RBRACE T_LPAREN T_RPAREN T_COMMA 

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */

/*
%type <ident> ident variable
%type <expr> numeric expr assignment
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> prog stmts block
%type <stmt> stmt var_decl func_decl
%type <token> comparison algerbra
*/
%type <block> prog stmts
%type <stmt> stmt var_decl func_decl
%type <ident> variable
/* control structures */
%type <exprvec> args_list
%type <stmt> stmt_control if_stmt unless_stmt for_stmt while_stmt
%type <token> comparison

/* Operator precedence for mathematical operators */
/*
%left T_PLUS T_MINUS
%left T_MUL T_DIV
*/

%start prog

%{
extern int yylex(nqp::parser::semantic_type* yylval,
       nqp::parser::location_type* yylloc);
%}

%initial-action {
 // Filename for locations here
 @$.begin.filename = @$.end.filename = new std::string("stdin");
}
%%

prog : stmts { root_node = $1; }
     ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl { $$ = new NVariableDeclaration(); }
     | func_decl { printf("func_decl NYI."); }
     | stmt_control { printf("stmt_contrl NYI."); }
     | methodop { printf("methodop NYI."); }
     ;

func_ident : T_ID { printf("function ID NYI.") }
           | T_CODE_SIGIL T_ID { printf("func_ident with & NYI."); }
           ;

func_decl : T_SUB func_ident xblock { printf("func_decl NYI."); }
          | T_SUB func_ident signature xblock { printf("func_decl with signature NYI."); }
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


var_decl : T_MY variable {  }
         | T_MY variable '=' expr { }
         | T_MY T_LPAREN args_list T_RPAREN '=' expr { }
         ;

variable : T_SIGIL T_ID { }
         ;

stmt_control : if_stmt { }
             | unless_stmt { }
             | for_stmt { }
             | while_stmt { }
             ;

if_stmt : T_IF expr xblock  {}
        ;

for_stmt : T_FOR expr xblock {}
        /* | expr T_FOR expr {} */
         ;

while_stmt : T_WHILE expr xblock { }
           ;

methodop : variable T_LPAREN args_list T_RPAREN { }
         ;

args_list : /* blank args */ {}
          | expr { }
          | args_list T_COMMA expr { }
          ;

xblock : T_LBRACE stmts T_RBRACE
       ;

expr : variable {}
     | variable comparison variable {}
     | T_LPAREN expr T_RPAREN {}
     ;

comparison : T_CEQ | T_CLT | T_CGT | T_CLTE | T_CLGTE
           ;

%%

namespace nqp {
  void parser::error(location const &loc, const std::string& s) {
    std::cerr << "\n\nerror at " << loc << ": " << s << std::endl;
    exit(-1);
  }
}
