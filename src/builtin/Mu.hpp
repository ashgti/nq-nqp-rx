#ifndef NQNQP_BUILTIN_MU_H_
#define NQNQP_BUILTIN_MU_H_

#include "builtin/Attribute.hpp"
#include "builtin/Method.hpp"

namespace nqp {

class Mu {
 publi:
 protected:
 private:
  std::map<std::string, Attribute> vars;
  std::map<std::string, Method> methods;
};

} // namespace nqp

#endif // NQNQP_BUILTIN_MU_H_
