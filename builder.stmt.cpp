/* builder.stmt.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "decl.hpp"
#include "stmt.hpp"

Stmt* Builder::makeSkip() {
    return new skipStmt();
}

Stmt* Builder::makeBlock(std::initializer_list<Stmt*> ss) {
    return new blockStmt(ss);
}

Stmt* Builder::makeIf(Expr* e, Stmt* s1, Stmt* s2) {
    e = requireBool(e);
    return new ifStmt(e, s1, s2);
}

Stmt* Builder::makeWhile(Expr* e, Stmt* s1) {
    e = requireBool(e);
    return new whileStmt(e, s1);
}

Stmt* Builder::makeBreak() {
    return new breakStmt();
}

Stmt* Builder::makeCont() {
    return new contStmt();
}

Stmt* Builder::makeRet(Decl* d, Expr* e) {
    assert(d->isVariable());
    varDecl* var = static_cast<varDecl*>(d);
    copyInit(var, e);
    return new returnStmt(var->getInit());
}

Stmt* Builder::makeExpr(Expr* e) {
    return new exprStmt(e);
}

Stmt* Builder::makeDecl(Decl* d) {
    return new declStmt(d);
}
