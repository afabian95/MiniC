/* actions.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "builder.hpp"
#include "scope.hpp"
#include "token.hpp"

class Expr;
class Stmt;
class Decl;
class Type;

// The semantic/parsing actions class
class Actions {
public:
    // Returns a boolean expression
    Expr* onBoolLit(Token const& tok);
    // Returns an integer expression
    Expr* onIntLit(Token const& tok);
    // Returns an ID expression
    Expr* onIdExpr(Token const& tok);
    // Returns a negation expression
    Expr* onNegExpr(Expr* arg);
    // Returns a reciprocal expression
    Expr* onRecExpr(Expr* arg);
    // Returns a multiplication expression
    Expr* onMultExpr(Expr* e1, Expr* e2);
    // Returns a division expression
    Expr* onDivQuoExpr(Expr* e1, Expr* e2);
    // Returns a remainder expression
    Expr* onDivRemExpr(Expr* e1, Expr* e2);

    // Returns an object declaration
    Decl* onObjectDecl(Token id, Type* t);
    void finishObjectDecl(Decl* d, Expr* init);

    // Returns a function declaration
    Decl* onFuncDecl(Token id, std::vector<Decl*> const& parms, Type* t);
    Decl* startFuncDecl(Decl* d);
    Decl* finishFuncDecl(Decl* d, Stmt* s);

private:
    // The builder
    Builder myBuilder;
    // The scope stack
    scopeStack myStack;

public:
    // Enter a new scope
    void enterScope() { myStack.emplace_back(); }
    // Leave the current scope
    void leaveScope() { myStack.pop_back(); }
    // Return the current scope
    Scope* getCurrentScope() { return &myStack.back(); }
};
