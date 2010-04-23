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
  Stash *stack = GET_VM()->top(); 

  ArgsTy say_args = construct_args(1, "*@a", MuRef);
  P6opaque *subs = construct_sub(stack, reinterpret_cast<SubPtr>(_say), -1);
  stack->values["&say"] = subs;
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

ArgsTy construct_args(int argc, ...) {
  ArgsTy result = new ArgsTy;
  
}

P6opaque* construct_int(long long v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new int(v));
  result->klass_type = int_type;
  result->klass_name = "Int()";
  return result;
}

P6opaque* _say(Stash* lex) {
  Stash *stack = GET_VM()->top();

  for (StringMap<P6opaque*>::iterator it = stack->values.begin(); it != stack->values.end(); ++it) {
    cout << it->first() << " and " << *((int*)(it->second)->content_ptr) << endl;
  }
  cout << "blah and " << endl;
  return NULL;
}

/* 
P6opaque* _self_say(Stash* lex, P6opaque* self) {
//  P6opaque bar = *(stack->find("foo"));
// cout << "blah " << self << " and " << bar.klass_name << endl;
  return self;
}
*/

P6opaque* construct_sub(Stash *lex_scope, SubPtr sub_ptr, int argc, ...) {
  P6opaque* result = new P6opaque;
  result->klass_name = "Sub()";
  result->method_table = new StringMap<mt_entry*>;
  
  mt_entry *sub_entry = result->method_table->GetOrCreateValue("postcircumfix:<( )>", new mt_entry).second;
  sub_entry->sub = sub_ptr;
  sub_entry->argc = argc;
  sub_entry->sub_type = sub;
  sub_entry->scope = lex_scope;

  return result;
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

