#ifndef SRC_RUNTIME_SUPPORT_H
#define SRC_RUNTIME_SUPPORT_H

/*
 * =====================================================================================
 *
 *       Filename:  runtime_support.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/20/2010 14:42:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <cstdarg>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Setup function */
void nqp_init();
/* settings function to define global settings */
void settings();

/* Builtin say functions */
P6opaquePtr _say(Stash* lex);
P6opaquePtr _puts(Stash* lex);
P6opaquePtr _infix_add(Stash* lex);
P6opaquePtr _infix_sub(Stash* lex);
P6opaquePtr _infix_mul(Stash* lex);
P6opaquePtr _infix_div(Stash* lex);
P6opaquePtr _infix_stitch(Stash* lex);
P6opaquePtr _prefix_stitch(Stash* lex);
P6opaquePtr _prefix_add(Stash* lex);

/* Construct a nqp integer */
P6opaquePtr  str_new(N_STR v, uint64_t len = ULLONG_MAX);
P6opaquePtr  bool_new(N_BOOL v);
P6opaquePtr  int_new(N_INT v);
P6opaquePtr  num_new(N_NUM v);

P6opaquePtr  array_new();
void         array_push(P6opaquePtr ar, P6opaquePtr val);
P6opaquePtr  array_pop(P6opaquePtr ar);
P6opaquePtr  array_at(P6opaquePtr ar, unsigned int key);
unsigned int array_size(P6opaquePtr ar);
P6opaquePtr  array_iter(P6opaquePtr ar);

P6opaquePtr  hash_new();
void         hash_push(P6opaquePtr hash, P6opaquePtr key);
P6opaquePtr  hash_remove(P6opaquePtr hash, P6opaquePtr key);
P6opaquePtr  hash_find(P6opaquePtr, P6opaquePtr key);
unsigned int hash_size(P6opaquePtr hash);
P6opaquePtr  hash_iter(P6opaquePtr hash);

void        vm_stack_push();
void        vm_stack_pop();
void        vm_stack_set_package(const char* name);
P6opaquePtr vm_stack_create_val(const char* name);
P6opaquePtr vm_stack_find(const char* name);
/* Utility Function */
void        print_stack(unsigned int lex = 1); // Prints the current lexical scope (lex = 1), or the current dynamic scope (lex = 0) 


/* Construct a sub object, for using nqp */
P6opaquePtr construct_sub(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...); // ends in a name list
P6opaquePtr construct_closure(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...); // ends in a name list

/* VM Ops: */
P6opaquePtr vm_invoke(P6opaquePtr sub_obj, unsigned int argc, ...);
P6opaquePtr vm_dispatch(const char* sub_name, unsigned int argc, ...);

/* Internal ops */
N_STR internal_to_str(P6opaquePtr val);
N_NUM internal_to_num(P6opaquePtr val);

#ifdef __cplusplus
}
#endif

#endif // SRC_RUNTIME_SUPPORT_H

