/*
 * =====================================================================================
 *
 *       Filename:  ast_pass.cpp
 *
 *    Description:  AST Passes, like type inference 
 *
 *        Version:  1.0
 *        Created:  04/16/2010 09:17:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "ast_pass.h"

namespace nqp {
  
void TypeInferencePass(Node *root_node) {
  // TODO: This would be useful, I can know if I can use built in types, like int's and floats
  // or if i need to use my Int and Num object
}

} // end namespace nqp

