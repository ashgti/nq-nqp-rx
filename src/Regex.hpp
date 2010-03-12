#ifndef NQNQP_REGEX_H_
#define NQNQP_REGEX_H_

#include <string>
// #include "Regex/Match.hpp"

namespace nqp {

namespace Regex {

class Match;

// define character classes
enum R_CCLASS {                         /* ASCII characters matching this class: */
cclass_any = 0xffff,                /* all */
cclass_none = 0x0000,               /* none */
cclass_uppercase = 0x0001,          /* A-Z */
cclass_lowercase = 0x0002,          /* a-z */
cclass_alphabetic = 0x0004,         /* a-z, A-Z */
cclass_numeric = 0x0008,            /* 0-9 */
cclass_hexadecimal = 0x0010,        /* 0-9, a-f, A-F */
cclass_whitespace = 0x0020,         /* ' ', '\f', '\n', '\r', '\t', '\v' */
cclass_printing = 0x0040,           /* any printable character including space */
cclass_graphical = 0x0080,          /* any printable character except space */
cclass_blank = 0x0100,              /* ' ', '\t' */
cclass_control = 0x0200,            /* control characters */
cclass_punctuation = 0x0400,        /* all except ' ', a-z, A-Z, 0-9 */
cclass_alphanumeric = 0x0800,       /* a-z, A-Z, 0-9 */
cclass_newline = 0x1000,            /* '\n', '\r' */
cclass_word = 0x2000                /* a-z, A-Z, 0-9, '_'*/
};

const unsigned int ascii_lookup_table[256] = {
0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, /* 0-7 */
0x0200, 0x0320, 0x1220, 0x0220, 0x1220, 0x1220, 0x0200, 0x0200, /* 8-15 */
0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, /* 16-23 */
0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, 0x0200, /* 24-31 */
0x0160, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, /* 32-39 */
0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, /* 40-47 */
0x28d8, 0x28d8, 0x28d8, 0x28d8, 0x28d8, 0x28d8, 0x28d8, 0x28d8, /* 48-55 */
0x28d8, 0x28d8, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x04c0, /* 56-63 */
0x04c0, 0x28d5, 0x28d5, 0x28d5, 0x28d5, 0x28d5, 0x28d5, 0x28c5, /* 64-71 */
0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, /* 72-79 */
0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, 0x28c5, /* 80-87 */
0x28c5, 0x28c5, 0x28c5, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x24c0, /* 88-95 */
0x04c0, 0x28d6, 0x28d6, 0x28d6, 0x28d6, 0x28d6, 0x28d6, 0x28c6, /* 96-103 */
0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, /* 104-111 */
0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, 0x28c6, /* 112-119 */
0x28c6, 0x28c6, 0x28c6, 0x04c0, 0x04c0, 0x04c0, 0x04c0, 0x0200, /* 120-127 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1020, 0x0000, 0x0000, /* 128-135 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 136-143 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 144-151 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 152-159 */
0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 160-167 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 168-175 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 176-183 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 184-191 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 192-199 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 200-207 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 208-215 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 216-223 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 224-231 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 232-239 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 240-247 */
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, /* 248-255 */
};


/* is_class checks whether a character is of a given type of character class.
 * this only works on ascii characters for now.
 */
unsigned int
is_class(const R_CCLASS cclass, const unsigned char character) {
  return (ascii_lookup_table[character] & cclass) ? 1 : 0;
}

class Cursor {
 public:
  Cursor();
  Cursor(::std::string);

  bool compile(void);

  void MATCH() {
    if (match == NULL) {
      // calculate match object
    }
  }

  Cursor before(Cursor *regex) {
    Cursor cur;
    int pos;
    cursor_start(cur, pos);
    if (regex != NULL) {
      // * not finished. *
    }
    return cur;
  }

  Cursor alpha();
  Cursor upper();
  Cursor lower();
  Cursor digit();
  Cursor xdigit();
  Cursor print();
  Cursor graph();
  Cursor cntrl();
  Cursor punct();
  Cursor alnum();
  Cursor space();
  Cursor blank();
  void FAILGOAL(std::string *goal);
  void DEBUG() { 
    debug = true; 
  }

 protected:
  
 private:
  std::string *target;
  unsigned int from;
  unsigned int pos;
  Regex::Match *match;
  // std::string 
  std::string *src;
  bool debug;
  // backtrack stack: bstack;
  // subcuror stack: cstack;
  // caparray;

  void cursor_start(Cursor &cur, int &pos);
  void cursor_start(Cursor &cur, std::string &tgt, int &pos);
  
  Cursor cclass(const std::string name, R_CCLASS cclass) {
    Cursor cur;
    int pos;
    std::string tgt;
    cursor_start(cur, tgt, pos);
    if (is_class(cclass, tgt[pos])) {
      ++pos;
      cur.cursor_pass(pos, name);
    }
    return cur;
  }

  Cursor protoregex(std::string name) {
    return *this;
  }

  Cursor cursor_pass(unsigned int _pos, std::string name = "") {
    pos = _pos;
    // match = true?
    if (name != "") {
      reduce(name);
    }
    return *this;
  }

  /* reduce(name [, key] [, match]) */
  Cursor reduce(std::string name, std::string key = "", Match *match = NULL) {
    return *this;
  }
}; // end class Cursor

} // end namespace Regex

class Grammar {
 public:
  Grammar();
  ~Grammar();

  void compile();
 private:
  unsigned int states;
  Regex::Cursor cursor;
};

class Actions {
};

class Node {
};

class NExpression : Node {
};

class NVariableDeclaration : NExpression {
};

} // end namespace nqp

#endif // NQNQP_REGEX_H_

