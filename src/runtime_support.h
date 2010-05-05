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

/* Construct a nqp integer */
P6opaquePtr  construct_str(N_STR v);
P6opaquePtr  construct_bool(N_BOOL v);
P6opaquePtr  construct_int(N_INT v);
P6opaquePtr  construct_num(N_NUM v);
P6opaquePtr  construct_array();
P6opaquePtr  construct_hash();

void         array_push(P6opaquePtr ar, P6opaquePtr val);
P6opaquePtr  array_pop(P6opaquePtr ar);
P6opaquePtr  array_at(P6opaquePtr ar, int key);
unsigned int array_size(P6opaquePtr ar);

Stash*      vm_stack_top();
Stash*      vm_stack_push();
void        vm_stack_pop();
P6opaquePtr stack_find(Stash *stack, const char* name);
void        print_stack(Stash*);


/* Construct a sub object, for using nqp */
P6opaquePtr construct_sub(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...); // ends in a name list
P6opaquePtr construct_closure(Stash *lex_scope, SubPtr sub_ptr, unsigned int argc, ...); // ends in a name list

/* VM Ops: */
P6opaquePtr vm_invoke(P6opaquePtr sub_obj, unsigned int argc, ...);
P6opaquePtr vm_dispatch_sub(const char* sub_name, unsigned int argc, ...);
P6opaquePtr vm_disaptch_method(P6opaquePtr self, char* sub_name, unsigned int argc, ...);

#ifdef __cplusplus
}
#endif

#endif // SRC_RUNTIME_SUPPORT_H

