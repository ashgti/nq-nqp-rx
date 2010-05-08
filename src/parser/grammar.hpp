
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
#line 17 "src/parser/grammar.yy"
namespace nqp {

/* Line 237 of glr.cc  */
#line 54 "src/parser/grammar.hpp"
  class position;
  class location;

/* Line 240 of glr.cc  */
#line 17 "src/parser/grammar.yy"
} // nqp

/* Line 240 of glr.cc  */
#line 63 "src/parser/grammar.hpp"

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
#line 17 "src/parser/grammar.yy"
namespace nqp {

/* Line 268 of glr.cc  */
#line 97 "src/parser/grammar.hpp"
  /// A Bison parser.
  class parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 275 of glr.cc  */
#line 25 "src/parser/grammar.yy"

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



/* Line 275 of glr.cc  */
#line 124 "src/parser/grammar.hpp"
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
     T_MY = 264,
     T_OUR = 265,
     T_HAS = 266,
     T_EQ = 267,
     T_BIND = 268,
     T_RO_BIND = 269,
     T_PACKAGE = 270,
     T_MODULE = 271,
     T_CLASS = 272,
     T_GRAMMAR = 273,
     T_ROLE = 274,
     T_SUB = 275,
     T_METHOD = 276,
     T_SUBMETHOD = 277,
     T_SPLAT = 278,
     T_REGEX = 279,
     T_TOKEN = 280,
     T_RULE = 281,
     T_SLASH = 282,
     T_BSLASH = 283,
     T_LAMBDA = 284,
     T_LAMBDA_RW = 285,
     T_RANGE = 286,
     T_ELLIPSES = 287,
     T_CN_EQ = 288,
     T_CN_NE = 289,
     T_CN_LT = 290,
     T_CN_GT = 291,
     T_CN_LE = 292,
     T_CN_GE = 293,
     T_CS_EQ = 294,
     T_CS_NE = 295,
     T_CS_LT = 296,
     T_CS_GT = 297,
     T_CS_LE = 298,
     T_CS_GE = 299,
     T_SMARTMATCH = 300,
     T_ID_CMP = 301,
     T_NOT = 302,
     T_REPEATER = 303,
     T_CAROT = 304,
     T_OR_EQ = 305,
     T_BAR = 306,
     T_PLUS = 307,
     T_MINUS = 308,
     T_MUL = 309,
     T_DIV = 310,
     T_MOD = 311,
     T_STITCH = 312,
     T_REGEX_OPEN = 313,
     T_REGEX_NAME = 314,
     T_REGEX_START = 315,
     T_REGEX_END = 316,
     T_BARBAR = 317,
     T_REGEX_AND = 318,
     T_AND = 319,
     T_IF = 320,
     T_ELSIF = 321,
     T_ELSE = 322,
     T_UNLESS = 323,
     T_FOR = 324,
     T_WHILE = 325,
     T_RETURN = 326,
     T_MAKE = 327,
     T_GIVEN = 328,
     T_WHEN = 329,
     T_INLINE_IF = 330,
     T_INLINE_ELSE = 331,
     T_LBRACE = 332,
     T_RBRACE = 333,
     T_LPAREN = 334,
     T_RPAREN = 335,
     T_COMMA = 336,
     T_SEMICOLON = 337,
     T_DOT = 338,
     T_RBRACKET = 339,
     T_LBRACKET = 340
   };
#endif

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    parser (Block * &root_node_yyarg);
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
    Block * &root_node;
  };



#ifndef YYSTYPE
# define YYSTYPE nqp::parser::semantic_type
#endif
#ifndef YYLTYPE
# define YYLTYPE nqp::parser::location_type
#endif


/* Line 372 of glr.cc  */
#line 17 "src/parser/grammar.yy"
} // nqp

/* Line 372 of glr.cc  */
#line 312 "src/parser/grammar.hpp"


#endif /* ! defined PARSER_HEADER_H */
