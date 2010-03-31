#include <iostream>
#include <string>
#include <map>
#include <cstdarg>
#include <exception>

using namespace std;

class MethodNotFoundException { //: public exception {
 private:
  string arg;
 public:
  MethodNotFoundException(string arg = "") : arg(arg) { }
  ~MethodNotFoundException() { }
  virtual const char* what() const throw() {
    return (string("abc ") + arg).c_str();
  }
};

class _Str;
class _Role;
class _ClassHOW;
class _Hash;

class P6opaque {
 private:
  map<string, P6opaque*> properties;
  const std::string &_class;

 protected:

 public:
  /* Constructors */
  P6opaque(const std::string& _class) : 
      _class(_class) { }

  /* methods */
  P6opaque* dispatch(std::string arg) {
    P6opaque* result = properties[arg];
    if (result) {
      return result;
    }
    else {
      throw MethodNotFoundException(arg);
    }
  }

  const std::string& get_class() {
    return _class;
  }
  
  P6opaque* get_attr(std::string attr_name) {
    return properties[attr_name];
  }

  void set_attr(std::string attr_name, P6opaque* attr) {
    properties[attr_name] = attr;
  }

  virtual P6opaque* _bless(_Hash* hash) = 0;
};

class _Mu : public P6opaque {
 protected:
  /* Attributes */
  _Mu* HOW;
  
 public:
  /* Constructors */
  _Mu(string arg = "Mu()") : 
      P6opaque(arg) {
  }

  /* Some general methods */
  _Str* Str();

  virtual P6opaque* create() {
    return new _Mu();
  }

  static P6opaque* _new(_Hash* args = NULL) {
    P6opaque* candidate = _Mu::_CREATE("*");
    return candidate->_bless(args);
  }

  virtual P6opaque& get_HOW() {
    return *HOW;
  }

  virtual void _BUILD();
  virtual P6opaque* _CREATE() {

    return new _Mu();
  }

  static P6opaque* _CREATE(string repr) {
    if ("*" == repr) {
      return new _Mu("Mu()");
    }
    return NULL;
  }

  static P6opaque* _CREATE(_Str* repr);

  virtual P6opaque* _bless(_Hash* hash) {
    // BUILDALL
    return this;
  }
};

_Mu* _GLOBAL_Mu = new _Mu;

/* do i want a kernel object? 
class _Kernel : public _Mu {
 private:
 public:
  _Kernel(string name="Kernel()");
};

_Mu* _GKernel = new _Kernel();
*/

class _Any : public _Mu {
 public:
  _Any(string arg = "Any()") : 
      _Mu(arg) {
  }
};

_Mu* _GLOBAL_Any = new _Any();

class _Whatever : public _Any {
 private:
  _Mu* HOW;
 public:

};

_Mu* _GLOBAL_Whatever = new _Whatever();

/*

class _Role : public _Any {
 public:
  _Role(string arg = "Role()") :
      _Any(arg) {
  }
};

*/

/*
class _Iterable : public _Any {
 public:
  _Iterable(string arg = "Iterable()") : 
};
*/

class _Str : public _Any {
 private:
  std::string* value;
  static _Mu* HOW;

 public:
  _Str(string arg = "Str()") : _Any(arg) {
  }

  _Str(string arg = "Str()", std::string value = "Str()") : 
      _Any(arg), value(new string(value)) {
  }

  ~_Str() {
    delete value;
  }

  static _Str* create(string value) {
    return new _Str("Str()", value);
  }

  string& str() {
    return *value;
  }
};

/*
class _Int : public _Any {
 private:
  long long value;

 public:
  _Int() :
      _Mu("Int()") {
  }

  _Int(long long value) : 
      _Mu("Int()"), value(value) {
  }
}; */

/* 
class _Num : public _Any {
};

*/

class _ClassHOW : public _Mu {
 public:
  _ClassHOW(string arg="ClassHOW()") : _Mu(arg) { }
};

/*
class _RoleHOW : public _Mu {
};

class _GrammarHOw : public _Mu {
};

class _Grammar : public _Mu {
};
*/

//class _Bool : public _Any {
// private:
//  bool value;
// public:
//
//};

/*
_Role _Code = _Role::create("Code()",
      new map<string, P6opaque*>("string", )
    );
*/

/* role Code */
/*
class _Code : public _Any {
};

class _Block : public _Any {
};

class _Parcel : public _Any {
};

enum _Routine_t {
  _Sub,
  _Method,
  _Submethod,
  _Macro,
};

class _Routine : public _Code {

};

class _Hash : _Any {
};

*/

_Mu* _say(int num_args, ...) {
  _Mu* val;
  va_list vl;
  va_start(vl, num_args);
  
  for (int i = 0; i < num_args; i++) {
    cout << val->Str()->str();
  }
  
  cout << "\n";

  return new _Mu;
}

int main() {
  try {
    P6opaque *instance = _GLOBAL_Any->_new();
    _say(1, instance);
    //P6opaque *b = a->dispatch(".^methods"); // .^methods should return an Array of methods.
    //cout << b->dispatch(".WHAT"); // .WHAT returns a Str which says "Array()".
    //cout << b;
  }
  catch (MethodNotFoundException e) {
    cerr << "MethodNotFoundException: " << e.what() << endl;
  }
  catch (...) {
    cerr << "Uncaught exception" << endl;
    return -1;
  }
  return 0;
}

_Str* _Mu::Str() {
  return _Str::create("Mu()");
}

P6opaque* _Mu::_CREATE(_Str* repr) {
  return _Mu::_CREATE(repr->str());
}


//P6opaque& _Mu::getHOW() {
//}

// P6opaque& _Mu::_get_HOW() {
//  if (HOW == NULL) {
//    HOW = new _ClassHOW();
//  }
//
//  return *HOW;
//}


