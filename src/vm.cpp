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
#include "vm.h"
#include <vector>
#include <iostream>

using namespace std;

namespace nqp {

Stash* NqpVM::top() {
  return this->lex_pad;
}

NqpVM* NqpVM::main_vm = NULL; // new NqpVM;

NqpVM::NqpVM() {
  lex_pad = new Stash; 
}

NqpVM::~NqpVM() {
  cout << "VM Destroyed" << endl;
}

NqpVM* NqpVM::current(void) {
  // Potentially add other VM's for other threads 
  return NqpVM::main_vm;
}

Stash* NqpVM::push() {
  Stash *new_lex = new Stash();
  // cout << "New lexpad: " << new_lex << endl;
  new_lex->OUTER = this->lex_pad;
  this->lex_pad = new_lex;
  return this->lex_pad;
}

void NqpVM::pop() {
  this->lex_pad = this->lex_pad->OUTER;
}

P6opaquePtr NqpVM::dispatch(const char* name, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc);

  P6opaquePtr result = this->vdispatch(name, argc, argv);
  va_end(argv);

  return result;
}

P6opaquePtr NqpVM::dispatch(P6opaque* code, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc);

  P6opaquePtr result = this->vdispatch(code, argc, argv);
  va_end(argv);

  return result;
}

P6opaquePtr NqpVM::vdispatch(const char* name, unsigned int argc, va_list argv) {
  if (name[0] != '&') {
    char* tmp = (char*)malloc(sizeof(char) * strlen(name) + 2); // Memory leak?
    tmp[0] = '&';
    strcpy(tmp+1, name);
    name = tmp;
  }

  P6opaquePtr func_obj = stack_find(this->top(), name);

  return this->vdispatch(func_obj, argc, argv);
}

P6opaque* NqpVM::vdispatch(P6opaque* code, unsigned int argc, va_list argv) {
  P6opaquePtr slurp = NULL;
  mt_entry* method = code->method_table->lookup("postcircumfix:<( )>");

  if (method == NULL) {
    throw "error"; // MethodNotFound Error
  }
  if (method->sig->slurpy == false && argc != method->sig->argc) {
    throw "Bad number of args";
  } 
  else if (method->sig->slurpy == true && argc < method->sig->expected) {
    throw "not enough args";
  }
  
  bool slurpy = false;
  ParameterHolder *slurpy_arg = NULL;

  for (unsigned int i = 0; i < method->sig->argc; ++i) {
    if (method->sig->argv[i].slurpy) {
      slurpy = true;
      slurpy_arg = &method->sig->argv[i];
    }
  }

  Stash* stack = this->push();

  if (slurpy) {
    slurp = construct_array();
  }

  // x used to reference current argument in list of args;
  int x = 0;
  for (unsigned int i = 0; i < argc; ++i) {
    P6opaquePtr param = va_arg(argv, P6opaquePtr);
    if (param) {
      if (method->sig->argv[x].slurpy == true) {
        array_push(slurp, param);
      }
      else {
        stack->values[method->sig->argv[x].name] = param;
        x++; 
      }
    }
  }
  
  if (slurpy) {
    stack->values[slurpy_arg->name] =  slurp;
  }

  P6opaquePtr result = (method->sub)(method->scope);
  this->pop();

  return result;
}


} // end namespace nqp

