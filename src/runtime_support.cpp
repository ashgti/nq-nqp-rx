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

  stack->values["&say"] = construct_sub(stack, reinterpret_cast<SubPtr>(_say), 2, "*@to-print", NULL);
  stack->values["&puts"] = construct_sub(stack, reinterpret_cast<SubPtr>(_say), 2, "*@to-print", NULL);;

  stack->values["&infix:<+>"] = construct_sub(stack, reinterpret_cast<SubPtr>(_infix_add), 4, "$lhs", NULL, "$rhs", NULL);
  stack->values["&infix:<->"] = construct_sub(stack, reinterpret_cast<SubPtr>(_infix_sub), 4, "$lhs", NULL, "$rhs", NULL);
  stack->values["&infix:<*>"] = construct_sub(stack, reinterpret_cast<SubPtr>(_infix_mul), 4, "$lhs", NULL, "$rhs", NULL);
  stack->values["&infix:</>"] = construct_sub(stack, reinterpret_cast<SubPtr>(_infix_div), 4, "$lhs", NULL, "$rhs", NULL);
  stack->values["&prefix:<+>"] = construct_sub(stack, reinterpret_cast<SubPtr>(_prefix_add), 2, "$val", NULL);
  
  stack->values["&infix:<~>"] = construct_sub(stack, reinterpret_cast<SubPtr>(_infix_stitch), 4, "$lhs", NULL, "$rhs", NULL);
  stack->values["&prefix:<~>"] = construct_sub(stack, reinterpret_cast<SubPtr>(_prefix_stitch), 2, "$val", NULL);
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
P6opaque* construct_str(N_STR v, uint64_t len) {
  P6opaque* result = new P6opaque;
  if (len == ULLONG_MAX) { 
    len = strlen(v);
  }

  StrObj *str_container = new StrObj;

  str_container->len = len;
  str_container->val = new N_STR_VAL[len+1];

  strncpy((char*)str_container->val, v, len);

  result->content_ptr = static_cast<void*>(str_container);
  result->klass_type = kBUILT_IN_STR;
  result->klass_name = "Str()";

  return result;
}

P6opaque* construct_num(N_NUM v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new N_NUM(v));
  result->klass_type = kBUILT_IN_NUM;
  result->klass_name = "Num()";
  return result;
}

P6opaque* construct_bool(N_BOOL v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new N_BOOL(v));
  result->klass_type = kBUILT_IN_BOOL;
  result->klass_name = "Bool()";
  return result;
}

P6opaquePtr _infix_add(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr lhs = stack_find(stack, "$lhs");
  P6opaquePtr rhs = stack_find(stack, "$rhs");
  
  if (rhs->klass_type == lhs->klass_type == kBUILT_IN_INT) {
    return construct_int(*static_cast<N_INT*>(lhs->content_ptr) + *static_cast<N_INT*>(rhs->content_ptr));
  }
  else if ((rhs->klass_type == kBUILT_IN_NUM || rhs->klass_type == kBUILT_IN_INT) && (lhs->klass_type == kBUILT_IN_NUM || lhs->klass_type == kBUILT_IN_INT)) {
    return construct_num(*static_cast<N_NUM*>(lhs->content_ptr) + *static_cast<N_INT*>(rhs->content_ptr));
  }
  else {
    // TODO: call some sort of conversion to cast objects as nums
    throw new exception;
  }
  return NULL;
}

P6opaquePtr _infix_sub(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr lhs = stack_find(stack, "$lhs");
  P6opaquePtr rhs = stack_find(stack, "$rhs");
  
  if (rhs->klass_type == lhs->klass_type == kBUILT_IN_INT) {
    return construct_int(*static_cast<N_INT*>(lhs->content_ptr) - *static_cast<N_INT*>(rhs->content_ptr));
  }
  else if ((rhs->klass_type == kBUILT_IN_NUM || rhs->klass_type == kBUILT_IN_INT) && (lhs->klass_type == kBUILT_IN_NUM || lhs->klass_type == kBUILT_IN_INT)) {
    return construct_num(*static_cast<N_NUM*>(lhs->content_ptr) - *static_cast<N_INT*>(rhs->content_ptr));
  }
  else {
    // TODO: call some sort of conversion to cast objects as nums
    throw new exception;
  }
  return NULL;
}

P6opaquePtr _infix_mul(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr lhs = stack_find(stack, "$lhs");
  P6opaquePtr rhs = stack_find(stack, "$rhs");
  
  if (rhs->klass_type == lhs->klass_type == kBUILT_IN_INT) {
    return construct_int(*static_cast<N_INT*>(lhs->content_ptr) * *static_cast<N_INT*>(rhs->content_ptr));
  }
  else if ((rhs->klass_type == kBUILT_IN_NUM || rhs->klass_type == kBUILT_IN_INT) && (lhs->klass_type == kBUILT_IN_NUM || lhs->klass_type == kBUILT_IN_INT)) {
    return construct_num(*static_cast<N_NUM*>(lhs->content_ptr) * *static_cast<N_INT*>(rhs->content_ptr));
  }
  else {
    // TODO: call some sort of conversion to cast objects as nums
    throw new exception;
  }
  return NULL;
}

P6opaquePtr _infix_div(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr lhs = stack_find(stack, "$lhs");
  P6opaquePtr rhs = stack_find(stack, "$rhs");
  
  if (rhs->klass_type == lhs->klass_type == kBUILT_IN_INT) {
    return construct_int(*static_cast<N_INT*>(lhs->content_ptr) / *static_cast<N_INT*>(rhs->content_ptr));
  }
  else if ((rhs->klass_type == kBUILT_IN_NUM || rhs->klass_type == kBUILT_IN_INT) && (lhs->klass_type == kBUILT_IN_NUM || lhs->klass_type == kBUILT_IN_INT)) {
    return construct_num(*static_cast<N_NUM*>(lhs->content_ptr) / *static_cast<N_INT*>(rhs->content_ptr));
  }
  else {
    // TODO: call some sort of conversion to cast objects as nums
    throw new exception;
  }
  return NULL;
}

P6opaquePtr _infix_stitch(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr lhs = stack_find(stack, "$lhs");
  P6opaquePtr rhs = stack_find(stack, "$rhs");
  
  N_STR lhs_repr = internal_to_str(lhs);
  size_t lhs_len = strlen(lhs_repr);
  
  N_STR rhs_repr = internal_to_str(rhs);
  size_t rhs_len = strlen(rhs_repr);

  char* combined = (char*)malloc(sizeof(N_STR_VAL) * (lhs_len + rhs_len));

  size_t len_cpy = lhs_len;
  while (len_cpy--) {
    combined[len_cpy] = lhs_repr[len_cpy];
  }
  len_cpy = rhs_len;
  while (len_cpy--) {
    combined[lhs_len + len_cpy] = rhs_repr[len_cpy];
  }
  combined[lhs_len + rhs_len + 1] = '\0';

  P6opaquePtr result = construct_str(combined, lhs_len + rhs_len + 1);
  
  return result;
}

P6opaquePtr _prefix_stitch(Stash* lex) {
  Stash* stack = vm_stack_top();
  P6opaquePtr val = stack_find(stack, "$val");
  
  if (val->klass_type == kBUILT_IN_STR) {
    return val;
  }
  else {
    return construct_str(internal_to_str(val));
  }
}

P6opaquePtr _prefix_add(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr val = stack_find(stack, "$var");
  
  return construct_num(internal_to_num(val));
}

N_NUM internal_to_num(P6opaquePtr val) {
  switch (val->klass_type) {
    case kBUILT_IN_INT:
      return *static_cast<N_INT*>(val->content_ptr);
      break;
    case kBUILT_IN_NUM:
      return *static_cast<N_NUM*>(val->content_ptr);
      break;
    case kBUILT_IN_STR:
      /* magic happens here */
      throw new exception;
      break;
    case kBUILT_IN_BOOL:
      if (*(N_BOOL*)val->content_ptr) {
        return 1;
      }
      else {
        return 0;
      }
      break;
    default:
      cerr << "I don't know how to numify this yet " << val->klass_name << endl;
      exit(-1);
      break;
  }
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
      o << (N_STR)((StrObj*)val->content_ptr)->val;
      break;
    case kBUILT_IN_BOOL:
      if (*(N_BOOL*)val->content_ptr) {
        o << "True";
      }
      else {
        o << "False";
      }
      break;
    case kBUILT_IN_MU:
      o << "Mu()";
      break;
    case kBUILT_IN_ARRAY:
      o << array_size(val);
      break;
    default:
      cerr << "I don't know how to print this yet" << endl;
      exit(-1);
      break;
  }

  string result_buf = o.str();
  char* result = (char*)malloc(sizeof(N_STR_VAL) * result_buf.length());
  for (size_t i = 0; i < result_buf.length(); i++)
    result[i] = result_buf[i];
  result[result_buf.length()] = '\0';
 
  return result;
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

P6opaquePtr vm_dispatch(const char* sub_name, unsigned int argc, ...) {
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

