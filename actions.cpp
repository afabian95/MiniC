/* actions.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "actions.hpp"
#include "expr.hpp"
#include "name.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "symbol.hpp"

Expr* Actions::onBoolLit(Token const& token) {
    if (token.isSameAs(Token::myTrueKW))
        return myBuilder.makeTrue();
    return myBuilder.makeFalse();
}

Expr* Actions::onIntLit(Token const& token) {
    int n = std::stoi(token.getLexeme().str());
    return myBuilder.makeInt(n);
}

Expr* Actions::onIdExpr(Token const& token) {
    Decl* decl = myStack.lookup(token.getLexeme());
    if (!decl)
        throw std::runtime_error("Error: no matching declaration");
    return myBuilder.makeId(decl);
}

Expr* Actions::onNegExpr(Expr* arg) {
    return myBuilder.makeNeg(arg);
}

Expr* Actions::onRecExpr(Expr* arg) {
    return myBuilder.makeRec(arg);
}

Expr* Actions::onMultExpr(Expr* e1, Expr* e2) {
    return myBuilder.makeMult(e1, e2);
}

Expr* Actions::onDivQuoExpr(Expr* e1, Expr* e2) {
    return myBuilder.makeDivQuo(e1, e2);
}

Expr* Actions::onDivRemExpr(Expr* e1, Expr* e2) {
    return myBuilder.makeDivRem(e1, e2);
}

Decl* Actions::onObjectDecl(Token id, Type* type) {
    Scope* scope = getCurrentScope();

    // Check for any redefinitions
    if (scope->lookup(id.getLexeme()))
        throw std::runtime_error("Error: redefinition");

    // Partially create the declaration.
    Name* name = myBuilder.makeName(id.getLexeme());
    Decl *var = myBuilder.makeVar(name, type);

    // Emit the declaration.
    scope->declare(var);

    return var;
}

void Actions::finishObjectDecl(Decl* d, Expr* init) {
    // Perform copy initialization
    myBuilder.copyInit(d, init);
}

Decl* Actions::onFuncDecl(Token id, std::vector<Decl*> const& params, Type* type) {
    Scope* scope = getCurrentScope();

    // Check for any redefinitions
    if (scope->lookup(id.getLexeme()))
        throw std::runtime_error("Error: redefinition");

    // Build the function type
    //Type* f = myBuilder.getFuncType(params, type);

    // Build the function
    funcDecl* fn = nullptr;

    // Emit the declaration
    scope->declare(fn);

    return fn;
}

Decl* Actions::startFuncDecl(Decl* d) {
    funcDecl* fn = static_cast<funcDecl*>(d);
    return fn;
}

Decl* Actions::finishFuncDecl(Decl* d, Stmt* s) {
    funcDecl* fn = static_cast<funcDecl*>(d);

    // Set the body of the function.
    fn->setBody(s);

    return fn;
}

