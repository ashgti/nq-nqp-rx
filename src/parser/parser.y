%{

  #include "node.h"
  NBlock *programBlok; /* the top level root node  of our AST */
  
  void yyerror(const char *s) { printf("ERROR: %s\n", s); }
  extern int yylex();
  

%}

%union {
  Node * node;
  NBlock * block;
  std::string * string;
  int token;
}

%token <string> T_ID T_DIGIT
%token <token> T_MY T_SIGIL
%token <token> T_CEQ T_CNE T_EQUAL T_BIND
%token <token> T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_COMMA T_DOT

%type <ident> ident
%type <block> program stmts
%type <stmt> stmt var_decl



%start program

%%

program : stmts { printf("program block starded"); exit(0); }
        ;

stmts : stmt { printf("statements started"); }
      | stmts stmt { printf("satement made of staments"); }
      ;

stmt : var_decl { printf("Var declared"); }
     ;

var_decl : T_MY ident ident { printf("Started declaring a variable"); }
         ;

ident : T_ID { std::cout << "Got identifier " << *$1; delete $1; }
      ;

%%

