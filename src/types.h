#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <llvm/ADT/StringMap.h>
#include <gc/gc_cpp.h>
#include <map>
#include <string>

using namespace std;
using namespace llvm;

struct P6opaque;

class Stash : public gc {
 public:
  Stash() { }
  StringMap<P6opaque*> values;
  Stash* OUTER;

  P6opaque* find(string name) {
    StringMap<P6opaque*>::iterator it = values.find(name);
    if (it == values.end()) {
      if (OUTER == NULL) {
        throw "Error Value not found";
      }
      else {
        return OUTER->find(name);
      }
    }
    else {
      return it->second;
    }
  }
};


class Kernel : public gc_cleanup {
 private: 
  static Kernel _instance;
  Stash *lex_pad;
  Kernel() { }
  ~Kernel() { }

  Kernel(const Kernel&);                 // Prevent copy-construction
  Kernel& operator=(const Kernel&);      // Prevent assignment

 public:
  static Stash* top();
  static void push();
  static void pop();

  static Kernel& getInstance();
};



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
  vector<P6opaque*> *parents;
  void *content_ptr;
  StringMap<P6opaque*> *properties;
  StringMap<mt_entry*> *method_table;
};


#ifdef __cplusplus
}
#endif

#endif // SRC_TYPES_H

