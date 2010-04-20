/*
 * =====================================================================================
 *
 *       Filename:  signatures.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2010 10:21:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "P6opaque.h"
#include <gc/gc_cpp.h>

using namespace std;

enum container_type_t {
  scalar,
  hash,
  array,
  code
};

enum arg_type {
  named,
  requied,
  optional,
}

struct container {
  container_type_t type;
  P6opaque *val;
  int type;
  int constraint;
};

struct param_capture {
  int argc;
  container *argv;
};

struct signature {
  int argc;
  container *argv;
}

struct method_entry { 
  signature_t sig_ref;
  Ptr cfunc*
}

struct ArgsTy : gc {
  StringMap<P6opaque *> kwargs;
  vector<P6opaque *> args;
};

extern "c"
P6opaque *
nqp_vm_dispatch_sub(char *name, ArgsTy *args) {
  kernel::push();
  Stash stack = kernel::top();

  function = stack.find(name);

  if (NULL == function) {
    throw "method not found error...";
  }

  P6opaque* result = function(stack, package);

  kernel::pop();
  return result;
}

extern "C"
P6opaque *
nqp_vm_dispatch_method(P6opaqe* self, char *name) {

}

extern "c"
P6opaque *
foo(P6opaque *self, Stack stack, Stack package) {
  P6opaque *a = stack["$a"];
  P6opaque *foo = stack["&foo"];

}

/* bar($a, $b) */
extern "c"
P6opaque *
bar(Stack stack, Stack package) {
    
}

extern "C"
signature *
new_sig(int count, ...) {
  va_list ap;
  signature* result = new signature;
  string 
  result->argc = count;
  va_start(ap, count);
  for (int i = 0; i < count; i++) {
    container
  }
  va_end(ap);

}

extern "C"
void
Settings_setup() {
  P6opaque *Foo = new_class("Foo");
  add_method(Foo, make_method(*foo));
  stack = kernel::top();
  stack.add("Foo") = Foo;
  bar_sig = new_sig("$a", MuRef, "$b", MuRef);
  construct_sub("bar", bar, signature);
  stack.add("&bar", bar);
}


