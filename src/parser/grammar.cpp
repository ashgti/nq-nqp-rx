
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */

/* Line 311 of lalr1.cc  */
#line 1 "src/parser/grammar.yy"


#include "node.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>

using namespace std;
using namespace nqp;



/* Line 311 of lalr1.cc  */
#line 54 "src/parser/grammar.cpp"


#include "grammar.hpp"

/* User implementation prologue.  */

/* Line 317 of lalr1.cc  */
#line 136 "src/parser/grammar.yy"

extern int yylex(nqp::parser::semantic_type* yylval,
       nqp::parser::location_type* yylloc);


/* Line 317 of lalr1.cc  */
#line 69 "src/parser/grammar.cpp"

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


/* Line 380 of lalr1.cc  */
#line 17 "src/parser/grammar.yy"
namespace nqp {

/* Line 380 of lalr1.cc  */
#line 137 "src/parser/grammar.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  parser::parser (Block * &root_node_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      root_node (root_node_yyarg)
  {
  }

  parser::~parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 553 of lalr1.cc  */
#line 141 "src/parser/grammar.yy"
{
}

/* Line 553 of lalr1.cc  */
#line 319 "src/parser/grammar.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 2:

/* Line 678 of lalr1.cc  */
#line 145 "src/parser/grammar.yy"
    { 
        root_node = (yysemantic_stack_[(1) - (1)].block);
      }
    break;

  case 3:

/* Line 678 of lalr1.cc  */
#line 150 "src/parser/grammar.yy"
    { 
          (yyval.block) = new Block(); (yyval.block)->statements.push_back((yysemantic_stack_[(1) - (1)].stmt));
        }
    break;

  case 4:

/* Line 678 of lalr1.cc  */
#line 153 "src/parser/grammar.yy"
    { 
          (yysemantic_stack_[(2) - (1)].block)->statements.push_back((yysemantic_stack_[(2) - (2)].stmt));
        }
    break;

  case 6:

/* Line 678 of lalr1.cc  */
#line 159 "src/parser/grammar.yy"
    { printf("Packages NYI."); }
    break;

  case 8:

/* Line 678 of lalr1.cc  */
#line 161 "src/parser/grammar.yy"
    { printf("regex NYI."); }
    break;

  case 10:

/* Line 678 of lalr1.cc  */
#line 163 "src/parser/grammar.yy"
    { 
       (yyval.stmt) = new BlockReturn(*(yysemantic_stack_[(3) - (2)].expr)); 
     }
    break;

  case 11:

/* Line 678 of lalr1.cc  */
#line 166 "src/parser/grammar.yy"
    {
       (yyval.stmt) = new ExpressionStatement(*(yysemantic_stack_[(2) - (1)].expr));
     }
    break;

  case 12:

/* Line 678 of lalr1.cc  */
#line 169 "src/parser/grammar.yy"
    { 
       (yyval.stmt) = new BlockReturn(*(yysemantic_stack_[(1) - (1)].expr));
       // Last expression, therefor a return-like statement 
     }
    break;

  case 13:

/* Line 678 of lalr1.cc  */
#line 175 "src/parser/grammar.yy"
    {
             (yyval.ident) = new Identifier("&", *(yysemantic_stack_[(1) - (1)].string));
             delete (yysemantic_stack_[(1) - (1)].string);
           }
    break;

  case 14:

/* Line 678 of lalr1.cc  */
#line 179 "src/parser/grammar.yy"
    {
             (yyval.ident) = new Identifier("&", *(yysemantic_stack_[(2) - (2)].string));
             delete (yysemantic_stack_[(2) - (2)].string);
           }
    break;

  case 15:

/* Line 678 of lalr1.cc  */
#line 185 "src/parser/grammar.yy"
    { }
    break;

  case 16:

/* Line 678 of lalr1.cc  */
#line 186 "src/parser/grammar.yy"
    { }
    break;

  case 17:

/* Line 678 of lalr1.cc  */
#line 187 "src/parser/grammar.yy"
    { printf("Starting a class\n"); }
    break;

  case 18:

/* Line 678 of lalr1.cc  */
#line 188 "src/parser/grammar.yy"
    { }
    break;

  case 19:

/* Line 678 of lalr1.cc  */
#line 189 "src/parser/grammar.yy"
    { }
    break;

  case 20:

/* Line 678 of lalr1.cc  */
#line 192 "src/parser/grammar.yy"
    { 
                   (yyval.stmt) = new FunctionDeclaration(*(yysemantic_stack_[(4) - (2)].ident), *(yysemantic_stack_[(4) - (3)].param_list), *(yysemantic_stack_[(4) - (4)].block)); 
                 }
    break;

  case 21:

/* Line 678 of lalr1.cc  */
#line 195 "src/parser/grammar.yy"
    { printf("method NYI."); }
    break;

  case 22:

/* Line 678 of lalr1.cc  */
#line 196 "src/parser/grammar.yy"
    { printf("submethod NYI."); }
    break;

  case 23:

/* Line 678 of lalr1.cc  */
#line 199 "src/parser/grammar.yy"
    { printf("Regex needs work... NYI."); }
    break;

  case 27:

/* Line 678 of lalr1.cc  */
#line 205 "src/parser/grammar.yy"
    { }
    break;

  case 28:

/* Line 678 of lalr1.cc  */
#line 206 "src/parser/grammar.yy"
    { printf("Got a regex block %s\n", (yysemantic_stack_[(3) - (2)].string)->c_str()); }
    break;

  case 29:

/* Line 678 of lalr1.cc  */
#line 209 "src/parser/grammar.yy"
    { (yyval.param_list) = (yysemantic_stack_[(3) - (2)].param_list); }
    break;

  case 30:

/* Line 678 of lalr1.cc  */
#line 212 "src/parser/grammar.yy"
    {
             (yyval.param_list) = new ParameterList();
           }
    break;

  case 31:

/* Line 678 of lalr1.cc  */
#line 215 "src/parser/grammar.yy"
    {
             (yyval.param_list) = new ParameterList(); 
             (yyval.param_list)->push_back((yysemantic_stack_[(1) - (1)].param_var));
           }
    break;

  case 32:

/* Line 678 of lalr1.cc  */
#line 219 "src/parser/grammar.yy"
    {
             (yysemantic_stack_[(3) - (1)].param_list)->push_back((yysemantic_stack_[(3) - (3)].param_var));
           }
    break;

  case 33:

/* Line 678 of lalr1.cc  */
#line 224 "src/parser/grammar.yy"
    {
            (yyval.param_var) = new ParameterDeclaration(*(yysemantic_stack_[(1) - (1)].var_decl));
          }
    break;

  case 34:

/* Line 678 of lalr1.cc  */
#line 227 "src/parser/grammar.yy"
    {
            (yyval.param_var) = new ParameterDeclaration(*(yysemantic_stack_[(2) - (2)].var_decl), false, true, true);
          }
    break;

  case 35:

/* Line 678 of lalr1.cc  */
#line 230 "src/parser/grammar.yy"
    { 
            (yyval.param_var) = new ParameterDeclaration(*(yysemantic_stack_[(2) - (1)].var_decl), false, true);
          }
    break;

  case 36:

/* Line 678 of lalr1.cc  */
#line 234 "src/parser/grammar.yy"
    {
            (yyval.param_var) = new ParameterDeclaration(*(yysemantic_stack_[(1) - (1)].var_decl), true, true);
          }
    break;

  case 37:

/* Line 678 of lalr1.cc  */
#line 239 "src/parser/grammar.yy"
    { 
                 (yyval.var_decl) = new VariableDeclaration(*(yysemantic_stack_[(1) - (1)].ident)); 
               }
    break;

  case 38:

/* Line 678 of lalr1.cc  */
#line 242 "src/parser/grammar.yy"
    {
                 (yyval.var_decl) = new VariableDeclaration(*(yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (2)].token), (yysemantic_stack_[(3) - (3)].expr));
               }
    break;

  case 39:

/* Line 678 of lalr1.cc  */
#line 247 "src/parser/grammar.yy"
    { (yyval.var_decl) = (yysemantic_stack_[(2) - (2)].var_decl); }
    break;

  case 40:

/* Line 678 of lalr1.cc  */
#line 251 "src/parser/grammar.yy"
    { 
                    (yyval.stmt) = new VariableDeclaration(*(yysemantic_stack_[(2) - (2)].ident)); 
                  }
    break;

  case 41:

/* Line 678 of lalr1.cc  */
#line 254 "src/parser/grammar.yy"
    { 
                  (yyval.stmt) = new VariableDeclaration(*(yysemantic_stack_[(4) - (2)].ident), (yysemantic_stack_[(4) - (3)].token), (yysemantic_stack_[(4) - (4)].expr));
                }
    break;

  case 42:

/* Line 678 of lalr1.cc  */
#line 259 "src/parser/grammar.yy"
    {
           (yyval.ident) = new Identifier(*(yysemantic_stack_[(2) - (1)].string), *(yysemantic_stack_[(2) - (2)].string)); 
           delete (yysemantic_stack_[(2) - (1)].string); 
           delete (yysemantic_stack_[(2) - (2)].string);
         }
    break;

  case 48:

/* Line 678 of lalr1.cc  */
#line 273 "src/parser/grammar.yy"
    {
          (yyval.stmt) = new IfBlock(*(yysemantic_stack_[(3) - (2)].expr), *(yysemantic_stack_[(3) - (3)].block)); 
        }
    break;

  case 49:

/* Line 678 of lalr1.cc  */
#line 276 "src/parser/grammar.yy"
    { }
    break;

  case 50:

/* Line 678 of lalr1.cc  */
#line 277 "src/parser/grammar.yy"
    { }
    break;

  case 51:

/* Line 678 of lalr1.cc  */
#line 278 "src/parser/grammar.yy"
    { }
    break;

  case 52:

/* Line 678 of lalr1.cc  */
#line 281 "src/parser/grammar.yy"
    { }
    break;

  case 53:

/* Line 678 of lalr1.cc  */
#line 282 "src/parser/grammar.yy"
    { }
    break;

  case 54:

/* Line 678 of lalr1.cc  */
#line 285 "src/parser/grammar.yy"
    { printf("unless NYI."); }
    break;

  case 55:

/* Line 678 of lalr1.cc  */
#line 287 "src/parser/grammar.yy"
    {
         }
    break;

  case 56:

/* Line 678 of lalr1.cc  */
#line 291 "src/parser/grammar.yy"
    {
                  /* */
                }
    break;

  case 57:

/* Line 678 of lalr1.cc  */
#line 296 "src/parser/grammar.yy"
    {
           }
    break;

  case 58:

/* Line 678 of lalr1.cc  */
#line 300 "src/parser/grammar.yy"
    {
           (yyval.expr) = new MethodCall(*(yysemantic_stack_[(4) - (1)].ident), (yysemantic_stack_[(4) - (3)].exprvec));
         }
    break;

  case 59:

/* Line 678 of lalr1.cc  */
#line 303 "src/parser/grammar.yy"
    {
           (yyval.expr) = new MethodCall((yysemantic_stack_[(6) - (1)].ident), *(yysemantic_stack_[(6) - (3)].ident), (yysemantic_stack_[(6) - (5)].exprvec));
         }
    break;

  case 60:

/* Line 678 of lalr1.cc  */
#line 306 "src/parser/grammar.yy"
    { 
           /* this ones for Class.methods() */ 
         }
    break;

  case 61:

/* Line 678 of lalr1.cc  */
#line 311 "src/parser/grammar.yy"
    {
            (yyval.exprvec) = new ExpressionList();
          }
    break;

  case 62:

/* Line 678 of lalr1.cc  */
#line 314 "src/parser/grammar.yy"
    {
            (yyval.exprvec) = new ExpressionList(); (yyval.exprvec)->push_back((yysemantic_stack_[(1) - (1)].expr));
          }
    break;

  case 63:

/* Line 678 of lalr1.cc  */
#line 317 "src/parser/grammar.yy"
    {
            (yysemantic_stack_[(3) - (1)].exprvec)->push_back((yysemantic_stack_[(3) - (3)].expr));
          }
    break;

  case 64:

/* Line 678 of lalr1.cc  */
#line 322 "src/parser/grammar.yy"
    {
         (yyval.block) = new Block();
       }
    break;

  case 65:

/* Line 678 of lalr1.cc  */
#line 325 "src/parser/grammar.yy"
    { 
         (yyval.block) = (yysemantic_stack_[(3) - (2)].block);
       }
    break;

  case 67:

/* Line 678 of lalr1.cc  */
#line 331 "src/parser/grammar.yy"
    {
            (yysemantic_stack_[(3) - (1)].expr)->compound_expr.push_back((yysemantic_stack_[(3) - (3)].expr));
          }
    break;

  case 68:

/* Line 678 of lalr1.cc  */
#line 336 "src/parser/grammar.yy"
    {
       (yyval.expr) = new Assignment(*(yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (2)].token), *(yysemantic_stack_[(3) - (3)].expr));
     }
    break;

  case 69:

/* Line 678 of lalr1.cc  */
#line 339 "src/parser/grammar.yy"
    {
       (yyval.expr) = new BasicOp(*(yysemantic_stack_[(3) - (1)].ident), (yysemantic_stack_[(3) - (2)].token), *(yysemantic_stack_[(3) - (3)].expr));
     }
    break;

  case 70:

/* Line 678 of lalr1.cc  */
#line 342 "src/parser/grammar.yy"
    {
       (yyval.expr) = new BasicOp(*(yysemantic_stack_[(3) - (1)].expr), (yysemantic_stack_[(3) - (2)].token), *(yysemantic_stack_[(3) - (3)].expr));
     }
    break;

  case 72:

/* Line 678 of lalr1.cc  */
#line 346 "src/parser/grammar.yy"
    {
     
     }
    break;

  case 75:

/* Line 678 of lalr1.cc  */
#line 353 "src/parser/grammar.yy"
    {  }
    break;

  case 78:

/* Line 678 of lalr1.cc  */
#line 360 "src/parser/grammar.yy"
    { 
         istringstream buffer(*(yysemantic_stack_[(1) - (1)].string));
         long long val;
         buffer >> val;
         (yyval.expr) = new IntegerConstant(val);
         delete (yysemantic_stack_[(1) - (1)].string);
       }
    break;

  case 79:

/* Line 678 of lalr1.cc  */
#line 367 "src/parser/grammar.yy"
    { }
    break;

  case 80:

/* Line 678 of lalr1.cc  */
#line 370 "src/parser/grammar.yy"
    { }
    break;

  case 81:

/* Line 678 of lalr1.cc  */
#line 371 "src/parser/grammar.yy"
    { }
    break;

  case 83:

/* Line 678 of lalr1.cc  */
#line 375 "src/parser/grammar.yy"
    { }
    break;

  case 84:

/* Line 678 of lalr1.cc  */
#line 376 "src/parser/grammar.yy"
    { }
    break;

  case 85:

/* Line 678 of lalr1.cc  */
#line 377 "src/parser/grammar.yy"
    { }
    break;

  case 86:

/* Line 678 of lalr1.cc  */
#line 378 "src/parser/grammar.yy"
    { }
    break;

  case 87:

/* Line 678 of lalr1.cc  */
#line 381 "src/parser/grammar.yy"
    {
          (yyval.expr) = new StringConstant(*(yysemantic_stack_[(1) - (1)].string));
        }
    break;



/* Line 678 of lalr1.cc  */
#line 1002 "src/parser/grammar.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char parser::yypact_ninf_ = -79;
  const short int
  parser::yypact_[] =
  {
       230,   -61,   -58,   -79,    27,    25,    35,    38,    41,    66,
      71,    17,    17,    17,   -79,   -79,   -79,    36,    36,    36,
      36,    36,    36,    72,    21,    76,   230,   -79,    -1,   -79,
     -79,   -79,    17,     0,   290,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -48,   -79,   -79,   -79,   224,   -79,    17,    73,
     -79,    23,     2,     2,     2,     2,     2,   -79,     4,     4,
       4,   -53,   -53,   -53,   -53,   -35,   -32,   -79,   -79,   -79,
      78,    -4,   -79,   -79,    36,     8,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,    17,
      36,    36,   -79,   -79,   -79,   -79,    36,    36,   -79,    36,
       9,   -79,    36,   128,   -79,   -79,   -79,   -79,   -79,    19,
       2,     2,     2,   -16,   -79,   -79,   -79,   -79,   -79,    36,
     -79,   -79,   -28,    26,   -79,    12,   -79,   -79,   -26,   -79,
     -79,    36,    11,   -79,   152,    25,    25,   -23,   -79,     5,
     -79,    23,   -79,   -79,   -79,     2,     2,    -7,   -79,   -79,
      16,    20,    36,   -79,   -19,   -79,   -79,   -79,   -79,    19,
     -79,    36,   -79,   -79,     2,     2,   -79,   -79,   -17,   -79,
     -79,   -79,   -79,   -79,   -79
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  parser::yydefact_[] =
  {
         0,    13,    78,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    24,    26,     0,     0,     0,
       0,     0,    61,     0,     0,     0,     2,     3,     0,     6,
       7,     8,     0,     0,    74,     9,    43,    44,    45,    46,
      47,    71,    12,    66,    82,    80,    73,    81,     0,     0,
      42,    40,     0,     0,     0,     0,     0,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    62,    14,    76,
       0,     0,     1,     4,    61,     0,     5,    88,    89,    90,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    91,    92,    93,    94,    95,    96,     0,
       0,     0,    86,    84,    85,    83,     0,     0,    11,     0,
       0,    79,     0,     0,    15,    16,    17,    18,    19,    30,
       0,     0,     0,    48,    54,    55,    57,    10,    72,     0,
      77,    75,     0,     0,    23,     0,    69,    68,     0,    67,
      70,    61,    41,    64,     0,     0,     0,     0,    31,    33,
      36,    37,    20,    21,    22,     0,     0,    50,    63,    58,
       0,     0,    61,    56,     0,    65,    34,    39,    29,     0,
      35,     0,    52,    49,     0,     0,    28,    27,     0,    60,
      32,    38,    53,    51,    59
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  parser::yypgoto_[] =
  {
       -79,   -79,   -18,   -25,    -3,   -79,   -79,   -79,   -79,   -79,
       6,   -79,   -72,   -78,   -79,   -79,    -5,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -51,   -50,    -2,   -20,   -79,
     -79,   -79,   -79,    53,   -79,   -44,   -79,   -79,   -79,   -79
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const short int
  parser::yydefgoto_[] =
  {
        -1,    25,    26,    27,    28,    29,    30,    31,    32,   134,
     120,   147,   148,   149,   150,    33,    34,    35,    36,   157,
      37,    38,    39,    40,    41,    66,   114,    42,    43,    44,
      71,    45,    46,   100,    47,   101,   102,   103,   104,   105
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char parser::yytable_ninf_ = -1;
  const unsigned char
  parser::yytable_[] =
  {
        51,    73,    67,   115,   116,   117,   118,   112,    58,    59,
      60,   123,   124,   125,   126,    61,    62,    63,    64,    65,
      57,   106,    48,   132,   113,    49,     4,    69,   107,    75,
      50,   160,     4,   107,   108,    77,    78,    79,    52,     1,
       2,    53,     3,     4,    54,   110,   107,   127,   128,   129,
     155,   156,   159,   129,    67,   107,   163,   168,   169,   174,
     175,   179,   129,   184,   129,   121,   122,   166,   167,    55,
     152,   153,   154,   145,    56,    68,    72,   111,    74,   113,
     136,   137,    76,   119,   130,   133,   131,   139,   141,   140,
     164,   162,   107,   170,   176,   144,   135,   180,   177,   109,
       0,     0,     0,    23,   138,   172,   173,   171,   146,   158,
     142,   178,    70,   161,   151,    22,     0,     0,     0,    73,
       0,    67,    23,     0,   182,   183,    24,     0,     0,     0,
       0,     1,     2,     0,     3,     4,     0,     5,     0,     0,
     151,   151,    67,     6,     7,     8,     9,    10,    11,    12,
      13,   181,    14,    15,    16,     1,     2,     0,     3,     4,
       0,     5,     0,     0,   151,     0,     0,     6,     7,     8,
       9,    10,    11,    12,    13,     0,    14,    15,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,    18,    19,    20,    21,
       0,     0,     0,     0,     0,     0,   143,    22,     0,     0,
       0,     0,     0,     0,    23,     0,     0,    17,    24,     0,
      18,    19,    20,    21,     0,     0,     0,     0,     0,     0,
     165,    22,     0,     1,     2,     0,     3,     4,    23,     5,
       0,     0,    24,     0,     0,     6,     7,     8,     9,    10,
      11,    12,    13,     0,    14,    15,    16,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,    93,     0,     0,     0,    94,    95,    96,    97,
       0,    98,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,    18,    19,
      20,    21,    77,    78,    79,     0,     0,     0,     0,    22,
       0,     0,     0,     0,     0,     0,    23,     0,     0,     0,
      24,     0,     0,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     0,     0,    93,     0,
       0,     0,    94,    95,    96,    97,     0,    98,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99
  };

  /* YYCHECK.  */
  const short int
  parser::yycheck_[] =
  {
         5,    26,    22,    53,    54,    55,    56,    51,    11,    12,
      13,    61,    62,    63,    64,    17,    18,    19,    20,    21,
       3,    69,    83,    74,    77,    83,     7,     6,    81,    32,
       3,     5,     7,    81,    82,    12,    13,    14,     3,     3,
       4,     3,     6,     7,     3,    48,    81,    82,    80,    81,
      66,    67,    80,    81,    74,    81,    82,    80,    81,    66,
      67,    80,    81,    80,    81,    59,    60,   145,   146,     3,
     120,   121,   122,    54,     3,     3,     0,     4,    79,    77,
     100,   101,    82,    79,     6,    77,    90,   107,    79,   109,
     141,    79,    81,    88,    78,   113,    99,   169,    78,    46,
      -1,    -1,    -1,    86,   106,   155,   156,   151,    89,   129,
     112,   162,    91,    87,   119,    79,    -1,    -1,    -1,   144,
      -1,   141,    86,    -1,   174,   175,    90,    -1,    -1,    -1,
      -1,     3,     4,    -1,     6,     7,    -1,     9,    -1,    -1,
     145,   146,   162,    15,    16,    17,    18,    19,    20,    21,
      22,   171,    24,    25,    26,     3,     4,    -1,     6,     7,
      -1,     9,    -1,    -1,   169,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,    71,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    65,    90,    -1,
      68,    69,    70,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    79,    -1,     3,     4,    -1,     6,     7,    86,     9,
      -1,    -1,    90,    -1,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    -1,    48,    -1,    -1,    -1,    52,    53,    54,    55,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      70,    71,    12,    13,    14,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,
      90,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    -1,    48,    -1,
      -1,    -1,    52,    53,    54,    55,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  parser::yystos_[] =
  {
         0,     3,     4,     6,     7,     9,    15,    16,    17,    18,
      19,    20,    21,    22,    24,    25,    26,    65,    68,    69,
      70,    71,    79,    86,    90,    93,    94,    95,    96,    97,
      98,    99,   100,   107,   108,   109,   110,   112,   113,   114,
     115,   116,   119,   120,   121,   123,   124,   126,    83,    83,
       3,   108,     3,     3,     3,     3,     3,     3,    96,    96,
      96,   119,   119,   119,   119,   119,   117,   120,     3,     6,
      91,   122,     0,    95,    79,    96,    82,    12,    13,    14,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    48,    52,    53,    54,    55,    57,    83,
     125,   127,   128,   129,   130,   131,    69,    81,    82,   125,
      96,     4,   127,    77,   118,   118,   118,   118,   118,    79,
     102,   102,   102,   118,   118,   118,   118,    82,    80,    81,
       6,    90,   117,    77,   101,    96,   120,   120,   119,   120,
     120,    79,   119,    78,    94,    54,    89,   103,   104,   105,
     106,   108,   118,   118,   118,    66,    67,   111,   120,    80,
       5,    87,    79,    82,   117,    78,   105,   105,    80,    81,
      88,   127,   118,   118,    66,    67,    78,    78,   117,    80,
     104,   120,   118,   118,    80
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,    38,    60,    63,    58,
      47,   124
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  parser::yyr1_[] =
  {
         0,    92,    93,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    97,    97,    97,
      98,    98,    98,    99,   100,   100,   100,   101,   101,   102,
     103,   103,   103,   104,   104,   104,   104,   105,   105,   106,
     107,   107,   108,   109,   109,   109,   109,   109,   110,   110,
     110,   110,   111,   111,   112,   113,   114,   115,   116,   116,
     116,   117,   117,   117,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   121,   122,   122,   123,   123,
     124,   124,   124,   125,   125,   125,   125,   126,   127,   127,
     127,   128,   129,   129,   129,   129,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  parser::yyr2_[] =
  {
         0,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       3,     2,     1,     1,     2,     3,     3,     3,     3,     3,
       4,     4,     4,     3,     1,     1,     1,     3,     3,     3,
       0,     1,     3,     1,     2,     2,     1,     1,     3,     2,
       2,     4,     2,     1,     1,     1,     1,     1,     3,     5,
       4,     6,     2,     3,     3,     3,     4,     3,     4,     6,
       6,     0,     1,     3,     2,     3,     1,     3,     3,     3,
       3,     1,     3,     1,     1,     3,     1,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const parser::yytname_[] =
  {
    "$end", "error", "$undefined", "T_ID", "T_DIGIT", "T_RBLOCK",
  "T_STRINGC", "T_SIGIL", "T_TWIGIL", "T_MY", "T_OUR", "T_HAS", "T_EQ",
  "T_BIND", "T_RO_BIND", "T_PACKAGE", "T_MODULE", "T_CLASS", "T_GRAMMAR",
  "T_ROLE", "T_SUB", "T_METHOD", "T_SUBMETHOD", "T_SPLAT", "T_REGEX",
  "T_TOKEN", "T_RULE", "T_SLASH", "T_BSLASH", "T_LAMBDA", "T_LAMBDA_RW",
  "T_RANGE", "T_ELLIPSES", "T_CN_EQ", "T_CN_NE", "T_CN_LT", "T_CN_GT",
  "T_CN_LE", "T_CN_GE", "T_CS_EQ", "T_CS_NE", "T_CS_LT", "T_CS_GT",
  "T_CS_LE", "T_CS_GE", "T_SMARTMATCH", "T_ID_CMP", "T_NOT", "T_REPEATER",
  "T_CAROT", "T_OR_EQ", "T_BAR", "T_PLUS", "T_MINUS", "T_MUL", "T_DIV",
  "T_MOD", "T_STITCH", "T_REGEX_OPEN", "T_REGEX_NAME", "T_REGEX_START",
  "T_REGEX_END", "T_BARBAR", "T_REGEX_AND", "T_AND", "T_IF", "T_ELSIF",
  "T_ELSE", "T_UNLESS", "T_FOR", "T_WHILE", "T_RETURN", "T_MAKE",
  "T_GIVEN", "T_WHEN", "T_INLINE_IF", "T_INLINE_ELSE", "T_LBRACE",
  "T_RBRACE", "T_LPAREN", "T_RPAREN", "T_COMMA", "T_SEMICOLON", "T_DOT",
  "T_RBRACKET", "T_LBRACKET", "'&'", "'<'", "'?'", "':'", "'/'", "'|'",
  "$accept", "prog", "stmts", "stmt", "func_ident", "package_declarator",
  "func_declarator", "regex_declarator", "regex_type_identifier", "rblock",
  "signature", "param_list", "parameter", "param_variable", "named_param",
  "var_declarator", "variable", "stmt_control", "if_stmt", "elsif_stmt",
  "unless_stmt", "for_stmt", "for_inline_stmt", "while_stmt", "methodop",
  "args_list", "xblock", "expr_list", "expr", "p6regex", "nibbler",
  "number", "constants", "infix", "stringc", "assignment", "other_ops",
  "math_ops", "string_ops", "comparison", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const parser::rhs_number_type
  parser::yyrhs_[] =
  {
        93,     0,    -1,    94,    -1,    95,    -1,    94,    95,    -1,
     107,    82,    -1,    97,    -1,    98,    -1,    99,    -1,   109,
      -1,    71,   119,    82,    -1,   119,    82,    -1,   119,    -1,
       3,    -1,    86,     3,    -1,    15,     3,   118,    -1,    16,
       3,   118,    -1,    17,     3,   118,    -1,    18,     3,   118,
      -1,    19,     3,   118,    -1,    20,    96,   102,   118,    -1,
      21,    96,   102,   118,    -1,    22,    96,   102,   118,    -1,
     100,    96,   101,    -1,    25,    -1,    24,    -1,    26,    -1,
      77,    87,    78,    -1,    77,     5,    78,    -1,    79,   103,
      80,    -1,    -1,   104,    -1,   103,    81,   104,    -1,   105,
      -1,    54,   105,    -1,   105,    88,    -1,   106,    -1,   108,
      -1,   108,   127,   120,    -1,    89,   105,    -1,     9,   108,
      -1,     9,   108,   127,   119,    -1,     7,     3,    -1,   110,
      -1,   112,    -1,   113,    -1,   114,    -1,   115,    -1,    65,
     119,   118,    -1,    65,   119,   118,    67,   118,    -1,    65,
     119,   118,   111,    -1,    65,   119,   118,   111,    67,   118,
      -1,    66,   118,    -1,   111,    66,   118,    -1,    68,   119,
     118,    -1,    69,   119,   118,    -1,   119,    69,   119,    82,
      -1,    70,   119,   118,    -1,    96,    79,   117,    80,    -1,
     108,    83,    96,    79,   117,    80,    -1,     3,    83,    96,
      79,   117,    80,    -1,    -1,   120,    -1,   117,    81,   120,
      -1,    77,    78,    -1,    77,    94,    78,    -1,   120,    -1,
     119,    81,   120,    -1,   108,   127,   120,    -1,   108,   125,
     120,    -1,   124,   125,   120,    -1,   116,    -1,    79,   117,
      80,    -1,   124,    -1,   108,    -1,    90,   122,    90,    -1,
       6,    -1,    91,     6,    -1,     4,    -1,     4,    83,     4,
      -1,   123,    -1,   126,    -1,   121,    -1,   131,    -1,   129,
      -1,   130,    -1,   128,    -1,     6,    -1,    12,    -1,    13,
      -1,    14,    -1,    48,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    57,    -1,    33,    -1,    34,    -1,    35,
      -1,    36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,
      -1,    41,    -1,    42,    -1,    43,    -1,    44,    -1,    45,
      -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  parser::yyprhs_[] =
  {
         0,     0,     3,     5,     7,    10,    13,    15,    17,    19,
      21,    25,    28,    30,    32,    35,    39,    43,    47,    51,
      55,    60,    65,    70,    74,    76,    78,    80,    84,    88,
      92,    93,    95,    99,   101,   104,   107,   109,   111,   115,
     118,   121,   126,   129,   131,   133,   135,   137,   139,   143,
     149,   154,   161,   164,   168,   172,   176,   181,   185,   190,
     197,   204,   205,   207,   211,   214,   218,   220,   224,   228,
     232,   236,   238,   242,   244,   246,   250,   252,   255,   257,
     261,   263,   265,   267,   269,   271,   273,   275,   277,   279,
     281,   283,   285,   287,   289,   291,   293,   295,   297,   299,
     301,   303,   305,   307,   309,   311,   313,   315,   317,   319
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  parser::yyrline_[] =
  {
         0,   145,   145,   150,   153,   158,   159,   160,   161,   162,
     163,   166,   169,   175,   179,   185,   186,   187,   188,   189,
     192,   195,   196,   199,   202,   202,   202,   205,   206,   209,
     212,   215,   219,   224,   227,   230,   234,   239,   242,   247,
     251,   254,   259,   266,   267,   268,   269,   270,   273,   276,
     277,   278,   281,   282,   285,   287,   291,   296,   300,   303,
     306,   311,   314,   317,   322,   325,   330,   331,   336,   339,
     342,   345,   346,   349,   350,   353,   356,   357,   360,   367,
     370,   371,   372,   375,   376,   377,   378,   381,   386,   387,
     388,   391,   394,   394,   394,   394,   397,   401,   401,   401,
     401,   401,   401,   402,   402,   402,   402,   402,   402,   403
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    86,     2,
       2,     2,     2,     2,     2,     2,     2,    90,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    89,     2,
      87,     2,     2,    88,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    91,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int parser::yyeof_ = 0;
  const int parser::yylast_ = 373;
  const int parser::yynnts_ = 40;
  const int parser::yyempty_ = -2;
  const int parser::yyfinal_ = 72;
  const int parser::yyterror_ = 1;
  const int parser::yyerrcode_ = 256;
  const int parser::yyntokens_ = 92;

  const unsigned int parser::yyuser_token_number_max_ = 340;
  const parser::token_number_type parser::yyundef_token_ = 2;


/* Line 1054 of lalr1.cc  */
#line 17 "src/parser/grammar.yy"
} // nqp

/* Line 1054 of lalr1.cc  */
#line 1653 "src/parser/grammar.cpp"


/* Line 1056 of lalr1.cc  */
#line 405 "src/parser/grammar.yy"


namespace nqp {
  void parser::error(location const &loc, const std::string& s) {
    std::cerr << "\n\nerror at " << loc << ": " << s << std::endl;
    exit(-1);
  }
}

