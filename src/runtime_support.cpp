/*
 * =====================================================================================
 *
 *       Filename:  runtime_support.cpp
 *
 *    Description:  Links to the C++ implemented components that need access from the LLVM
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


#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cstdarg>
#include <exception>
#include <gc/gc_cpp.h>
#include <llvm/ADT/StringMap.h>
#include "types.h"
#include "runtime_support.h"

using namespace std;
using namespace llvm;

namespace nqp { 

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

void
nqp_init() {
  GC_INIT();
  NqpVM::main_vm = new NqpVM();
  settings();
}

void settings() {
  GET_VM()->push();
  Stash *stack = GET_VM()->top();

  cout << "stack id" << stack << endl;;

  P6opaque *say = construct_sub(stack, reinterpret_cast<SubPtr>(_say), 1, "*@to-print", NULL);
  stack->values["&say"] = say;

  P6opaque *puts = construct_sub(stack, reinterpret_cast<SubPtr>(_puts), 1, "*@to-print", NULL);
  stack->values["&puts"] = puts;
}

Stash *vm_stack_top() {
  return NqpVM::current()->top();
}

void vm_stack_push() {
  GET_VM()->push();
}

void vm_stack_pop() {
  GET_VM()->pop();
}

P6opaquePtr construct_array() {
  P6opaquePtr result = new P6opaque;

  result->klass_type = kBUILT_IN_ARRAY;
  result->klass_name = "Array()";
  result->content_ptr = static_cast<void*>(new map<long long int, P6opaquePtr>);

  return result;
}

void array_push(P6opaquePtr ar, P6opaquePtr val) {
  vector<P6opaquePtr> *ref = static_cast<vector<P6opaquePtr> *>(ar->content_ptr);
  ref->push_back(val); 
}

P6opaquePtr array_pop(P6opaquePtr ar) {
  vector<P6opaquePtr> *ref = static_cast<vector<P6opaquePtr> *>(ar->content_ptr);
  P6opaquePtr result = ref->back();
  ref->pop_back(); 
  return result;
}

P6opaquePtr array_at(P6opaquePtr ar, int key) {
  return static_cast<vector<P6opaquePtr> *>(ar->content_ptr)->at(key);  
}

unsigned int array_size(P6opaquePtr ar) {
  return static_cast<vector<P6opaquePtr> *>(ar->content_ptr)->size();
}

P6opaque* construct_int(long long v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new int(v));
  result->klass_type = kBUILT_IN_INT;
  result->klass_name = "Int()";
  return result;
}

P6opaquePtr _say(Stash* lex) {
  Stash *stack = GET_VM()->top();
  P6opaquePtr vals = stack->values["@to-print"];
  unsigned int size = array_size(vals); 

  for (unsigned int i = 0; i < size; ++i) {
    P6opaquePtr arg = array_at(vals, i);
    cout << *((int*)arg->content_ptr);
  }

  cout << "\n";
  return NULL;
}

P6opaquePtr _puts(Stash* lex) {
  Stash *stack = GET_VM()->top();
  P6opaquePtr vals = stack->values["@to-print"];
  unsigned int size = array_size(vals); 

  for (unsigned int i = 0; i < size; ++i) {
    P6opaquePtr arg = array_at(vals, i);
    cout << *((int*)arg->content_ptr) << " ";
  }

  cout << "\n";
  return NULL;
}

P6opaquePtr construct_sub(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc * 2);
  
  ParamTyPtr sub_args = new ParamTy;
  sub_args->argv = new ParameterHolder[argc];
  sub_args->argc = argc;
  sub_args->expected = 0;
  sub_args->slurpy = false;
  
  for (unsigned int i=0; i < argc; i++) {
    char* tmp_name = va_arg(argv, char*);
    char* name;
    P6opaquePtr init = va_arg(argv, P6opaquePtr);
    ParameterHolder tmp;
    int name_length = strlen(tmp_name);
    name = (char*)malloc(sizeof(char) * (name_length + 1));
    strncpy(name, tmp_name, name_length);
    tmp.ptype = kREQUIRED;

    if (name[0] == '*') {
      strncpy(name, name+1, name_length--);
      sub_args->slurpy = true;
      tmp.ptype = kOPTIONAL;
      tmp.slurpy = true;
    }
    else if (name[0] == ':') {
      tmp.ptype = kNAMED;
    }
    else if (name[name_length-1] == '?') {
      strncpy(name, name, name_length - 1);
      tmp.ptype = kOPTIONAL;
    }
    else {
      sub_args->expected++;
    }

    switch (name[0]) {
      case '@':
        tmp.ctype = kARRAY;
        break;
      case '$':
        tmp.ctype = kSCALAR;
        break;
      case '&':
        tmp.ctype = kCODE;
        break;
      case '%':
        tmp.ctype = kHASH;
        break;
      default:
        cout << "Bad sigil... how did you get here?";
    }

    tmp.name = name;
    tmp.val = init;
    sub_args->argv[i] = tmp;
  }

  va_end(argv);
  P6opaque* result = new P6opaque;
  result->klass_name = "Sub()";
  result->klass_type = kBUILT_IN_SUB;
  result->method_table = new StringMap<mt_entry*>;
  mt_entry *sub_entry = result->method_table->GetOrCreateValue("postcircumfix:<( )>", new mt_entry).second;
  sub_entry->sub = sub_ptr;
  sub_entry->sig = sub_args;
  sub_entry->sub_type = sub;
  sub_entry->scope = lex_scope;

  return result;
}

void print_stack(Stash *stack) {
  for (StringMap<P6opaque*>::iterator it = stack->values.begin(); it != stack->values.end(); ++it) {
    cout << it->first() << " and " << *((int*)(it->second)->content_ptr) << endl;
  }
}

/* 
P6opaque* invoke_sub(Stash *lex_scope, char* name, SubPtr sub_ptr, int argc) {
  P6opaque* result = new P6opaque;
  result->klass_name = "Sub()";
  result->method_table = new StringMap<mt_entry*>;
  
  mt_entry *sub_entry = result->method_table->lookup("postcircumfix:<( )>", new mt_entry).second; // .second; // = new mt_entry;
  sub_entry->sub = sub_ptr;
  sub_entry->argc = argc;
  sub_entry->sub_type = sub;
  sub_entry->scope = lex_scope;
  // result->method_table->GetOrCreateValue("postcircumfix:<( )>", sub_entry);

  return result;
}
*/

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif


}

