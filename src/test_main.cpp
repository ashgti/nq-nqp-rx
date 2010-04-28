#include <iostream>
#include <stdio.h>
#include "types.h"
#include "runtime_support.h"
#include "vm.h"
#include <gc/gc_cpp.h>

P6opaquePtr add_two(Stash* lex) {
  Stash* stack = vm_stack_top();

  int *a = (int*)stack_find(stack, "$a")->content_ptr;
  int *b = (int*)stack_find(stack, "$b")->content_ptr;

  return construct_int(*a + *b);
}

extern "C"
int main() {
  nqp_init();
 
  Stash* stack = vm_stack_top();

  P6opaque *subs = construct_sub(stack, reinterpret_cast<SubPtr>(add_two), 2, "$a", NULL, "$b", NULL);

  stack->values["&add_two"] = subs;

  P6opaquePtr foo = construct_int(4);
  P6opaquePtr baz = construct_int(3);

  P6opaquePtr result = vm_dispatch_sub("&add_two", 2, foo, baz);
  vm_dispatch_sub("&say", 1, result);
  vm_dispatch_sub("&puts", 2, foo, baz);

  return 0;  
}
