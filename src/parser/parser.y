%{

  #include "node.h"
  NBlock *programBlok; /* the top level root node  of our AST */

  extern int yylex();
  void yyerror(const char *s) { printf("ERROR: %s\n", s); }

%}

%union {
  Node *node;
}

%token <string> TIDENTIFIER TINTEGER TDOUBLE
%token <token> TMY
%token <token> TCEQ TCNE TEQUAL TBIND
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT

%type <ident> ident
%type <block> program stmts
%type <stmt> stmt var_decl

%start program

%%

program : stmts { printf("program block starded"); }
        ;

stmts : stmt { printf("statements started"); }
      | stmts stmt { printf("satement made of staments"); }
      ;

stmt : var_decl
     ;

var_decl : TMY ident ident { printf("Started declaring a variable"); }
         ;

ident : TIDENTIFIER { printf("Got identifier %s", *$1); delete $1; }
      ;

%%

