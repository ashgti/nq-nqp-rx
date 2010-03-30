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

//  const P6opaque& getHOW();
//  static const P6opaque& getHOW();
};

class _Mu : public P6opaque {
 private:
  /* Attributes */
  static P6opaque* HOW;
  
 public:
  /* Constructors */
  _Mu(string arg = "Mu()") : 
      P6opaque(arg) {
  }

  /* Some general methods */
  //bool does(_Role* role);
  //bool can(_Role* role);
  _Str* Str();

  virtual P6opaque* create() {
    return new _Mu();
  }

  static P6opaque* _new(_Hash* args) {
    P6opaque* candidate = _Mu::_CREATE("P6opaque");
    return result->_bless(args);
  }

  virtual P6opaque& get_HOW() {
    return _Mu::_get_HOW();
  }

  static P6opaque& _get_HOW();

  static void _BUILD();
  static P6opaque* _CREATE() {
    return new P6opaque();
  }

  static P6opaque* _CREATE(string repr) {
    if ("*" == repr) {
      return new P6opaque("Mu()");
    }
  }

  virtual P6opaque* _bless(_Hash* hash) {
    //call CREATE
    _Mu* result = _new();
    _Hash::iterator it;
    for (it = _Hash.begin(); it != _Hash.end(); it++) {
      
    }

  }
};

class _Any : public _Mu {
 public:
  _Any(string arg = "Any()") : 
      _Mu(arg) {
  }
};

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

/* 

class _Str : public _Any {
 private:
  std::string& value;

 public:
  _Str() : _Mu("Str()") {
  }

  _Str(std::string value) : 
      _Mu("Str()"), value(value) {
  }

  string& str() {
    return value;
  }
};

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

class _Bool : public _Any {
 private:
  bool value;
 public:

};

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
  va_start(vl,num_args);
  
  for (i = 0; i < num_args; i++) {
    cout << val->Str().str();
  }
  
  cout << "\n";

  return new Mu;
}

int main() {
  try {
    P6opaque *a = new _Any();
    P6opaque *instance = a->_new();
    say(1, instance);
    //P6opaque *b = a->dispatch(".^methods"); // .^methods should return an Array of methods.
    //cout << b->dispatch(".WHAT"); // .WHAT returns a Str which says "Array()".
    //cout << b;
  }
  catch (MethodNotFoundException e) {
    cerr << "MethodNotFoundException: " << e.getErr() << endl;
  }
  catch (...) {
    cerr << "Uncaught exception" << endl;
    return -1;
  }
  return 0;
}

_Str* _Mu::Str() {
  return new _Str("Mu()");
}

P6opague& _Mu::getHOW() {
  return 
}

static P6opaque& _Mu::_get_HOW() {
  if (HOW == NULL) {
    HOW = new _ClassHOW();
  }

  return *HOW;
}


