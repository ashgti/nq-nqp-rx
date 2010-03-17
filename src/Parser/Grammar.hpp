
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison GLR parsers in C++
   
      Copyright (C) 2002, 2003, 2004, 2005, 2006 Free Software Foundation, Inc.
   
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

/* C++ GLR parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H



#include <string>
#include <iostream>

/* Using locations.  */
#define YYLSP_NEEDED 1


/* Line 237 of glr.cc  */
#line 16 "src/Parser/Grammar.yy"
namespace nqp {

/* Line 237 of glr.cc  */
#line 54 "src/Parser/Grammar.hpp"
  class position;
  class location;

/* Line 240 of glr.cc  */
#line 16 "src/Parser/Grammar.yy"
} // nqp

/* Line 240 of glr.cc  */
#line 63 "src/Parser/Grammar.hpp"

#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).begin  = YYRHSLOC (Rhs, 1).begin;			\
	  (Current).end    = YYRHSLOC (Rhs, N).end;			\
	}								\
      else								\
	{								\
	  (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;	\
	}								\
    while (/*CONSTCOND*/ 0)
#endif


/* Line 268 of glr.cc  */
#line 16 "src/Parser/Grammar.yy"
namespace nqp {

/* Line 268 of glr.cc  */
#line 97 "src/Parser/Grammar.hpp"
  /// A Bison parser.
  class parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 275 of glr.cc  */
#line 21 "src/Parser/Grammar.yy"

  std::string *string;
  unsigned int token;
  NBlock *block;
  NStatement *stmt;
  NExpression *expr;
  NVariableDeclaration *var_decl;
  ExpressionList *exprvec;
  NIdentifier *ident;



/* Line 275 of glr.cc  */
#line 122 "src/Parser/Grammar.hpp"
    };
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;
    /// Tokens.
    struct token
    {
      /* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_ID = 258,
     T_DIGIT = 259,
     T_RBLOCK = 260,
     T_STRINGC = 261,
     T_SIGIL = 262,
     T_TWIGIL = 263,
     T_SCALAR_SIGIL = 264,
     T_LIST_SIGIL = 265,
     T_HASH_SIGIL = 266,
     T_CODE_SIGIL = 267,
     T_MY = 268,
     T_OUR = 269,
     T_HAS = 270,
     T_EQ = 271,
     T_BIND = 272,
     T_RO_BIND = 273,
     T_PACKAGE = 274,
     T_MODULE = 275,
     T_CLASS = 276,
     T_GRAMMAR = 277,
     T_ROLE = 278,
     T_SUB = 279,
     T_METHOD = 280,
     T_SUBMETHOD = 281,
     T_SPLAT = 282,
     T_REGEX = 283,
     T_TOKEN = 284,
     T_RULE = 285,
     T_SLASH = 286,
     T_BSLASH = 287,
     T_LAMBDA = 288,
     T_LAMBDA_RW = 289,
     T_RANGE = 290,
     T_CN_EQ = 291,
     T_CN_NEQ = 292,
     T_CN_LT = 293,
     T_CN_GT = 294,
     T_CN_LTE = 295,
     T_CN_GTE = 296,
     T_CN_EQL = 297,
     T_CS_EQ = 298,
     T_CS_NEQ = 299,
     T_CS_LT = 300,
     T_CS_GT = 301,
     T_CS_LTE = 302,
     T_CS_GTE = 303,
     T_CS_EQL = 304,
     T_SMARTMATCH = 305,
     T_TRIPLE_EQ = 306,
     T_EQV = 307,
     T_NOT = 308,
     T_REPEATER = 309,
     T_PLUS = 310,
     T_MINUS = 311,
     T_MUL = 312,
     T_DIV = 313,
     T_MOD = 314,
     T_STITCH = 315,
     T_IF = 316,
     T_ELSE = 317,
     T_UNLESS = 318,
     T_FOR = 319,
     T_WHILE = 320,
     T_RETURN = 321,
     T_LBRACE = 322,
     T_RBRACE = 323,
     T_LPAREN = 324,
     T_RPAREN = 325,
     T_COMMA = 326,
     T_SEMICOLON = 327,
     T_DOT = 328
   };
#endif

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    parser (NBlock * &root_node_yyarg);
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

    /// The current debugging stream.
    std::ostream& debug_stream () const;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);

  private:

  public:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);
  private:

#if YYDEBUG
  public:
    /// \brief Report a symbol value on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_value_print_ (int yytype,
					 const semantic_type* yyvaluep,
					 const location_type* yylocationp);
    /// \brief Report a symbol on the debug stream.
    /// \param yytype       The token type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    virtual void yy_symbol_print_ (int yytype,
				   const semantic_type* yyvaluep,
				   const location_type* yylocationp);
  private:
    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif


    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);


    /* User arguments.  */
    NBlock * &root_node;
  };



#ifndef YYSTYPE
# define YYSTYPE nqp::parser::semantic_type
#endif
#ifndef YYLTYPE
# define YYLTYPE nqp::parser::location_type
#endif


/* Line 372 of glr.cc  */
#line 16 "src/Parser/Grammar.yy"
} // nqp

/* Line 372 of glr.cc  */
#line 298 "src/Parser/Grammar.hpp"


#endif /* ! defined PARSER_HEADER_H */
