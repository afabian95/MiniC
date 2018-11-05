/* stmt.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "tree.hpp"
#include "value.hpp"

class Expr;
class Decl;
class Printer;

// The general statement class
class Stmt {
public:
    // Kinds of statements
    enum Kind{
        mySkipStmt,
        myBreakStmt,
        myContStmt,
        myBlockStmt,
        myWhileStmt,
        myIfStmt,
        myRetStmt,
        myExprStmt,
        myDeclStmt,
    };

protected:
    Stmt(Kind k);

private:
    Kind myKind;

public:
    Kind getStmtKind() const { return myKind; }
    char const* getStmtName() const;
};
inline Stmt::Stmt(Kind k) :
    myKind(k) {}

// For statements with no operands
class nullaryStmt : public Stmt {
protected:
   nullaryStmt(Kind k);
};
inline nullaryStmt::nullaryStmt(Kind k) :
    Stmt(k) {}

// For statements with one operand
class unaryStmt : public Stmt {
protected:
    unaryStmt(Kind k, Stmt* op);
private:
    Stmt* myOp;
public:
    Stmt* getChild() const { return myOp; }
};
inline unaryStmt::unaryStmt(Kind k, Stmt* op) :
    Stmt(k), myOp(op) {}

// For statements with two operands
class binaryStmt : public Stmt {
protected:
    binaryStmt(Kind k, Stmt* op1, Stmt* op2);
private:
    Stmt* firstOp;
    Stmt* secondOp;
public:
    Stmt* getFirst() const { return firstOp; }
    Stmt* getSecond() const { return secondOp; }
};
inline binaryStmt::binaryStmt(Kind k, Stmt* op1, Stmt* op2) :
    Stmt(k), firstOp(op1), secondOp(op2) {}

// For statements with k operands
class knaryStmt : public Stmt {
protected:
    knaryStmt(Kind k, std::initializer_list<Stmt*> ops);
private:
    Stmt* const* firstOp;
    Stmt* const* lastOp;
    std::initializer_list<Stmt*> allOps;
public:
    Stmt* const* getFirst() const { return firstOp; }
    Stmt* const* getLast() const { return lastOp; }
    std::initializer_list<Stmt*> getChildren() const { return allOps;}
};
inline knaryStmt::knaryStmt(Kind k, std::initializer_list<Stmt*> ops) :
    Stmt(k), firstOp(ops.begin()), lastOp(ops.end()), allOps(ops) {}

// Statements

// Skip statement
class skipStmt : public nullaryStmt {
public:
    skipStmt();
};
inline skipStmt::skipStmt() :
    nullaryStmt(mySkipStmt) {}

// Break statement
class breakStmt : public nullaryStmt {
public:
    breakStmt();
};
inline breakStmt::breakStmt() :
    nullaryStmt(myBreakStmt) {}

// Continue statement
class contStmt : public nullaryStmt {
public:
    contStmt();
};
inline contStmt::contStmt() :
    nullaryStmt(myContStmt) {}

// Block statement
class blockStmt : public knaryStmt {
public:
    blockStmt(std::initializer_list<Stmt*> ops);
};
inline blockStmt::blockStmt(std::initializer_list<Stmt*> ops) :
    knaryStmt(myBlockStmt, ops) {}

// While statement
class whileStmt : public unaryStmt {
private:
    Expr* myCond;
public:
    whileStmt(Expr* e, Stmt* s);
    Expr* getCond() const { return myCond; }
    Stmt* getBody() const { return getChild(); }
};
inline whileStmt::whileStmt(Expr* e, Stmt* s) :
    unaryStmt(myWhileStmt, s), myCond(e) {}

// If statement
class ifStmt : public binaryStmt {
private:
    Expr* myCond;
public:
    ifStmt(Expr* e, Stmt* s1, Stmt* s2);
    Expr* getCond() const { return myCond; }
    Stmt* getTrue() const { return getFirst(); }
    Stmt* getFalse() const { return getSecond(); }
};
inline ifStmt::ifStmt(Expr* e, Stmt* s1, Stmt* s2) :
    binaryStmt(myIfStmt, s1, s2) {}

// Return statement
class returnStmt : public nullaryStmt {
private:
    Expr* myRet;
public:
    returnStmt(Expr* e);
    Expr* getReturn() const { return myRet; }
};
inline returnStmt::returnStmt(Expr* e) :
    nullaryStmt(myRetStmt), myRet(e) {}

// Expression statement
class exprStmt : public nullaryStmt {
private:
    Expr* myExpr;
public:
    exprStmt(Expr* e);
    Expr* getExpression() const { return myExpr; }
};
inline exprStmt::exprStmt(Expr* e) :
    nullaryStmt(myExprStmt), myExpr(e) {}

// Declaration statement
class declStmt : public nullaryStmt {
private:
    Expr* myDecl;
public:
    declStmt(Expr* e);
    Expr* getDeclaration() const { return myDecl; }
};
inline declStmt::declStmt(Expr* e) :
    nullaryStmt(myDeclStmt), myDecl(e) {}

//Operations
void printStmt(Printer& p, Stmt const* s);

std::ostream& operator<<(std::ostream& os, Stmt const& s);

