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
#include <sstream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cstdarg>
#include <exception>
#include <gc/gc_cpp.h>
#include <llvm/ADT/StringMap.h>
#include "types.h"
#include "vm.h"
#include "runtime_support.h"

using namespace std;
using namespace llvm;

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

void
nqp_init() {
  GC_INIT();
  nqp::NqpVM::main_vm = new nqp::NqpVM();
  settings();
}

void settings() {
  GET_VM()->push();
  Stash *stack = GET_VM()->top();

  P6opaque *say = construct_sub(stack, reinterpret_cast<SubPtr>(_say), 2, "*@to-print", NULL);
  stack->values["&say"] = say;

  P6opaque *puts = construct_sub(stack, reinterpret_cast<SubPtr>(_puts), 2, "*@to-print", NULL);
  stack->values["&puts"] = puts;

  P6opaque *infix_add = construct_sub(stack, reinterpret_cast<SubPtr>(_infix_add), 4, "$lhs", NULL, "$rhs", NULL);
  stack->values["&infix:<+>"] = infix_add;
}

Stash* vm_stack_top() {
  Stash* stack = nqp::NqpVM::current()->top();
  return stack;
}

Stash* vm_stack_push() {
  return GET_VM()->push();
}

void vm_stack_pop() {
  GET_VM()->pop();
}

P6opaquePtr construct_array() {
  P6opaquePtr result = new P6opaque;

  result->klass_type = kBUILT_IN_ARRAY;
  result->klass_name = "Array()";
  result->content_ptr = static_cast<void*>(new vector<P6opaquePtr>);

  return result;
}

void array_push(P6opaquePtr ar, P6opaquePtr val) {
  vector<P6opaquePtr> *ref = (vector<P6opaquePtr> *)ar->content_ptr;
  ref->push_back(val);
}

P6opaquePtr array_pop(P6opaquePtr ar) {
  vector<P6opaquePtr> *ref = static_cast<vector<P6opaquePtr> *>(ar->content_ptr);
  P6opaquePtr result = ref->back();
  ref->pop_back(); 
  return result;
}

P6opaquePtr array_at(P6opaquePtr ar, int key) {
  vector<P6opaquePtr> *ref = static_cast<vector<P6opaquePtr> *>(ar->content_ptr);
  if (key < ref->size() + 1) {
    return ref->at(key);  
  } 
  else {
    return NULL;
  }
}

unsigned int array_size(P6opaquePtr ar) {
  return static_cast<vector<P6opaquePtr> *>(ar->content_ptr)->size();
}

P6opaque* construct_int(N_INT v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new N_INT(v));
  result->klass_type = kBUILT_IN_INT;
  result->klass_name = "Int()";
  return result;
}

// 32 vs 64 bit here
P6opaque* construct_str(N_STR v, int64_t len = ULLONG_MAX) {
  P6opaque* result = new P6opaque;
  if (len == ULLONG_MAX) len = 0;
  result->content_ptr = static_cast<void*>(new N_STR);
  result->klass_type = kBUILT_IN_STR;
  result->klass_name = "Str()";
  return result;
}

P6opaque* construct_num(N_NUM v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new N_INT(v));
  result->klass_type = kBUILT_IN_NUM;
  result->klass_name = "Num()";
  return result;
}

P6opaquePtr _infix_add(Stash* lex) {
  Stash* stack = vm_stack_top();

  print_stack(stack);
  print_stack(lex);

  P6opaquePtr lhs = stack_find(stack, "$lhs");
  P6opaquePtr rhs = stack_find(stack, "$rhs");
  
  if (rhs->klass_type == lhs->klass_type == kBUILT_IN_INT) {
    return construct_int(*static_cast<N_INT*>(lhs->content_ptr) + *static_cast<N_INT*>(rhs->content_ptr));
  }
  else {
    throw new exception;
  }
  return NULL;
}

N_STR internal_to_str(P6opaquePtr val) {
  ostringstream o;
  switch (val->klass_type) {
    case kBUILT_IN_INT:
      o << *((N_INT*)val->content_ptr);
      break;
    case kBUILT_IN_NUM:
      o << *((N_NUM*)val->content_ptr);
      break;
    case kBUILT_IN_STR:
      o << *((N_STR*)val->content_ptr);
      break;
    case kBUILT_IN_BOOL:
      if (*(N_BOOL*)val->content_ptr) {
        cout << "True";
      }
      else {
        cout << "False";
      }
      break;
    case kBUILT_IN_MU:
      cout << "Mu()";
      break;
    default:
      cerr << "I don't know how to print this yet" << endl;
      exit(-1);
      break;
  }

  return (N_STR)o.str().c_str();
}

P6opaquePtr _say(Stash* lex) {
  Stash *stack = GET_VM()->top();
  P6opaquePtr vals = stack_find(stack, "@to-print");
  unsigned int size = array_size(vals);

  for (unsigned int i = 0; i < size; ++i) {
    P6opaquePtr arg = array_at(vals, i);
    if (!arg) {
      cerr << "Bad argument to &say" << endl;
      continue;
    }
    cout << internal_to_str(arg);
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
    if (arg)
      cout << internal_to_str(arg) << " ";
  }

  cout << "\n";
  return NULL;
}

P6opaquePtr stack_find(Stash *stack, const char* name) {
  StringMap<P6opaque*>::iterator it = stack->values.find(name);
  if (it == stack->values.end()) {
    if (stack->OUTER == NULL) {
      throw "Error Value not found";
    }
    else {
      return stack_find(stack->OUTER, name);
    }
  }
  else {
    return it->second;
  }
}


ParamTyPtr construct_args(unsigned int argc, va_list argv) {
  ParamTyPtr sub_args = new ParamTy;
  sub_args->argv = new ParameterHolder[argc / 2];
  sub_args->argc = argc / 2;
  sub_args->expected = 0;
  sub_args->slurpy = false;
  
  for (unsigned int i=0; i < argc / 2; i++) {
    const char* tmp_name = va_arg(argv, const char*);
    char* name;
    P6opaquePtr init = va_arg(argv, P6opaquePtr);
    ParameterHolder tmp;
    int name_length = strlen(tmp_name);
    name = (char*)malloc(sizeof(char) * (name_length + 1));
    strncpy(name, tmp_name, name_length);
    tmp.ptype = kREQUIRED;
    tmp.slurpy = false;

    if (name[0] == '*') {
      char* name_holder = (char*)malloc(sizeof(char) * name_length);
      strncpy(name_holder, name, name_length);
      strncpy(name, name_holder+1, name_length--);
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

    // cout << "Testing: " << name << endl;

    tmp.name = name;
    tmp.val = init;
    sub_args->argv[i] = tmp;
  }

  return sub_args;
}

P6opaquePtr construct_sub(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc);
  
  ParamTyPtr sub_args = construct_args(argc, argv);

  va_end(argv);
  P6opaquePtr result = new P6opaque;
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

P6opaquePtr construct_closure(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc);
  ParamTyPtr sub_args = construct_args(argc, argv);
  va_end(argv);

  P6opaquePtr result = new P6opaque;
  result->klass_name = "Block()";
  result->klass_type = kBUILT_IN_BLOCK;
  result->method_table = new StringMap<mt_entry*>;
  mt_entry *sub_entry = result->method_table->GetOrCreateValue("postcircumfix:<( )>", new mt_entry).second;
  sub_entry->sub = sub_ptr;
  sub_entry->sig = sub_args;
  sub_entry->sub_type = sub;
  sub_entry->scope = lex_scope;

  return result;
}

void print_stack(Stash *stack) {
  if (stack->values.size()) {
    for (StringMap<P6opaque*>::iterator it = stack->values.begin(); it != stack->values.end(); ++it) {
      cout << it->first() << " and " << it->second->klass_name << endl;
    }
  }
}

P6opaquePtr vm_dispatch_sub(const char* sub_name, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc);
  P6opaquePtr result = GET_VM()->vdispatch(sub_name, argc, argv);
  va_end(argv);
  return result;
}

P6opaquePtr vm_invoke(P6opaquePtr sub_obj, unsigned int argc, ...) {
  va_list argv;
  va_start(argv, argc);
  P6opaquePtr result = GET_VM()->vdispatch(sub_obj, argc, argv);
  va_end(argv);
  return result;
}

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

