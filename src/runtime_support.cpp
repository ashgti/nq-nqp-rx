#include <iostream>
#include <string>
#include <stack>
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

class _Stash;

class Kernel {
 private: 
  static Kernel _instance;
  stack<_Stash> lex_pads;
 public:
  static const _Stash& getCurrent();

}

static Kernel Kernel::_instance;

class _Str;
class _Role;
class _ClassHOW;
class _Hash;

class P6opaque {
 private:

 protected:
  map<string, P6opaque*> properties;
  const std::string &_class;

 public:
  /* Constructors */
  P6opaque(const std::string& _class);

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
  
 public:
  /* Constructors */
  _Mu(string arg = "Mu()") : 
      P6opaque(arg) {
  }

  ~_Mu() { }

  /* Some general methods */
  _Str* Str();

  virtual P6opaque* create() {
    return new _Mu();
  }

  static P6opaque* _new(_Hash* args = NULL) {
    P6opaque* candidate = _Mu::_CREATE("*");
    return candidate->_bless(args);
  }

  virtual void _BUILD();

  virtual void _BUILDALL(_Hash* hash) {
  
  }

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

  virtual P6opaque* _bless(_Hash* hash); 
};

//_Mu* _GLOBAL_Mu = new _Mu;

class _Stash : public _Mu {
 private:
  map<string, P6opaque*> values;
 public:
  _Stash(string name="Stash()") : _Mu(name) { }
  P6opaque* operator ()(const std::string& s) {
//    OUTER::
//    !file
//    !line
//    !id
    P6opaque *result = this->get_attr(s);

    if (result == NULL) {
      result = new _Mu;
      this->set_attr(s, result);
    }

    return result;
  }

  void insert(pair<string, P6opaque*> arg) {
    this->set_attr(arg.first, arg.second);
  }
};

class _Any : public _Mu {
 public:
  _Any(string arg = "Any()") : 
      _Mu(arg) {
  }
};

//_Mu* _GLOBAL_Any = new _Any();

class _Whatever : public _Any {
 private:
 public:

};

//_Mu* _GLOBAL_Whatever = new _Whatever();

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
  std::string *value;

 public:
  _Str(string val = "Str()", string name = "Str()") : 
      _Any(name), value(new string(val)) {
  }

  ~_Str() {
    if (value) {
      delete value;
    }
  }

//  static _Str* create(string value) {
//    return new _Str("Str()", value);
//  }

  string* str() {
    return value;
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

*/

class _Hash : _Any {
 private:
  map<string, P6opaque*> values;

 public:
  _Hash(string name = "Hash()") : _Any(name) { }

  void set(string name, P6opaque* val) {
    values[name] = val;
  }

  P6opaque* get(string name) {
    return values[name];
  }
};

extern "C"
_Mu* _say(_Stash* curpad, int num_args, ...) {
  va_list vl;
  _Mu* val;
  va_start(vl, num_args);

  cerr << "Starting to _say" << endl; 
  
  for (int i = 0; i < num_args; i++) {
    cerr << "i: " << i << endl;
    val = va_arg(vl, _Mu*);
    cerr << "argp " << val;
    _Str* str = val->Str();
    cerr << " and " << str;
 //   cout << val->Str()->str();
  }
  
  cout << "\n";

  P6opaque *mu = (*curpad)("Mu");
  return static_cast<_Mu*>(static_cast<_Mu*>(mu)->_new());
}

_Stash& settings() {
  _Stash* settings = new _Stash; 

  P6opaque* glb = new _Mu;
  glb->set_attr(".HOW", new _ClassHOW());
  static_cast<_Stash*>(settings)->insert(pair<string, P6opaque*>("Mu", glb));

  glb = new _Str;
  glb->set_attr(".HOW", new _ClassHOW());
  static_cast<_Stash*>(settings)->insert(pair<string, P6opaque*>("Str", glb));

  glb = new _Any;
  glb->set_attr(".HOW", new _ClassHOW());
  static_cast<_Stash*>(settings)->insert(pair<string, P6opaque*>("Any", glb));

  return *settings;
}

int main() {
  try {
    _Stash &curpad = settings();
    P6opaque *any = curpad("Any"); 
    P6opaque *instance = static_cast<_Any*>(any)->_new();
    _say(&curpad, 1, instance);
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

P6opaque::P6opaque(const std::string& _class) : _class(_class) {
}

_Str* _Mu::Str() {
  _Str* result = (_Str*)get_attr(".WHAT");

  if (result) {
    cerr << "Str was good" << endl;
  } 
  else {
    cerr << "Str was bad " << result << endl;
  }
  return static_cast<_Str*>(get_attr(".WHAT"));
}

P6opaque* _Mu::_CREATE(_Str* repr) {
  return _Mu::_CREATE(*repr->str());
}

P6opaque* _Mu::_bless(_Hash* hash) {
  // BUILDALL
  _Hash* parents_list = (_Hash*)get_attr(".^parents");
  parents_list->set(get_class(), _Str::create(get_class()));
  _BUILDALL(hash);
  return this;
}


void _Mu::_BUILD() {
  // this->set_attr()
  set_attr(".WHAT", new _Str(get_class()));      

  cerr << "BUILD called" << endl;
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


