#ifndef NQNQP_BUILTIN_MU_H_
#define NQNQP_BUILTIN_MU_H_

#include "builtin/Attribute.hpp"
#include "builtin/Method.hpp"

namespace nqp {

/*
 * Some default methods that need to be implemented: 
 * notdef BUILDALL new Bool print say defined BUILD REJECTS clone WHICH CREATE Capture PARROT bless WHENCE WHERE list
 */


class Mu {
 publi:
  Mu invoke(std::string, std::vector<Mu>);
 protected:
 private:
  std::map<std::string, Attribute> vars;
  std::map<std::string, Method> methods;
};

} // namespace nqp

#endif // NQNQP_BUILTIN_MU_H_
