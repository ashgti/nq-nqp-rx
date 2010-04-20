#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cstdarg>
#include <exception>
// #include <gc_cpp.h>
#include "types.h"

using namespace std;
using namespace llvm;

Kernel Kernel::_instance;

Kernel& Kernel::getInstance() {
  return _instance;
}

extern "C" 
Stash *kernel_top() {
  return Kernel::top();
}

extern "C"
void kernel_push() {
  Kernel::push();
}

extern "C"
void kernel_pop() {
  Kernel::pop();
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
P6opaque* _say(Stash* lex, int argc, ...) {
  Kernel::push();
  Stash *stack = Kernel::top();
  cout << "blah and " << endl;
  Kernel::pop();
  return NULL;
}

extern "C"
P6opaque* _self_say(Stash* lex, P6opaque* self, ...) {
  Kernel::push();
  Stash *stack = Kernel::top();
  P6opaque bar = *(stack->find("foo"));
  cout << "blah " << self << " and " << bar.klass_name << endl;
  Kernel::pop();
  return self;
}

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

Stash* Kernel::top() {
  Kernel &that = getInstance();
  return that.lex_pad;
}

void Kernel::push() {
  Kernel &that = getInstance();
  Stash *new_lex = new Stash();
  new_lex->OUTER = that.lex_pad;
  that.lex_pad = new_lex;
}

void Kernel::pop() {
  Kernel &that = getInstance();
  that.lex_pad = that.lex_pad->OUTER;
}


