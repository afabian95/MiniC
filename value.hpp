/* value.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <cassert>
#include <iosfwd>

class funcDecl;
class varDecl;
class Decl;

// Integer value
using intValue = long long;
// Float value
using floatValue = double;
// Function value
using funcValue = funcDecl*;

class addrValue {
public:
    int store;
    Decl* def;
};

class Value {
public:
    // Kinds of values
    enum Kind{
        myNonVal,
        myIntVal,
        myFloatVal,
        myFuncVal,
        myAddrVal,
    };

    Value();
    explicit Value(bool b);
    explicit Value(int n);
    explicit Value(intValue n);
    explicit Value(float n);
    explicit Value(floatValue n);
    explicit Value(funcValue f);
    explicit Value(addrValue const& a);

private:
    union Data {
        Data() = default;
        Data(intValue n) : num(n) {}
        Data(floatValue n) : fp(n) {}
        Data(funcValue f) : func(f) {}
        Data(addrValue a) : addr(a) {}

        intValue num;
        floatValue fp;
        funcValue func;
        addrValue addr;
    };

    Kind myKind;
    Data myData;

public:
    // Kind
    Kind getValue() const { return myKind; }
    bool isIndeterm() const { return myKind == myNonVal; }
    bool isInt() const { return myKind == myIntVal; }
    bool isFloat() const { return myKind == myFloatVal; }
    bool isFunc() const { return myKind == myFuncVal; }
    bool isAddr() const { return myKind == myAddrVal; }

    // Accessors
    intValue getInt() const;
    floatValue getFloat() const;
    funcValue getFunction() const;
    addrValue const& getAddress() const;
};
inline Value::Value() :
    myKind(myNonVal) {}
inline Value::Value(bool b) :
    Value((intValue)b) {}
inline Value::Value(int n) :
    Value((intValue)n) {}
inline Value::Value(intValue n) :
    myKind(myIntVal), myData(n) {}
inline Value::Value(float n) :
    Value((floatValue)n) {}
inline Value::Value(floatValue n) :
    myKind(myFloatVal), myData(n) {}
inline Value::Value(funcValue f) :
    myKind(myFuncVal), myData(f) {}
inline Value::Value(addrValue const& a) :
    myKind(myAddrVal), myData(a) {}
inline intValue Value::getInt() const {
  assert(isInt());
  return myData.num;
}
inline floatValue Value::getFloat() const {
  assert(isFloat());
  return myData.fp;
}
inline funcValue Value::getFunction() const {
  assert(isFunc());
  return myData.func;
}
inline addrValue const& Value::getAddress() const {
  assert(isAddr());
  return myData.addr;
}

// Operations
std::ostream& operator<<(std::ostream& os, Value const& v);
