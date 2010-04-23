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
// #include <gc_cpp.h>
#include "types.h"
#include "runtime_support.h"

using namespace std;
using namespace llvm;

namespace nqp {

extern "C"
void
init_nqp() {
  settings();
}

extern "C"
void settings() {
  GET_VM()->push();
  Stash *stack = GET_VM()->top(); 

  P6opaque *subs = construct_sub(stack, reinterpret_cast<SubPtr>(_say), -1);
  stack->values["&say"] = subs;
}

extern "C" 
Stash *vm_stack_top() {
  return GET_VM()->top();
}

extern "C"
void vm_stack_push() {
  GET_VM()->push();
}

extern "C"
void vm_stack_pop() {
  GET_VM()->pop();
}

extern "C"
P6opaque* construct_int(long long v) {
  P6opaque* result = new P6opaque;
  result->content_ptr = static_cast<void*>(new int(v));
  result->klass_type = int_type;
  result->klass_name = "Int()";
  return result;
}

extern "C"
P6opaque* _say(Stash* lex, long long argc) {
  GET_VM()->push();
  Stash *stack = GET_VM()->top();
  cout << "blah and " << endl;
  GET_VM()->pop();
  return NULL;
}

/* 
extern "C"
P6opaque* _self_say(Stash* lex, P6opaque* self) {
//  P6opaque bar = *(stack->find("foo"));
// cout << "blah " << self << " and " << bar.klass_name << endl;
  return self;
}
*/

extern "C"
P6opaque* construct_sub(Stash *lex_scope, char* name, SubPtr sub_ptr, int argc) {
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

extern "C"
P6opaque* invoke_sub(Stash *lex_scope, char* name, SubPtr sub_ptr, int argc) {
  P6opaque* result = new P6opaque;
  result->klass_name = "Sub()";
  result->method_table = new StringMap<mt_entry*>;
  
  mt_entry *sub_entry = result->method_table->GetOrCreateValue("postcircumfix:<( )>", new mt_entry).second; // .second; // = new mt_entry;
  sub_entry->sub = sub_ptr;
  sub_entry->argc = argc;
  sub_entry->sub_type = sub;
  sub_entry->scope = lex_scope;
  // result->method_table->GetOrCreateValue("postcircumfix:<( )>", sub_entry);

  return result;
}

} // end namespace nqp

