%{

#include "node.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>

using namespace std;
using namespace nqp;

%}

%defines
%locations
%error-verbose

%define namespace "nqp"

%glr-parser
%expect 6

%parse-param { Block * &root_node }
/*  %lex-param   { NBLock &ctx } */

%union {
  std::string *string;
  unsigned int token;
  Block *block;
  Statement *stmt;
  Expression *expr;
  VariableDeclaration *var_decl;
  ParameterList *param_list;
  ParameterDeclaration *param_var;
  ExpressionList *exprvec;
  Identifier *ident;
}

/* ID of a var, func, class, etc.  */
%token <string> T_ID T_DIGIT T_RBLOCK T_STRINGC

/* variable sigil type */
/* %token <token>  T_TWIGIL T_SCALAR_SIGIL T_LIST_SIGIL T_HASH_SIGIL T_CODE_SIGIL */

%token <string> T_SIGIL T_TWIGIL 

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
/* -> <-> .. ... */
%token <token> T_LAMBDA T_LAMBDA_RW T_RANGE T_ELLIPSES

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
%token <token> T_CN_EQ T_CN_NE T_CN_LT T_CN_GT T_CN_LE T_CN_GE
/* string ops: */
/* eq ne lt le gt ge */
%token <token> T_CS_EQ T_CS_NE T_CS_LT T_CS_GT T_CS_LE T_CS_GE
/* other operatos */
/* ~~ =:= ! ** ^ | // */
%token <token> T_SMARTMATCH T_ID_CMP T_NOT T_REPEATER T_CAROT T_OR_EQ T_BAR
/* math ops */
/* + - * / % */
%token <token> T_PLUS T_MINUS T_MUL T_DIV T_MOD
/* string ops */
/* ~ */
%token <token> T_STITCH
/* regex */
/* ^^ $$ && & || {*} #= */
%token <token> T_REGEX_OPEN T_REGEX_NAME T_REGEX_START T_REGEX_END T_BARBAR T_REGEX_AND T_AND

/* control structure tokens */
%token <token> T_IF T_ELSIF T_ELSE T_UNLESS T_FOR T_WHILE T_RETURN T_MAKE T_GIVEN T_WHEN T_INLINE_IF T_INLINE_ELSE
%token T_LBRACE T_RBRACE T_LPAREN T_RPAREN T_COMMA T_SEMICOLON T_DOT T_RBRACKET T_LBRACKET

%type <block> prog stmts xblock
%type <stmt> stmt var_declarator func_declarator regex_declarator
%type <ident> variable func_ident
%type <param_list> signature param_list
%type <param_var> parameter
%type <var_decl> param_variable named_param
%type <exprvec> args_list
%type <expr> expr_list expr number stringc constants methodop
%type <stmt> stmt_control if_stmt elsif_stmt unless_stmt for_stmt while_stmt
%type <token> comparison assignment infix prefix

/* Operator precedence for mathematical operators */
/*
    NQP::Grammar.O(':prec<y=>, :assoc<unary>', '%methodop');
    NQP::Grammar.O(':prec<x=>, :assoc<unary>', '%autoincrement');
    NQP::Grammar.O(':prec<w=>, :assoc<left>',  '%exponentiation');
    NQP::Grammar.O(':prec<v=>, :assoc<unary>', '%symbolic_unary');
    NQP::Grammar.O(':prec<u=>, :assoc<left>',  '%multiplicative');
    NQP::Grammar.O(':prec<t=>, :assoc<left>',  '%additive');
    NQP::Grammar.O(':prec<r=>, :assoc<left>',  '%concatenation');
    NQP::Grammar.O(':prec<m=>, :assoc<left>',  '%relational');
    NQP::Grammar.O(':prec<l=>, :assoc<left>',  '%tight_and');
    NQP::Grammar.O(':prec<k=>, :assoc<left>',  '%tight_or');
    NQP::Grammar.O(':prec<j=>, :assoc<right>', '%conditional');
    NQP::Grammar.O(':prec<i=>, :assoc<right>', '%assignment');
    NQP::Grammar.O(':prec<g=>, :assoc<list>, :nextterm<nulltermish>',  '%comma');
    NQP::Grammar.O(':prec<f=>, :assoc<list>',  '%list_infix');
    NQP::Grammar.O(':prec<e=>, :assoc<unary>', '%list_prefix');
*/

%nonassoc T_DOT
%right T_EQ T_BIND T_RO_BIND
%left T_PLUS T_MINUS
%left T_MUL T_DIV

%start prog

%{
extern int yylex(nqp::parser::semantic_type* yylval,
       nqp::parser::location_type* yylloc);
%}

%initial-action {
}
%%

prog : stmts { 
        root_node = $1;
      }
     ;

stmts : stmt { 
          $$ = new Block(); $$->statements.push_back($1);
        }
      | stmts stmt { 
          $1->statements.push_back($<stmt>2);
        }
      ;

stmt : var_declarator T_SEMICOLON
     | package_declarator { printf("Packages NYI."); }
     | func_declarator
     | regex_declarator { printf("regex NYI."); }
     | stmt_control
     | T_RETURN expr_list T_SEMICOLON { 
       $$ = new BlockReturn(*$2); 
     }
     | expr_list T_SEMICOLON {
       $$ = new ExpressionStatement(*$1);
     }
     | expr_list { 
       $$ = new BlockReturn(*$1);
       // Last expression, therefor a return-like statement 
     }
     ;

func_ident : T_ID {
             $$ = new Identifier("&", *$1);
             delete $1;
           }
           | '&' T_ID {
             $$ = new Identifier("&", *$2);
             delete $2;
           }
           ;

package_declarator : T_PACKAGE T_ID xblock { } 
                   | T_MODULE T_ID xblock { } 
                   | T_CLASS T_ID xblock { printf("Starting a class\n"); } 
                   | T_GRAMMAR T_ID xblock { } 
                   | T_ROLE T_ID xblock { }
                   ;

func_declarator  : T_SUB func_ident signature xblock { 
                   $$ = new FunctionDeclaration(*$2, *$3, *$4); 
                 }
                 | T_METHOD func_ident signature xblock { printf("method NYI."); }
                 | T_SUBMETHOD func_ident signature xblock { printf("submethod NYI."); }
                 ;

regex_declarator : regex_type_identifier func_ident rblock { printf("Regex needs work... NYI."); }
                 ;

regex_type_identifier : T_TOKEN | T_REGEX | T_RULE 
                      ;

rblock : T_LBRACE '<...>' T_RBRACE { }
       | T_LBRACE T_RBLOCK T_RBRACE { printf("Got a regex block %s\n", $<string>2->c_str()); }
       ;

signature : T_LPAREN param_list T_RPAREN { $$ = $2; }
          ;

param_list : /* blank */ {
             $$ = new ParameterList();
           }
           | parameter {
             $$ = new ParameterList(); 
             $$->push_back($1);
           }
           | param_list T_COMMA parameter {
             $1->push_back($3);
           }
           ;

parameter : param_variable {
            $$ = new ParameterDeclaration(*$1);
          }
          | T_MUL param_variable /* slurpy? */ {
            $$ = new ParameterDeclaration(*$2, false, true, true);
          } 
          | param_variable '?' { 
            $$ = new ParameterDeclaration(*$1, false, true);
          }
          /* | param_var '!' { } not sure if this is needed */
          | named_param {
            $$ = new ParameterDeclaration(*$1, true, true);
          }
          ;

param_variable : variable { 
                 $$ = new VariableDeclaration(*$1); 
               }
               | variable assignment expr {
                 $$ = new VariableDeclaration(*$1, $2, $3);
               }
               ;

named_param : ':' param_variable { $$ = $2; }
            ;


var_declarator  : T_MY variable { 
                    $$ = new VariableDeclaration(*$2); 
                  }
                | T_MY variable assignment expr_list { 
                  $$ = new VariableDeclaration(*$2, $3, $4);
                }
                ;

variable : T_SIGIL T_ID {
           $$ = new Identifier(*$1, *$2); 
           delete $1; 
           delete $2;
         }
         ;

stmt_control : if_stmt
             | unless_stmt
             | for_stmt
             | for_inline_stmt
             | while_stmt
             ;

if_stmt : T_IF expr_list xblock {
          $$ = new IfBlock(*$2, *$3); 
        }
        | T_IF expr_list xblock T_ELSE xblock { }
        | T_IF expr_list xblock elsif_stmt { }
        | T_IF expr_list xblock elsif_stmt T_ELSE xblock { }
        ;

elsif_stmt : T_ELSIF xblock { }
           | elsif_stmt T_ELSIF xblock { }
           ;

unless_stmt : T_UNLESS expr_list xblock { printf("unless NYI."); }

for_stmt : T_FOR expr_list xblock {
         }
         ;

for_inline_stmt : expr_list T_FOR expr_list T_SEMICOLON {
                  /* */
                }
                ;

while_stmt : T_WHILE expr_list xblock {
           }
           ;

methodop : func_ident T_LPAREN args_list T_RPAREN {
           $$ = new MethodCall(*$1, $3);
         }
         | variable T_DOT func_ident T_LPAREN args_list T_RPAREN {
           $$ = new MethodCall($1, *$3, $5);
         }
         | T_ID T_DOT func_ident T_LPAREN args_list T_RPAREN { 
           /* this ones for Class.methods() */ 
         }
         ;

args_list : /* blank args */ {
            $$ = new ExpressionList();
          }
          | expr {
            $$ = new ExpressionList(); $$->push_back($1);
          }
          | args_list T_COMMA expr {
            $1->push_back($3);
          }
          ;

xblock : T_LBRACE T_RBRACE {
         $$ = new Block();
       }
       | T_LBRACE stmts T_RBRACE { 
         $$ = $2;
       }
       ;

expr_list : expr 
          | expr_list T_COMMA expr {
            $1->compound_expr.push_back($3);
          }
          ;

expr : variable assignment expr {
       $$ = new Assignment(*$<ident>1, $2, *$3);
     }
     | variable infix expr {
       $$ = new BinaryOp(*$1, $2, *$3);
     }
     | constants infix expr {
       $$ = new BinaryOp(*$1, $2, *$3);
     }
     | methodop
     | T_RBRACKET args_list T_RBRACKET {
       $$ = new ListDeclaration($2);
     }
     | prefix expr {
       $$ = new PrefixOp($1, *$2);
     }
     | T_LPAREN args_list T_RPAREN {
       $$ = new ListDeclaration($2);
     }
     | constants
     | variable
     ;

p6regex : '/' nibbler '/' {  }
        ;

nibbler : T_STRINGC 
        | '|' T_STRINGC
        ;

number : T_DIGIT { 
         istringstream buffer(*$1);
         long long val;
         buffer >> val;
         $$ = new IntegerConstant(val);
         delete $1;
       }
       | T_DIGIT T_DOT T_DIGIT { }
       ;

constants : number { }
          | stringc { }
          | p6regex 
          ;

infix : comparison { }
      | math_ops { }
      | string_ops { }
      | other_ops { }
      ;

prefix : T_PLUS | T_STITCH | T_BAR
       ;

stringc : T_STRINGC {
          $$ = new StringConstant(*$1);
        }
        ;

assignment : T_EQ
           | T_BIND
           | T_RO_BIND
           ;

other_ops :  T_REPEATER
          ;

math_ops : T_PLUS | T_MINUS | T_MUL | T_DIV
         ;

string_ops : T_STITCH
           ;


comparison : T_CN_EQ | T_CN_NE | T_CN_LT | T_CN_GT | T_CN_LE | T_CN_GE 
           | T_CS_EQ | T_CS_NE | T_CS_LT | T_CS_GT | T_CS_LE | T_CS_GE 
           | T_SMARTMATCH
           ;
%%

namespace nqp {
  void parser::error(location const &loc, const std::string& s) {
    std::cerr << "\n\nerror at " << loc << ": " << s << std::endl;
    exit(-1);
  }
}
