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
        mySkipStmt,     // skip statement
        myBreakStmt,    // break statement
        myContStmt,     // continue statement
        myBlockStmt,    // block statement
        myWhileStmt,    // while statement
        myIfStmt,       // if statement
        myRetStmt,      // return statement
        myExprStmt,     // expression statement
        myDeclStmt,     // declaration statement
    };

protected:
    Stmt(Kind k);

private:
    Kind myKind;

public:
    // Returns the kind of the statement
    Kind getStmtKind() const { return myKind; }
    // Returns the name of the statement
    char const* getStmtName() const;
};
inline Stmt::Stmt(Kind k) :
    myKind(k) {}

// For statements with no arguments
class nullaryStmt : public Stmt {
protected:
   nullaryStmt(Kind k);
};
inline nullaryStmt::nullaryStmt(Kind k) :
    Stmt(k) {}

// For statements with one argument
class unaryStmt : public Stmt {
protected:
    unaryStmt(Kind k, Stmt* op);
private:
    Stmt* myOp;
public:
    // Returns the only argument
    Stmt* getChild() const { return myOp; }
};
inline unaryStmt::unaryStmt(Kind k, Stmt* op) :
    Stmt(k), myOp(op) {}

// For statements with two arguments
class binaryStmt : public Stmt {
protected:
    binaryStmt(Kind k, Stmt* op1, Stmt* op2);
private:
    Stmt* firstOp;
    Stmt* secondOp;
public:
    // Returns the first argument
    Stmt* getFirst() const { return firstOp; }
    // Returns the second argument
    Stmt* getSecond() const { return secondOp; }
};
inline binaryStmt::binaryStmt(Kind k, Stmt* op1, Stmt* op2) :
    Stmt(k), firstOp(op1), secondOp(op2) {}

// For statements with k operands
class karyStmt : public Stmt {
protected:
    // Initialized with no arguments
    karyStmt(Kind k);
    // Initialized with a list of arguments
    karyStmt(Kind k, std::initializer_list<Stmt*> list);
    karyStmt(Kind k, std::vector<Stmt*> const& vec);
    karyStmt(Kind k, std::vector<Stmt*>&& vec);

private:
    std::vector<Stmt*> myOps;

public:
    // Returns the first argument
    Stmt** begin() { return myOps.data(); }
    Stmt* const* begin() const { return myOps.data(); }
    // Returns the last argument
    Stmt** end() { return myOps.data() + myOps.size(); }
    Stmt* const* end() const { return myOps.data() + myOps.size(); }
    // Returns a range of arguments
    NodeRange<Stmt> getChildren() { return { begin(), end()}; }
    NodeRange<Stmt const> getChildren() const { return { begin(), end()}; }
};
inline karyStmt::karyStmt(Kind k) :
    Stmt(k) {}
inline karyStmt::karyStmt(Kind k, std::initializer_list<Stmt*> list) :
    Stmt(k), myOps(list) {}
inline karyStmt::karyStmt(Kind k, std::vector<Stmt*> const& vec) :
    Stmt(k), myOps(vec) {}
inline karyStmt::karyStmt(Kind k, std::vector<Stmt*>&& vec) :
    Stmt(k), myOps(std::move(vec)) {}

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
class blockStmt : public karyStmt {
public:
    // Constructs the block statement from a list of arguments
    blockStmt(std::initializer_list<Stmt*> ops);
    blockStmt(std::vector<Stmt*> const& vec);
    blockStmt(std::vector<Stmt*>& vec);
};
inline blockStmt::blockStmt(std::initializer_list<Stmt*> ops) :
    karyStmt(myBlockStmt, ops) {}
inline blockStmt::blockStmt(std::vector<Stmt*> const& vec) :
    karyStmt(myBlockStmt, vec) {}
inline blockStmt::blockStmt(std::vector<Stmt*>& vec) :
    karyStmt(myBlockStmt, vec) {}

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
    Decl* myDecl;
public:
    declStmt(Decl* d);
    Decl* getDeclaration() const { return myDecl; }
};
inline declStmt::declStmt(Decl* d) :
    nullaryStmt(myDeclStmt), myDecl(d) {}

//Operations
void printStmt(Printer& p, Stmt const* s);

std::ostream& operator<<(std::ostream& os, Stmt const& s);

