/*
 * =====================================================================================
 *
 *       Filename:  dispatcher.cpp
 *
 *    Description:  Dispatch functions
 *
 *        Version:  1.0
 *        Created:  04/19/2010 22:25:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */

extern "C"
nqp_vm_dispatch() {

}



int main() {
  nqp_vm vm = get_nqp_vm();
  TO_B(vm->dispatch("say", INT(1), ARRAY("A", "B", 3)));


}
