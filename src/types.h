#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <llvm/ADT/StringMap.h>
#include <gc/gc_cpp.h>
#include <map>
#include <vector>
#include <string>

using namespace std;
using namespace llvm;

namespace nqp { 

struct P6opaque;

class Stash : public gc {
 public:
  Stash();
  StringMap<P6opaque*> values;
  Stash* OUTER;

  P6opaque* find(string name);
};

class NqpCore : public gc {
 public:
  static NqpCore *shared;
};

#define GET_CORE() (NqpCore::shared)

class NqpVM : public gc_cleanup {
 private: 
  Stash* lex_pad;
  NqpVM();
  ~NqpVM();

 public:
  // The main VM Component, one per thread, in theory
  static NqpVM* main;

  Stash* top();
  Stash* push();
  void pop();

  static inline NqpVM* current(void);
};

#define GET_VM() (nqp::NqpVM::current())

#ifdef __cplusplus
extern "C" {
#endif

typedef P6opaque* (*MethodPtr)(Stash*, P6opaque*, ...);
typedef P6opaque* (*SubMethodPtr)(Stash*, P6opaque*, ...);
typedef P6opaque* (*SubPtr)(Stash*, ...);
typedef P6opaque* (*PhaserPtr)(Stash*, ...);

enum sub_type_t {
  sub = 0,
  method = 1,
  submethod = 2,
  phaser = 3
};

/* method entry */
struct mt_entry {
  sub_type_t sub_type;
  Stash* scope;
  union {
    MethodPtr method;
    SubMethodPtr submethod;
    SubPtr sub;
  };
  signed int argc;
};

enum built_in_types_t {
  mu_type = 0,
  int_type,
  num_type,
  string_type,
  bool_type,
  other_type
};

struct P6opaque : public gc {
  built_in_types_t klass_type;
  const char *klass_name;
  std::vector<P6opaque*> *parents;
  void *content_ptr;
  StringMap<P6opaque*> *properties;
  StringMap<mt_entry*> *method_table;
};

enum container_type_t {
  scalar,
  hash,
  array,
  code
};

enum arg_type {
  named,
  requied,
  optional,
}

struct container {
  container_type_t type;
  P6opaque *val;
  int type;
  int constraint;
};

struct param_capture {
  int argc;
  container *argv;
};

struct signature {
  int argc;
  container *argv;
}

struct method_entry { 
  signature_t sig_ref;
  Ptr cfunc*
}

struct ArgsTy : gc {
  StringMap<P6opaque *> kwargs;
  vector<P6opaque *> args;
};


#ifdef __cplusplus
}
#endif

} // end namespace nqp

#endif // SRC_TYPES_H

