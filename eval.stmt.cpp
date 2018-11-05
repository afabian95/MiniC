/* eval.stmt.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "eval.hpp"
#include "stmt.hpp"
#include "decl.hpp"

#include <iostream>

static Control evalExpr(Eval& eval, exprStmt const* s) {
    evalExpr(eval, s->getExpression());
    return nextFunc;
}

static Control evalBlock(Eval& eval, blockStmt const* s) {
    for (Stmt const* child : s->getChildren()) {
    Control ctrl = evalStmt(eval, child);
    if (ctrl != nextFunc)
        return ctrl;
    }
    return nextFunc;
}

static Control evalIf(Eval& eval, ifStmt const* s) {
    Value cond = evalExpr(eval, s->getCond());
    if (cond.getInt())
        return evalStmt(eval, s->getTrue());
    return evalStmt(eval, s->getFalse());
}

static Control evalWhile(Eval& eval, whileStmt const* s) {
    while (true) {
        Value cond = evalExpr(eval, s->getCond());
        if (cond.getInt()) {
            Control ctrl = evalStmt(eval, s->getBody());
        if (ctrl == returnFunc)
            return ctrl;
        if (ctrl == breakFunc)
            break;
        if (ctrl == contFunc)
            continue;
        } else break;
    }
    return nextFunc;
}

static Control evalBreak(Eval& eval, breakStmt const* s) {
    return breakFunc;
}

static Control evalCont(Eval& eval, contStmt const* s) {
    return contFunc;
}

static Control evalReturn(Eval& eval, returnStmt const* s) {
    Value val = evalExpr(eval, s->getReturn());
    Frame* frame = eval.getCurrentFrame();
    funcDecl* func = static_cast<funcDecl*>(frame->getFunction());
    Object* ret = frame->locateLocalVars(func->getReturn());
    ret->init(val);
    return returnFunc;
}

static Control evalDecl(Eval& eval, declStmt const* s) {
    // Decl* decl; // FIXME: Get from declStmt
    // Object* obj = eval.getCurrentFrame()->getLocalVars().locate(decl);
    // Value val = evalExpr(eval, s->getDeclaration());
    // obj->init(val);
    return nextFunc;
}

Control evalStmt(Eval& eval, Stmt const* s) {
    switch (s->getStmtKind()) {
        case Stmt::mySkipStmt:
            return nextFunc;
        case Stmt::myBreakStmt:
            return evalBreak(eval, static_cast<breakStmt const*>(s));
        case Stmt::myContStmt:
            return evalCont(eval, static_cast<contStmt const*>(s));
        case Stmt::myBlockStmt:
            return evalBlock(eval, static_cast<blockStmt const*>(s));
        case Stmt::myWhileStmt:
            return evalWhile(eval, static_cast<whileStmt const*>(s));
        case Stmt::myIfStmt:
            return evalIf(eval, static_cast<ifStmt const*>(s));
        case Stmt::myRetStmt:
            return evalReturn(eval, static_cast<returnStmt const*>(s));
        case Stmt::myExprStmt:
            return evalExpr(eval, static_cast<exprStmt const*>(s));
        case Stmt::myDeclStmt:
            return evalDecl(eval, static_cast<declStmt const*>(s));
    }
    assert(false);
}
