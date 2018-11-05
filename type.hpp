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
    bool isSameType(Type const* inputType) const;
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
class knaryType : public Type {
protected:
    knaryType(Kind k, std::initializer_list<Type*> ops);
private:
    Type* const* firstOp;
    Type* const* lastOp;
    std::initializer_list<Type*> allOps;
public:
    Type* const* getFirst() const { return firstOp; }
    Type* const* getLast() const { return lastOp; }
    std::initializer_list<Type*> getChildren() const { return allOps; }
};
inline knaryType::knaryType(Kind k, std::initializer_list<Type*> ops) :
    Type(k), firstOp(ops.begin()), lastOp(ops.end()), allOps(ops) {}

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
class funcType : public knaryType {
public:
    funcType(std::initializer_list<Type*> ops);
    funcType(std::vector<Type*> const& ops);
    funcType(std::vector<Type*>&& ops);
    std::size_t getParamCount() const { return getLast() - getFirst(); }
    NodeRange<Type> getParameterTypes();
    NodeRange<Type const> getParameterTypes() const;
    Type* getReturnType();
    Type const* getReturnType() const;

};
inline funcType::funcType(std::initializer_list<Type*> ops) :
    knaryType(myFuncType, ops) {}

//Operations
bool isSame(Type const* a, Type const* b);

void printType(Printer& p, Type const* t);

std::ostream& operator<<(std::ostream& os, Type const& t);

