#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cstdarg>
#include <exception>
#include <gc_cpp.h>
#include <llvm/ADT/StringMap.h>

/*
 * my $c := 5; 
 * sub f($b) { 
 *  $b + $c 
 * }
 * sub g() { 
 *  my $c := 4;
 *  f(4) 
 * }
 *
 * $c := 7;
 *
 * say(g());
 */


using namespace std;
using namespace llvm;

class Stash;

class Kernel : public gc_cleanup {
 private: 
  static Kernel _instance;
  Stash *lex_pad;
  Kernel() { }
  ~Kernel() { }

  Kernel(const Kernel&);                 // Prevent copy-construction
  Kernel& operator=(const Kernel&);      // Prevent assignment

 public:
  static Stash* top();
  static void push();
  static void pop();

  static Kernel &getInstance() {
    return _instance;
  }
};

Kernel Kernel::_instance;

struct P6opaque;

typedef P6opaque* (*MethodPtr)(Stash*, P6opaque*, ...);
typedef P6opaque* (*SubMethodPtr)(Stash*, P6opaque*, ...);
typedef P6opaque* (*SubPtr)(Stash*, ...);
typedef P6opaque* (*PhaserPtr)(Stash*, ...);

enum sub_type_t {
  sub = 0,
  method = 1,
  submethod = 2,
  phaser = 3
};

/* method entry */
struct mt_entry {
  sub_type_t sub_type;
  Stash* scope;
  union {
    MethodPtr method;
    SubMethodPtr submethod;
    SubPtr sub;
  };
  signed int argc;
};

struct P6opaque : public gc {
  string klass;  
  vector<P6opaque*> parents;
  void* constant_value;
  StringMap<P6opaque*> properties;
  StringMap<mt_entry*> method_table;
};

inline P6opaque* construct_int(int v) {
  P6opaque* result = new P6opaque;
  result->constant_value = (void*)new int(v);
  result->klass = "Int";
  return result;
}

class Stash : public gc {
 public:
  Stash() { }
  StringMap<P6opaque*> values;
  Stash* OUTER;

  P6opaque* find(string name) {
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
};

extern "C"
P6opaque* _self_say(Stash* lex, P6opaque* self, ...) {
  Kernel::push();
  Stash *stack = Kernel::top();
  P6opaque bar = *(stack->find("foo"));
  cout << "blah " << self << " and " << bar.klass << endl;
  Kernel::pop();
  return self;
}

extern "C"
P6opaque* _f(Stash* lex, P6opaque* b) {
  Kernel::push();
  Stash* stack = Kernel::top();

  P6opaque* c = lex->find("$c");

  P6opaque* result = construct_int(*static_cast<int*>(b->constant_value) + 
                           *static_cast<int*>(c->constant_value));

  cout << "result is: " << *static_cast<int*>(result->constant_value) << endl;

  P6opaque *z = stack->find("$*z");
  cout << "and " << *static_cast<int*>(b->constant_value) + 
                           *static_cast<int*>(z->constant_value) << endl;
  Kernel::pop();
  return result;
}


#define dispatch_sub(r, f, ...) do {\
    mt_entry *sub_table = f->method_table["postcircumfix:<( )>"];\
    r = sub_table->sub(sub_table->scope, __VA_ARGS__);\
  } while(0);


// TODO: Figure out the dispatch macro for methods
#define dispatch_method(r, f, ...) do {\ 
  } while(0);

extern "C" 
P6opaque* _g(Stash* lex) {
  Kernel::push();
  Stash* stack = Kernel::top();

  P6opaque *c = construct_int(4);
  stack->values["$c"] = c;

  stack->values["$*z"] = c;

  P6opaque *val = construct_int(4);
  P6opaque *result;

  dispatch(result, lex->values["f"], val);

  Kernel::pop();
  return result;
}

extern "C"
P6opaque* construct_sub(Stash *lex_scope, SubPtr sub_ptr, int argc) {
  P6opaque* result = new P6opaque;
  result->klass = "Sub()";

  mt_entry *sub_table = new mt_entry;
  sub_table->sub = sub_ptr;
  sub_table->argc = argc;
  sub_table->sub_type = sub;
  sub_table->scope = lex_scope;

  result->method_table["postcircumfix:<( )>"] = sub_table;

  return result;
}

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


