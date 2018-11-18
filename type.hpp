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
        myBoolType,
        myIntType,
        myFloatType,
        myRefType,
        myFuncType,
    };

protected:
    Type(Kind k);

private:
    Kind myKind;

public:
    // Queries
    Kind getTypeKind() const { return myKind; }
    char const* getTypeName() const;
    bool isBool() const { return myKind == myBoolType; }
    bool isInt() const { return myKind == myIntType; }
    bool isIntegral() const { return isBool() || isInt(); }
    bool isFloat() const { return myKind == myFloatType; }
    bool isReference() const { return myKind == myRefType; }
    bool isFunction() const { return myKind == myFuncType; }
    bool isObject() const { return myKind != myRefType; }
    bool isArithmetic() const { return isInt() || isFloat(); }
    bool isSameAs(Type const* inputType) const;
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
    Type* getChild() const { return myOp; }
};
inline unaryType::unaryType(Kind k, Type* op) :
    Type(k), myOp(op) {}

// For statements with k operands
class karyType : public Type {
protected:
    karyType(Kind k);
    karyType(Kind k, std::initializer_list<Type*> list);
    karyType(Kind k, std::vector<Type*> const& vec);
    karyType(Kind k, std::vector<Type*>&& vec);

private:
    std::vector<Type*> myOps;

public:
    Type** begin() { return myOps.data(); }
    Type** end() { return myOps.data() + myOps.size(); }
    Type* const* begin() const { return myOps.data(); }
    Type* const* end() const { return myOps.data() + myOps.size(); }
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
    funcType(std::initializer_list<Type*> list);
    funcType(std::vector<Type*> const& vec);
    funcType(std::vector<Type*>&& vec);
    std::size_t getParamCount() const { return getChildren().getSize() - 1; }
    NodeRange<Type> getParameterTypes() { return getChildren().getRevTail(); }
    NodeRange<Type const> getParameterTypes() const { return getChildren().getRevTail(); }
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

