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
#include "runtime_support.h"
#include <vector>
#include <iostream>

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

NqpVM* NqpVM::main_vm = NULL; // new NqpVM;

NqpVM::NqpVM() {
  lex_pad = new Stash; lex_pad->OUTER = lex_pad; 
}

NqpVM::~NqpVM() {
  cout << "hi?" << endl;
}


NqpVM* NqpVM::current(void) {
  // Potentially add other VM's for other threads 
  return NqpVM::main_vm;
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

P6opaque* NqpVM::dispatch(const char* name, int argc, ...) {
  P6opaque* func_obj = this->top()->find(name);
  cout << "func: " << func_obj << endl;
  mt_entry* method = func_obj->method_table->lookup("postcircumfix:<( )>");
  std::cout << "method found! " << method->argc << std::endl;
  Stash* stack = this->push();
  stack->values["a"] = construct_int(4);
  stack->values["b"] = construct_int(3);
  (method->sub)(method->scope);
  this->pop();
}

P6opaque* NqpVM::dispatch(P6opaque* code, int argc, ...) {
  mt_entry* method = code->method_table->lookup("postcircumfix:<( )>");
  std::cout << "method found! " << method->argc << std::endl;
  Stash* stack = this->push();
  stack->values["a"] = construct_int(4);
  stack->values["b"] = construct_int(3);
  (method->sub)(method->scope);
  this->pop();
}



} // end namespace nqp

