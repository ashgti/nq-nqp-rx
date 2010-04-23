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
// struct container;

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

 public:
  NqpVM();
  ~NqpVM();

  // The main VM Component, one per thread, in theory
  static NqpVM* main_vm;

  Stash* top();
  Stash* push();
  void pop();

  P6opaque* dispatch(P6opaque* code, int argc, ...);
  P6opaque* dispatch(const char* name, int argc, ...);

  static NqpVM* current(void);
};

#define GET_VM() (nqp::NqpVM::current())

#ifdef __cplusplus
extern "C" {
#endif

typedef P6opaque* (*MethodPtr)(Stash*);
typedef P6opaque* (*SubMethodPtr)(Stash*);
typedef P6opaque* (*SubPtr)(Stash*);
typedef P6opaque* (*PhaserPtr)(Stash*);

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
  vector<string> sig_names;
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
  scalar  = 0,
  hash    = 1,
  array   = 2,
  code    = 3
};

enum arg_type_t {
  named     = 0,
  requied   = 1,
  optional  = 2
};

struct container {
  container_type_t type;
  P6opaque *val;
  // Type constraints?
};

struct signature_t {
  int argc;
  container *argv;
};

/* 
struct method_entry { 
  signature_t sig_ref;
  Ptr cfunc*;
}
*/

struct ArgsTy : public gc {
  vector<P6opaque *> args;
};


#ifdef __cplusplus
}
#endif

} // end namespace nqp

#endif // SRC_TYPES_H

