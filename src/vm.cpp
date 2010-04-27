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
  lex_pad = new Stash; 
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

P6opaque* NqpVM::dispatch(const char* name, unsigned int argc, ...) {
  P6opaquePtr slurp = NULL;
  P6opaque* func_obj = this->top()->find(name);
  // cout << "func: " << func_obj << " argc: " << argc << endl;
  mt_entry* method = func_obj->method_table->lookup("postcircumfix:<( )>");
  if (method == NULL) {
    throw "error"; // MethodNotFound Error
  }
  if (method->sig->slurpy == false && argc != method->sig->argc) {
    throw "Bad number of args";
  } else if (method->sig->slurpy == true && argc < method->sig->expected) {
    throw "not enough args";
  }
  
  va_list argv;
  va_start(argv, argc);

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

  va_end(argv);

  P6opaquePtr result = (method->sub)(method->scope);
  this->pop();

  return result;
}

P6opaque* NqpVM::dispatch(P6opaque* code, unsigned int argc, ...) {
  P6opaquePtr slurp = NULL;
  mt_entry* method = code->method_table->lookup("postcircumfix:<( )>");

  if (method == NULL) {
    throw "error"; // MethodNotFound Error
  }
  if (method->sig->slurpy == false && argc != method->sig->argc) {
    throw "Bad number of args";
  } else if (method->sig->slurpy == true && argc < method->sig->expected) {
    throw "not enough args";
  }
  
  va_list argv;
  va_start(argv, argc);

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

  va_end(argv);

  P6opaquePtr result = (method->sub)(method->scope);
  this->pop();

  return result;
}



} // end namespace nqp

