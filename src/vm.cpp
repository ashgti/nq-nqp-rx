/*
 * =====================================================================================
 *
 *       Filename:  vm.cpp
 *
 *    Description:  The actual VM that is going to sit on top of the llvm.
 *
 *        Version:  1.0
 *        Created:  04/19/2010 19:48:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */


extern "C" {

void fast_add(P6opaque* )

}

namespace nqp {

// One global core, should be thread safe (when its time to care about threads)
class Core {
 public:
  static Core *shared;
};

// One VM per thread
class VM {
 public:
  static VM *main; // main VM thread
};

} // end namespace nqp

