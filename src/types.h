#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <llvm/ADT/StringMap.h>
#include <gc/gc_cpp.h>
#include <map>
#include <vector>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

struct P6opaque;
typedef P6opaque* P6opaquePtr;
struct Stash;
struct ParamTy;
typedef ParamTy* ParamTyPtr;

/* Function pointer definitions. */
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
struct mt_entry : public gc {
  sub_type_t sub_type;
  Stash* scope;
  union {
    MethodPtr method;
    SubMethodPtr submethod;
    SubPtr sub;
  };
  ParamTyPtr sig;
};

enum BuiltInTypes {
  kBUILT_IN_MU = 0,
  kBUILT_IN_INT,
  kBUILT_IN_NUM,
  kBUILT_IN_STRING,
  kBUILT_IN_BOOL,
  kBUILT_IN_ARRAY,
  kBUILT_IN_HASH,
  kBUILT_IN_CODE,
  kBUILT_IN_SUB,
  kOTHER
};

struct P6opaque : public gc {
  BuiltInTypes klass_type;
  const char *klass_name;
  std::vector<P6opaque*> *parents;
  void *content_ptr;
  llvm::StringMap<P6opaque*> *properties;
  llvm::StringMap<mt_entry*> *method_table;
};

struct Stash : public gc {
  llvm::StringMap<P6opaque*> values;
  Stash* OUTER;
};

enum ContainerTypes {
  kSCALAR  = 0,
  kHASH    = 1,
  kARRAY   = 2,
  kCODE    = 3
};

enum ParamType {
  kNAMED     = 0,
  kREQUIRED  = 1,
  kOPTIONAL  = 2
};

struct ParameterHolder : public gc {
  ParamType ptype;
  ContainerTypes ctype;
  bool slurpy;
  char* name;
  P6opaquePtr val;
  // Type constraints?
};

struct ParamTy : public gc { 
  unsigned int argc;
  unsigned int expected;
  bool slurpy;
  ParameterHolder* argv;
};

#ifdef __cplusplus
}
#endif

#endif // SRC_TYPES_H

