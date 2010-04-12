#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cstdarg>
#include <exception>
#include <gc_cpp.h>
#include "types.h"

using namespace std;
using namespace llvm;

Kernel Kernel::_instance;

Kernel& Kernel::getInstance() {
  return _instance;
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
P6opaque* _self_say(Stash* lex, P6opaque* self, ...) {
  Kernel::push();
  Stash *stack = Kernel::top();
  P6opaque bar = *(stack->find("foo"));
  cout << "blah " << self << " and " << bar.klass_name << endl;
  Kernel::pop();
  return self;
}

/* 
extern "C"
P6opaque* _f(Stash* lex, P6opaque* b) {
  Kernel::push();
  Stash* stack = Kernel::top();

  P6opaque* c = lex->find("$c");

  P6opaque* result = construct_int(*static_cast<int*>(b->content_ptr) + 
                           *static_cast<int*>(c->content_ptr));

  cout << "result is: " << *static_cast<int*>(result->content_ptr) << endl;

  P6opaque *z = stack->find("$*z");
  cout << "and " << *static_cast<int*>(b->content_ptr) + 
                           *static_cast<int*>(z->content_ptr) << endl;
  Kernel::pop();
  return result;
}
*/

#define dispatch_sub(r, f, ...) do {\
    mt_entry *sub_table = f->method_table["postcircumfix:<( )>"];\
    r = sub_table->sub(sub_table->scope, __VA_ARGS__);\
  } while(0);

// TODO: Figure out the dispatch macro for methods
#define dispatch_method(r, f, ...) do {\
  } while(0);

/* 
extern "C" 
P6opaque* _g(Stash* lex) {
  Kernel::push();
  Stash* stack = Kernel::top();

  P6opaque *c = construct_int(4);
  stack->values["$c"] = c;

  stack->values["$*z"] = c;

  P6opaque *val = construct_int(4);
  P6opaque *result;

  dispatch_sub(result, lex->values["f"], val);

  Kernel::pop();
  return result;
} */

extern "C"
P6opaque* construct_sub(Stash *lex_scope, SubPtr sub_ptr, int argc) {
  P6opaque* result = new P6opaque;
  result->klass_name = "Sub()";
  
  mt_entry *sub_table = new mt_entry;
  sub_table->sub = sub_ptr;
  sub_table->argc = argc;
  sub_table->sub_type = sub;
  sub_table->scope = lex_scope;
  result->method_table->GetOrCreateValue("postcircumfix:<( )>", sub_table);

  return result;
}

/*
int main() {
  try {
    GC_INIT();  
    Kernel::push();
    Stash *scope = Kernel::top();
    P6opaque foo;
    P6opaque c = *construct_int(5); 
    foo.klass = string("Foo");
    scope->values["$foo"] = &foo;
    scope->values["$c"] = &c;
    scope->values["$*z"] = &c;

    P6opaque *f = construct_sub(scope, (SubPtr)*_f, 1);
    scope->values["f"] = f;

    cout << "f is : " << f << endl;

    cout << "$foo is: " << &foo << " " << foo.klass << " $c is " << *static_cast<int*>(c.constant_value) << endl;
    mt_entry self_say;
    self_say.method = *_self_say;
    self_say.argc = -1;
    foo.method_table["say"] = &self_say;

    cout << "HI?" << endl;

    f = _g(scope);
    cout << "result was: " << *static_cast<int*>(f->constant_value) << endl;
    cout << "$foo: " << foo.klass << endl;
    scope->find("$blah");
    Kernel::pop();
  }
  catch (...) {
    cerr << "Uncaught exception" << endl;
    return -1;
  }
  return 0;
}
*/


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


