#include "llvm/ADT/StringMap.h"

// extern "C" {

namespace nqp {

// class Mu;

/* P6opaque object is a very simple struct used to contain our basic objects.
 * this class is very liable to evolve as the project grows in complexity. */
class P6opaque {
 private:

 public:
  /* P6opaque */
  P6opaque(std::string _class) : 
      _class(_class);
  P6opaque(std::string _class, llvm::StringMap<P6opaque*> properties) : 
      _class(_class), properties(properties) { }
  llvm::StringMap<P6opaque*> properties;
  std::string _class;
  // Mu* get_attr(std::string name);
  // void set_attr(std::string name, Mu attr);
  P6opaque* dispatch(std::string arg) {
    P6opaque* result = properties.find(arg);
    if (result) {
      return result;
    }
    else {
      throw MethodNotFoundException(arg);
    }
  }
  // P6opaque* dispatch(std::string arg, P6opaque* args) {
  //  
  // }
};

class Mu : public P6opaque {
 public:
  Mu() : P6opaque("Mu()") { }
  Str* Str() {
    return nqp::Str("Mu()");
  }
};

class Str : public Mu {
 private:
  std::string value;
 public:
  Str() : P6opaque("Str()") { }
  Str(std::string value) : 
      value(value), P6opaque("Str()") { }
};

class Int : public Mu {
 priavte:
  long long value;
 public:
  Int() : P6opaque("Int()") { }
  Int(long long value) : value(value), P6opaque("Int()") { }
};

class Num : public Mu {
};

class Bool : public Mu {
};

class Code {
};


P6opaque *a = new Mu();
P6opaque *b = a->dispatch(".^methods"); // .^methods should return an Array of methods.
cout << b->dispatch(".WHAT"); // .WHAT returns a Str which says "Array()".
cout << b;



}

namespace llvm {

template<bool xcompile> class TypeBuilder<P6opaque, xcompile> {
 public:
  static const StructType *get(LLVMContext &Context) {
    // If you cache this result, be sure to cache it separately
    // for each LLVMContext.
    std::vector<const Type*> st;
    st.push_back(TypeBuilder<types::i<32>, xcompile>::get(Context));
    st.push_back(TypeBuilder<types::i<8>*[], xcompile>::get(Context))

    static const StructType *const result = StructType::get(Context, st);
    return result;  
  }

  // You may find this a convenient place to put some constants
  // to help with getelementptr.  They don't have any effect on
  // the operation of TypeBuilder.
  enum Fields {
    FIELD_PROPERTIES,
    FIELD_CLASS,
  };
}

}  // namespace llvm

