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
    Type* getBoolType() { return &myBoolType; }
    Type* getIntType() { return &myIntType; }
    Type* getFloatType() { return &myFloatType; }
    Type* getRefType(Type* t);
    Type* getFuncType(std::initializer_list<Type*> const& ts);

    // Expressions
    Expr* makeBool(bool b);
    Expr* makeTrue();
    Expr* makeFalse();
    Expr* makeInt(int n);
    Expr* makeFloat(double n);
    Expr* makeAND(Expr* e1, Expr* e2);
    Expr* makeOR(Expr* e1, Expr* e2);
    Expr* makeNOT(Expr* e1);
    Expr* makeCond(Expr* e1, Expr* e2, Expr* e3);
    Expr* makeId(Decl* d);

    // Relational expressions
    Expr* makeEq(Expr* e1, Expr* e2);
    Expr* makeNEq(Expr* e1, Expr* e2);
    Expr* makeLT(Expr* e1, Expr* e2);
    Expr* makeGT(Expr* e1, Expr* e2);
    Expr* makeLTEq(Expr* e1, Expr* e2);
    Expr* makeGTEq(Expr* e1, Expr* e2);

    // Arithmetic expressions
    Expr* makeAdd(Expr* e1, Expr* e2);
    Expr* makeSub(Expr* e1, Expr* e2);
    Expr* makeMult(Expr* e1, Expr* e2);
    Expr* makeDivQuo(Expr* e1, Expr* e2);
    Expr* makeDivRem(Expr* e1, Expr* e2);
    Expr* makeNeg(Expr* e1);
    Expr* makeRec(Expr* e1);
    Expr* makeAssign(Expr* e1, Expr* e2);
    Expr* makeCall(std::vector<Expr*> const& es);

    // Statements
    Stmt* makeSkip();
    Stmt* makeBlock(std::initializer_list<Stmt*> ss);
    Stmt* makeBlock(std::vector<Stmt*> const& ss);
    Stmt* makeIf(Expr* e, Stmt* s1, Stmt* s2);
    Stmt* makeWhile(Expr* e, Stmt* s1);
    Stmt* makeBreak();
    Stmt* makeCont();
    Stmt* makeRet(Decl* d, Expr* e);
    Stmt* makeExpr(Expr* e);
    Stmt* makeDecl(Decl* d);

    // Declarations
    varDecl* makeVar(Name* n, Type* t);
    funcDecl* makeFunc(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s);

    // Typing
    Expr* requireBool(Expr* e);
    Expr* requireArmtc(Expr* e);
    Expr* requireFunc(Expr* e);
    Expr* requireType(Expr* e, Type* t);
    Expr* requireValOf(Expr* e, Type* t);
    Expr* requireRefTo(Expr* e, Type* t);
    std::pair<Expr*, Expr*> requireSame(Expr* e1, Expr* e2);
    std::pair<Expr*, Expr*> requireSameVal(Expr* e1, Expr* e2);
    std::pair<Expr*, Expr*> requireSameArmtc(Expr* e1, Expr* e2);
    std::pair<Expr*, Expr*> requireCommon(Expr* e1, Expr* e2);

    // Conversions
    Expr* convertToVal(Expr* e);

    // Initialization
    void copyInit(Decl* d, Expr* e);
    void refInit(Decl* d, Expr* e);
};
