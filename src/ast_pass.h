/*
 * =====================================================================================
 *
 *       Filename:  ast_pass.h
 *
 *    Description:  Header for AST passes
 *
 *        Version:  1.0
 *        Created:  04/19/2010 22:56:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef NQP_AST_PASS_H_
#define NQP_AST_PASS_H_ 

#include "node.h"

namespace nqp {
  
void TypeInferencePass(Node *root_node);

} // end namespace nqp

#endif // NQP_AST_PASS_H_ 

