/* builder.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <vector>

#include "type.hpp"

class Name;
class Type;
class Expr;
class Stmt;
class Decl;
class varDecl;
class funcDecl;
class Symbol;

// The builder class for semantic analysis
class Builder {
public:
    // Name
    Name* getName(char const* str);

private:
    boolType myBoolType;
    intType myIntType;
    floatType myFloatType;

public:
    // Types
    // Returns the boolean type
    Type* getBoolType() { return &myBoolType; }
    // Returns the integer type
    Type* getIntType() { return &myIntType; }
    // Returns the floating point type
    Type* getFloatType() { return &myFloatType; }
    // Returns the reference type
    Type* getRefType(Type* t);
    // Returns the function type
    Type* getFuncType(std::initializer_list<Type*> const& ts);
    Type* getFuncType(std::vector<Decl*> const& params, Type* type);

    // Expressions
    // Returns a new boolean literal
    Expr* makeBool(bool b);
    // Returns the literal true expression
    Expr* makeTrue();
    // Returns the literal false expression
    Expr* makeFalse();
    // Returns a new literal integer expression
    Expr* makeInt(int n);
    // Returns a new literal floating point expression
    Expr* makeFloat(double n);
    // Returns the expression e1 AND e2
    Expr* makeAND(Expr* e1, Expr* e2);
    // Returns the expression e1 OR e2
    Expr* makeOR(Expr* e1, Expr* e2);
    // Returns the expression NOT e1
    Expr* makeNOT(Expr* e1);
    // Returns the expression e1 ? e2 : e3
    Expr* makeCond(Expr* e1, Expr* e2, Expr* e3);
    // Return the identifier to a declaration
    Expr* makeId(Decl* d);

    // Relational expressions
    // Returns the expression e1 == e2
    Expr* makeEq(Expr* e1, Expr* e2);
    // Returns the expression e1 != e2
    Expr* makeNEq(Expr* e1, Expr* e2);
    // Returns the expression e1 < e2
    Expr* makeLT(Expr* e1, Expr* e2);
    // Returns the expression e1 > e2
    Expr* makeGT(Expr* e1, Expr* e2);
    // Returns the expression e1 <= e2
    Expr* makeLTEq(Expr* e1, Expr* e2);
    // Returns the expression e1 >= e2
    Expr* makeGTEq(Expr* e1, Expr* e2);

    // Arithmetic expressions
    // Returns the expression e1 + e2
    Expr* makeAdd(Expr* e1, Expr* e2);
    // Returns the expression e1 - e2
    Expr* makeSub(Expr* e1, Expr* e2);
    // Returns the expression e1 * e2
    Expr* makeMult(Expr* e1, Expr* e2);
    // Returns the expression e1 / e2
    Expr* makeDivQuo(Expr* e1, Expr* e2);
    // Returns the expression e1 % e2
    Expr* makeDivRem(Expr* e1, Expr* e2);
    // Returns the expression -e1
    Expr* makeNeg(Expr* e1);
    // Returns the expression /e1
    Expr* makeRec(Expr* e1);
    // Returns the expression e1 = e2
    Expr* makeAssign(Expr* e1, Expr* e2);
    // Returns the expression e1(e2, e3,..., en)
    Expr* makeCall(std::vector<Expr*> const& es);

    // Statements
    // Returns the skip statement
    Stmt* makeSkip();
    // Returns the statement { s1, s2,..., sn }
    Stmt* makeBlock(std::initializer_list<Stmt*> ss);
    Stmt* makeBlock(std::vector<Stmt*> const& ss);
    // Returns the statement if (e) s1 else s2
    Stmt* makeIf(Expr* e, Stmt* s1, Stmt* s2);
    // Returns the statement while (e) s1
    Stmt* makeWhile(Expr* e, Stmt* s1);
    // Returns the skip statement
    Stmt* makeBreak();
    Stmt* makeCont();
    // Returns the statement return e
    Stmt* makeRet(Decl* d, Expr* e);
    // Returns the statement e
    Stmt* makeExpr(Expr* e);
    // Returns the statement d
    Stmt* makeDecl(Decl* d);

    // Declarations
    // Returns a new name
    Name* makeName(Symbol s);
    // Returns a new object or reference definition
    varDecl* makeVar(Name* n, Type* t);
    // Returns a new function definition
    funcDecl* makeFunc(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s);

    // Typing
    // Return e if its converted type is boolean
    Expr* requireBool(Expr* e);
    // Return e if its converted type is arithmetic
    Expr* requireArmtc(Expr* e);
    // Return e if its converted type is a function
    Expr* requireFunc(Expr* e);
    // Returns e converted to a type
    Expr* requireType(Expr* e, Type* t);
    // Returns t if it has a value of a specified type
    Expr* requireValOf(Expr* e, Type* t);
    // Returns t if it is a reference to a specified type
    Expr* requireRefTo(Expr* e, Type* t);
    // Returns {e1, e2} if they can have the same type
    std::pair<Expr*, Expr*> requireSame(Expr* e1, Expr* e2);
    // Returns {e1, e2} if they can be converted to the same value
    std::pair<Expr*, Expr*> requireSameVal(Expr* e1, Expr* e2);
    // Returns {e1, e2} if they can be converted to the same arithmetic value
    std::pair<Expr*, Expr*> requireSameArmtc(Expr* e1, Expr* e2);
    // Returns {e1, e2} if they can be converted to a common type
    std::pair<Expr*, Expr*> requireCommon(Expr* e1, Expr* e2);

    // Convert a reference to a value
    Expr* convertToVal(Expr* e);

    // Initialization
    void copyInit(Decl* d, Expr* e);
    // Converts a declaration to an expression and returns it
    void refInit(Decl* d, Expr* e);
    // Binds a declaration to an expression and returns it
};
