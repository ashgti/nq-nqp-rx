#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <vector>
#include <cstdarg>
#include <exception>
#include <gc_cpp.h>

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

class MethodNotFoundException : public gc_cleanup, public exception {
 private:
  string arg;
 public:
  MethodNotFoundException(string arg = "") : arg(arg) { }
  ~MethodNotFoundException() throw() { }
  virtual const char* what() const throw() {
    return (string("abc ") + arg).c_str();
  }
};

class Stash;

class Kernel : public gc_cleanup {
 private: 
  static Kernel _instance;
  Stash *lex_pad;
  map<string, Stash*> lookup;
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

/* method table */
struct mt_table {
  sub_type_t sub_type;
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
  map<string, P6opaque*> properties;
  map<string, mt_table*> method_table;
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
  map<string, P6opaque*> values;
  Stash* OUTER;

  P6opaque* find(string name) {
    map<string, P6opaque*>::iterator it = values.find(name);
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
  //Kernel::push();
  //Stash* stack = Kernel::top();
  //P6opaque* result = new P6opaque;

  P6opaque* c = lex->find("$c");

  P6opaque* result = construct_int(*static_cast<int*>(b->constant_value) + 
                           *static_cast<int*>(c->constant_value));

  //Kernel::pop();
  return result;
}


extern "C" 
P6opaque* _g(Stash* lex) {
  Kernel::push();
  Stash* stack = Kernel::top();

  P6opaque *c = construct_int(4);
  stack->values["$c"] = c;

  P6opaque *val = construct_int(4);
  P6opaque *result = dispatch(stack->values["f"], val);

  Kernel::pop();
  return result;
}

P6opaque* construct_sub(SubPtr sub_ptr, int argc) {
  P6opaque* result = new P6opaque;
  result->klass = "Sub()";

  mt_table *sub_table = new mt_table;
  sub_table->sub = sub_ptr;
  sub_table->argc = argc;
  sub_table->sub_type = sub;

  result->method_table["invoke"] = sub_table;

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
    scope->values["foo"] = &foo;
    scope->values["$c"] = &c;
    cout << "foo is: " << &foo << " " << foo.klass << " C is " << *static_cast<int*>(c.constant_value) << endl;
    mt_table self_say;
    self_say.method = *_self_say;
    self_say.argc = -1;
    foo.method_table["say"] = &self_say;
    foo.method_table.find("say")->second->method(&foo);

    cout << "foo: " << foo.klass << endl;
    scope->find("blah");
    Kernel::pop();
  }
  catch (MethodNotFoundException e) {
    cerr << "MethodNotFoundException: " << e.what() << endl;
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


