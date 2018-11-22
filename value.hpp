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
// Floating point value
using floatValue = double;
// Function value
using funcValue = funcDecl*;

// Object address
class addrValue {
public:
    // The store in which the object resides
    int store;
    // The definition of the object
    Decl* def;
};

// Value computed by an expression
class Value {
public:
    // Kinds of values
    enum Kind{
        myNonVal,       // non-value
        myIntVal,       // integer
        myFloatVal,     // floating point
        myFuncVal,      // function
        myAddrVal,      // address
    };

    // Constructs an indeterminate value
    Value();
    // Constructs a boolean value
    explicit Value(bool b);
    // Constructs an integer value
    explicit Value(int n);
    // Constructs an integer value
    explicit Value(intValue n);
    // Constructs a floating point value
    explicit Value(float n);
    // Constructs a floating point value
    explicit Value(floatValue n);
    // Constructs a function value
    explicit Value(funcValue f);
    // Constructs a function value
    explicit Value(addrValue const& a);

private:
    // Where the actual value is stored
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
    // Returns the kind of the value
    Kind getValueKind() const { return myKind; }
    // Returns whether value is indeterminate
    bool isIndeterm() const { return myKind == myNonVal; }
    // Returns whether value is an integer
    bool isInt() const { return myKind == myIntVal; }
    // Returns whether value is floating point
    bool isFloat() const { return myKind == myFloatVal; }
    // Returns whether value is a function
    bool isFunc() const { return myKind == myFuncVal; }
    // Returns whether value is an address
    bool isAddr() const { return myKind == myAddrVal; }

    // Accessors
    // Returns the integer value
    intValue getInt() const;
    // Returns the floating point value
    floatValue getFloat() const;
    // Returns the function value
    funcValue getFunction() const;
    // Returns the address value
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
