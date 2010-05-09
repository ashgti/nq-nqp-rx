#include <iostream>
#include <stdio.h>
#include "types.h"
#include "runtime_support.h"
#include "vm.h"
#include <gc/gc_cpp.h>

using namespace std;

P6opaquePtr add_two(Stash* lex) {
  Stash* stack = vm_stack_top();

  int *a = (int*)stack_find(stack, "$a")->content_ptr;
  int *b = (int*)stack_find(stack, "$b")->content_ptr;

  return construct_int(*a + *b);
}

P6opaquePtr block(Stash* lex) {
  Stash* stack = vm_stack_top();

  return stack_find(lex, "$i");
}

P6opaquePtr foo(Stash* lex) {
  Stash* stack = vm_stack_top();

  P6opaquePtr i = stack_find(stack, "$i");

  Stash* block_stack = vm_stack_push();
  block_stack->values["$i"] = i;
  P6opaquePtr result = construct_closure(block_stack, reinterpret_cast<SubPtr>(block), 0);
  vm_stack_pop();

  return result;
}

extern "C"
int main() {
  nqp_init();
 
  Stash* stack = vm_stack_top();

  P6opaquePtr subs = construct_sub(stack, reinterpret_cast<SubPtr>(add_two), 4, "$a", NULL, "$b", NULL);
  stack->values["&add_two"] = subs;
  subs = construct_sub(stack, reinterpret_cast<SubPtr>(foo), 2, "$i", NULL);
  stack->values["&foo"] = subs;

  P6opaquePtr foo = construct_int(4l);
  P6opaquePtr baz = construct_int(3l);
 
  P6opaquePtr bar = construct_str("Hello World");
  P6opaquePtr num = construct_num(123.123);
  P6opaquePtr bool_test = construct_bool(N_BOOL_TRUE);

  P6opaquePtr result = vm_dispatch("&add_two", 2, foo, baz);
  P6opaquePtr result2 = vm_dispatch("&infix:<~>", 2, foo, bar);

  vm_dispatch("&say", 1, result2);

  //cout << "result is: " << *(int*)result->content_ptr << endl;
  //cout << " and " << result->klass_type << " id " << result << endl;

  vm_dispatch("&say", 1, result);
  vm_dispatch("&puts", 2, foo, baz);
  vm_dispatch("&puts", 3, bar, num, bool_test);

  vm_dispatch("&puts", 1, vm_dispatch("&infix:<->", 2, num, baz));

  P6opaquePtr a = vm_dispatch("&foo", 1, foo);
  P6opaquePtr b = vm_dispatch("&foo", 1, baz);
  vm_dispatch("say", 2, vm_invoke(a, 0), vm_invoke(b, 0));
  
  return 0;  
}
