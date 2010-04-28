#ifndef SRC_VM_H
#define SRC_VM_H
/*
 * =====================================================================================
 *
 *       Filename:  vm.h
 *
 *    Description:  VM 
 *
 *        Version:  1.0
 *        Created:  04/27/2010 13:34:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Harrison (ash), ash@greaterthaninfinity.com
 *        Company:  
 *
 * =====================================================================================
 */

#include "types.h"
#include <llvm/ADT/StringMap.h>
#include <gc/gc_cpp.h>
#include <map>
#include <vector>
#include <string>

namespace nqp { 


class NqpCore : public gc {
 public:
  static NqpCore *shared;
};

#define GET_CORE() (NqpCore::shared)

class NqpVM : public gc_cleanup {
 private: 
  Stash* lex_pad;

 public:
  NqpVM();
  ~NqpVM();

  // The main VM Component, one per thread, in theory
  static NqpVM* main_vm;

  Stash* top();
  Stash* push();
  void pop();

  P6opaque* dispatch(P6opaque* code, unsigned int argc, ...);
  P6opaque* dispatch(const char* name, unsigned int argc, ...);
  P6opaque* vdispatch(P6opaque* code, unsigned int argc, va_list argv);
  P6opaque* vdispatch(const char* name, unsigned int argc, va_list argv);

  static NqpVM* current(void);
};

#define GET_VM() (nqp::NqpVM::current())

}

#endif // SRC_VM_H

