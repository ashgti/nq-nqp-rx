/*
 * =====================================================================================
 *
 *       Filename:  vm.cpp
 *
 *    Description:  The actual VM that is going to sit on top of the llvm.
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */
#include "types.h"
#include <vector>

using namespace std;

namespace nqp {

Stash::Stash() {
}

P6opaque* Stash::find(string name) {
  StringMap<P6opaque*>::iterator it = values.find(name);
  if (it == values.end()) {
    if (OUTER == NULL) {
      throw "Error Value not found";
    }
    else {
      return OUTER->find(name);
    }
  }
  else {
    return it->second;
  }
}

Stash* NqpVM::top() {
  return this->lex_pad;
}

NqpVM* NqpVM::main = NULL;

inline
NqpVM* NqpVM::current(void) {
  // Potentially add other VM's for other threads 
  return NqpVM::main;
}

Stash* NqpVM::push() {
  Stash *new_lex = new Stash();
  new_lex->OUTER = this->lex_pad;
  this->lex_pad = new_lex;
  return this->lex_pad;
}

void NqpVM::pop() {
  this->lex_pad = this->lex_pad->OUTER;
}


} // end namespace nqp

