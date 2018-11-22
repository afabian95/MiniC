/* type.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "tree.hpp"
#include "value.hpp"

class Printer;

// The general type class
class Type {
public:
    // Kinds of types
    enum Kind{
        myBoolType,     // boolean type
        myIntType,      // integer type
        myFloatType,    // floating point type
        myRefType,      // reference type
        myFuncType,     // function type
    };

protected:
    Type(Kind k);

private:
    Kind myKind;

public:
    // Queries
    // Returns the kind of the type
    Kind getTypeKind() const { return myKind; }
    // Returns the spelling of the kind
    char const* getTypeName() const;
    // Returns if type is a boolean
    bool isBool() const { return myKind == myBoolType; }
    // Returns if type is an integer
    bool isInt() const { return myKind == myIntType; }
    // Returns if type is integral
    bool isIntegral() const { return isBool() || isInt(); }
    // Returns if type is floating point
    bool isFloat() const { return myKind == myFloatType; }
    // Returns if type is a reference
    bool isReference() const { return myKind == myRefType; }
    // Returns if type is a function
    bool isFunction() const { return myKind == myFuncType; }
    // Returns if type is an object
    bool isObject() const { return myKind != myRefType; }
    // Returns if type is arithmetic
    bool isArithmetic() const { return isInt() || isFloat(); }
    // Returns whether a type is the same as another
    bool isSameTypeAs(Type const* inputType) const;
    // Returns whether a type is a reference to another
    bool isReferenceTo(Type const* inputType) const;
};
inline Type::Type(Kind k) :
    myKind(k) {}

// For types with no operands
class nullaryType : public Type {
protected:
   nullaryType(Kind k);
};
inline nullaryType::nullaryType(Kind k) :
    Type(k) {}

// For types with one operand
class unaryType : public Type{
protected:
    unaryType(Kind k, Type* op);
private:
    Type* myOp;
public:
    // Returns the only operand
    Type* getChild() const { return myOp; }
};
inline unaryType::unaryType(Kind k, Type* op) :
    Type(k), myOp(op) {}

// For statements with k operands
class karyType : public Type {
protected:
    // Initialized with no parameters
    karyType(Kind k);
    // Initialized with a list of parameters
    karyType(Kind k, std::initializer_list<Type*> list);
    karyType(Kind k, std::vector<Type*> const& vec);
    karyType(Kind k, std::vector<Type*>&& vec);

private:
    std::vector<Type*> myOps;

public:
    // Returns the first operand
    Type** begin() { return myOps.data(); }
    Type* const* begin() const { return myOps.data(); }
    // Returns the last operand
    Type** end() { return myOps.data() + myOps.size(); }
    Type* const* end() const { return myOps.data() + myOps.size(); }
    // Returns a range of operands
    NodeRange<Type> getChildren() { return { begin(), end()}; }
    NodeRange<Type const> getChildren() const { return { begin(), end()}; }
};
inline karyType::karyType(Kind k) :
    Type(k) {}
inline karyType::karyType(Kind k, std::initializer_list<Type*> list) :
    Type(k), myOps(list) {}
inline karyType::karyType(Kind k, std::vector<Type*> const& vec) :
    Type(k), myOps(vec) {}
inline karyType::karyType(Kind k, std::vector<Type*>&& vec) :
    Type(k), myOps(std::move(vec)) {}

// Types

// The boolean type
class boolType : public nullaryType {
public:
    boolType();
};
inline boolType::boolType() :
    nullaryType(myBoolType) {}

// The integer type
class intType : public nullaryType {
public:
    intType();
};
inline intType::intType() :
    nullaryType(myIntType) {}

// The float type
class floatType : public nullaryType {
public:
    floatType();
};
inline floatType::floatType() :
    nullaryType(myFloatType) {}

// The reference type
class refType : public unaryType {
public:
    refType(Type* op);
    Type* getObjectType() const { return getChild(); }
};
inline refType::refType(Type* op) :
    unaryType(myRefType, op) {}

// The function type
class funcType : public karyType {
public:
    // Constructs the function type from a list of parameters
    funcType(std::initializer_list<Type*> list);
    funcType(std::vector<Type*> const& vec);
    funcType(std::vector<Type*>&& vec);
    // Returns the number of parameters
    std::size_t getParamCount() const { return getChildren().getSize() - 1; }
    // Returns the parameter types
    NodeRange<Type> getParameterTypes() { return getChildren().getRevTail(); }
    NodeRange<Type const> getParameterTypes() const { return getChildren().getRevTail(); }
    // Returns the return type
    Type* getReturnType() { return getChildren().getBack(); }
    Type const* getReturnType() const { return getChildren().getBack(); }

};
inline funcType::funcType(std::initializer_list<Type*> list) :
    karyType(myFuncType, list) {}
inline funcType::funcType(std::vector<Type*> const& vec) :
    karyType(myFuncType, vec) {}
inline funcType::funcType(std::vector<Type*>&& vec) :
    karyType(myFuncType, vec) {}

//Operations
bool isSameType(Type const* a, Type const* b);

void printType(Printer& p, Type const* t);

std::ostream& operator<<(std::ostream& os, Type const& t);

