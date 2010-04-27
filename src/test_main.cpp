#include <iostream>
#include <stdio.h>
#include "types.h"
#include "runtime_support.h"
#include <gc/gc_cpp.h>

//using namespace std;
//using namespace nqp;

P6opaquePtr add_two(Stash* lex) {
  Stash* stack = GET_VM()->top();

  int *a = (int*)stack->find("$a")->content_ptr;
  int *b = (int*)stack->find("$b")->content_ptr;

  return construct_int(*a + *b);
}

extern "C"
int main() {
  //return 0;
  nqp_init();
 
  Stash* stack = GET_VM()->top();

  P6opaque *subs = construct_sub(stack, reinterpret_cast<SubPtr>(add_two), 2, "$a", NULL, "$b", NULL);

  stack->values["&add_two"] = subs;

  P6opaquePtr foo = construct_int(4);
  P6opaquePtr baz = construct_int(3);

  P6opaquePtr result = GET_VM()->dispatch("&add_two", 2, foo, baz);
  GET_VM()->dispatch("&say", 1, result);

  GET_VM()->dispatch("&puts", 2, foo, baz);

  return 0;  
}
