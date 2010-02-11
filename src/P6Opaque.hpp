#include "llvm/ADT/StringMap.h"

namespace nqp {

/* P6opaque object is a very simple struct used to contain our basic objects.
 * this class is very liable to evolve as the project grows in complexity. */
struct P6opaque {
 private:
 protected:
 public:
  llvm::StringMap<Value*> properties;
  std::string _class;
};

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

