/* type.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

class Printer;

// The general type class
class Type {
public:
    // Kinds of types
    enum Kind{
        myBool,
        myInt,
        myFloat,
        myRef,
        myFunc,
    };

protected:
    Type(Kind k);

private:
    Kind myKind;

public:
    // Queries
    Kind getType() const { return myKind; }
    bool isBool() const { return myKind == myBool; }
    bool isInt() const { return myKind == myInt; }
    bool isFloat() const { return myKind == myFloat; }
    bool isReference() const { return myKind == myRef; }
    bool isFunction() const { return myKind == myFunc; }
    bool isSameType(Type const* inputType) const;
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
class unaryType : public Type {
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
public:
    Type* const* getFirst() const { return firstOp; }
    Type* const* getLast() const { return lastOp; }
};
inline knaryType::knaryType(Kind k, std::initializer_list<Type*> ops) :
    Type(k), firstOp(ops.begin()), lastOp(ops.end()) {}

// Types

// The boolean type
class boolType : public nullaryType {
public:
    boolType();
};
inline boolType::boolType() :
    nullaryType(myBool) {}

// The integer type
class intType : public nullaryType {
public:
    intType();
};
inline intType::intType() :
    nullaryType(myInt) {}

// The float type
class floatType : public nullaryType {
public:
    floatType();
};
inline floatType::floatType() :
    nullaryType(myFloat) {}

// The reference type
class refType : public unaryType {
public:
    refType(Type* op);
};
inline refType::refType(Type* op) :
    unaryType(myRef, op) {}

// The function type
class funcType : public knaryType {
public:
    funcType(std::initializer_list<Type*> ops);
};
inline funcType::funcType(std::initializer_list<Type*> ops) :
    knaryType(myFunc, ops) {}

//Operations
void print(Printer& p, Type const* t);

std::ostream& operator<<(std::ostream& os, Type const* t);
