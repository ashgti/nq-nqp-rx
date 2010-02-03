%{

#include "node.h"
NBlock *programBlock; /* the top level root node  of our AST */
  
void yyerror(const char *s) { printf("ERROR: %s\n", s);exit(1); }
extern int yylex(YYSTYPE *, yyscan_t);

#define YYPARSE_PARAM scanner
#define YYLEX_PARAM   scanner

%}

%pure-parser

%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NStatement *stmt;
    NIdentifier *ident;
    NVariableDeclaration *var_decl;
    std::vector<NVariableDeclaration*> *varvec;
    std::vector<NExpression*> *exprvec;
    std::string *string;
    int token;

}

/* Define our terminal symbols (tokens). This should
   match our tokens.l lex file. We also define the node type
   they represent.
 */
%token <string> T_ID T_SIGIL T_INTEGER T_DOUBLE T_DIGIT
%token <token> T_CEQ T_CNE T_CLT T_CLE T_CGT T_CGE T_EQUAL T_BIND
%token <token> T_MY T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_COMMA T_DOT T_SEMICOLON
%token <token> T_PLUS T_MINUS T_MUL T_DIV

/* Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */

%type <ident> ident var_ident
%type <expr> numeric expr
%type <varvec> func_decl_args
%type <exprvec> call_args
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl
%type <token> comparison

/* Operator precedence for mathematical operators */
%left TPLUS TMINUS
%left TMUL TDIV

%start program

%%

program : stmts { programBlock = $1; }
        ;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : var_decl | func_decl
     | expr { $$ = new NExpressionStatement(*$1); }
     ;

block : T_LBRACE stmts T_RBRACE { $$ = $2; }
      | T_LBRACE T_RBRACE { $$ = new NBlock(); }
      ;

var_decl : T_MY ident var_ident { printf("hi!"); $$ = new NVariableDeclaration(*$2, *$3); }
         | T_MY ident var_ident T_EQUAL expr { printf("Hi\n"); $$ = new NVariableDeclaration(*$2, *$3, $5); }
         ;

func_decl : ident ident T_LPAREN func_decl_args T_RPAREN block
            { $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
          ;

func_decl_args : /*blank*/  { $$ = new VariableList(); }
          | var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
          | func_decl_args T_COMMA var_decl { $1->push_back($<var_decl>3); }
          ;

var_ident : T_SIGIL T_ID { $$ = new NIdentifier(*$2); delete $2; }
      ;

ident : T_ID { printf("got an id %s\n", "he"); $$ = new NIdentifier(*$1); delete $1; }

numeric : T_INTEGER { $$ = new NInteger(atol($1->c_str())); delete $1; }
        | T_DOUBLE { $$ = new NDouble(atof($1->c_str())); delete $1; }
        ;

expr : ident T_EQUAL expr { $$ = new NAssignment(*$<ident>1, *$3); }
     | ident T_LPAREN call_args T_RPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }
     | ident { $<ident>$ = $1; }
     | numeric
     | expr comparison expr { $$ = new NBinaryOperator(*$1, $2, *$3); }
     | T_LPAREN expr T_RPAREN { $$ = $2; }
     ;

call_args : /*blank*/  { $$ = new ExpressionList(); }
          | expr { $$ = new ExpressionList(); $$->push_back($1); }
          | call_args T_COMMA expr  { $1->push_back($3); }
          ;

comparison : T_CEQ | T_CNE | T_CLT | T_CLE | T_CGT | T_CGE
           | T_PLUS | T_MINUS | T_MUL | T_DIV
           ;

%%

