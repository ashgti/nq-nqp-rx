
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison LALR(1) parsers in C++
   
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

/* C++ LALR(1) parser skeleton written by Akim Demaille.  */

#ifndef PARSER_HEADER_H
# define PARSER_HEADER_H



#include <string>
#include <iostream>
#include "stack.hh"


/* Line 35 of lalr1.cc  */
#line 17 "src/parser/grammar.yy"
namespace nqp {

/* Line 35 of lalr1.cc  */
#line 53 "src/parser/grammar.hpp"
  class position;
  class location;

/* Line 35 of lalr1.cc  */
#line 17 "src/parser/grammar.yy"
} // nqp

/* Line 35 of lalr1.cc  */
#line 62 "src/parser/grammar.hpp"

#include "location.hh"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
do {							\
  if (N)						\
    {							\
      (Current).begin = (Rhs)[1].begin;			\
      (Current).end   = (Rhs)[N].end;			\
    }							\
  else							\
    {							\
      (Current).begin = (Current).end = (Rhs)[0].end;	\
    }							\
} while (false)
#endif


/* Line 35 of lalr1.cc  */
#line 17 "src/parser/grammar.yy"
namespace nqp {

/* Line 35 of lalr1.cc  */
#line 109 "src/parser/grammar.hpp"

  /// A Bison parser.
  class parser
  {
  public:
    /// Symbol semantic values.
#ifndef YYSTYPE
    union semantic_type
    {

/* Line 35 of lalr1.cc  */
#line 24 "src/parser/grammar.yy"

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



/* Line 35 of lalr1.cc  */
#line 137 "src/parser/grammar.hpp"
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

    };
    /// Token type.
    typedef token::yytokentype token_type;

    /// Build a parser object.
    parser (Block * &root_node_yyarg);
    virtual ~parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
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
#endif

  private:
    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Generate an error message.
    /// \param state   the state where the error occurred.
    /// \param tok     the lookahead token.
    virtual std::string yysyntax_error_ (int yystate, int tok);

#if YYDEBUG
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
#endif


    /// State numbers.
    typedef int state_type;
    /// State stack type.
    typedef stack<state_type>    state_stack_type;
    /// Semantic value stack type.
    typedef stack<semantic_type> semantic_stack_type;
    /// location stack type.
    typedef stack<location_type> location_stack_type;

    /// The state stack.
    state_stack_type yystate_stack_;
    /// The semantic value stack.
    semantic_stack_type yysemantic_stack_;
    /// The location stack.
    location_stack_type yylocation_stack_;

    /// Internal symbol numbers.
    typedef unsigned char token_number_type;
    /* Tables.  */
    /// For a state, the index in \a yytable_ of its portion.
    static const short int yypact_[];
    static const signed char yypact_ninf_;

    /// For a state, default rule to reduce.
    /// Unless\a  yytable_ specifies something else to do.
    /// Zero means the default is an error.
    static const unsigned char yydefact_[];

    static const signed char yypgoto_[];
    static const short int yydefgoto_[];

    /// What to do in a state.
    /// \a yytable_[yypact_[s]]: what to do in state \a s.
    /// - if positive, shift that token.
    /// - if negative, reduce the rule which number is the opposite.
    /// - if zero, do what YYDEFACT says.
    static const unsigned char yytable_[];
    static const signed char yytable_ninf_;

    static const short int yycheck_[];

    /// For a state, its accessing symbol.
    static const unsigned char yystos_[];

    /// For a rule, its LHS.
    static const unsigned char yyr1_[];
    /// For a rule, its RHS length.
    static const unsigned char yyr2_[];

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif

#if YYERROR_VERBOSE
    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    virtual std::string yytnamerr_ (const char *n);
#endif

#if YYDEBUG
    /// A type to store symbol numbers and -1.
    typedef short int rhs_number_type;
    /// A `-1'-separated list of the rules' RHS.
    static const rhs_number_type yyrhs_[];
    /// For each rule, the index of the first RHS symbol in \a yyrhs_.
    static const unsigned short int yyprhs_[];
    /// For each rule, its source line number.
    static const unsigned short int yyrline_[];
    /// For each scanner token number, its symbol number.
    static const unsigned short int yytoken_number_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /* Debugging.  */
    int yydebug_;
    std::ostream* yycdebug_;
#endif

    /// Convert a scanner token number \a t to a symbol number.
    token_number_type yytranslate_ (int t);

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg        Why this token is reclaimed.
    /// \param yytype       The symbol type.
    /// \param yyvaluep     Its semantic value.
    /// \param yylocationp  Its location.
    inline void yydestruct_ (const char* yymsg,
			     int yytype,
			     semantic_type* yyvaluep,
			     location_type* yylocationp);

    /// Pop \a n symbols the three stacks.
    inline void yypop_ (unsigned int n = 1);

    /* Constants.  */
    static const int yyeof_;
    /* LAST_ -- Last index in TABLE_.  */
    static const int yylast_;
    static const int yynnts_;
    static const int yyempty_;
    static const int yyfinal_;
    static const int yyterror_;
    static const int yyerrcode_;
    static const int yyntokens_;
    static const unsigned int yyuser_token_number_max_;
    static const token_number_type yyundef_token_;

    /* User arguments.  */
    Block * &root_node;
  };

/* Line 35 of lalr1.cc  */
#line 17 "src/parser/grammar.yy"
} // nqp

/* Line 35 of lalr1.cc  */
#line 407 "src/parser/grammar.hpp"



#endif /* ! defined PARSER_HEADER_H */
