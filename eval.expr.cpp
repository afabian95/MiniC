/* eval.expr.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "eval.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"

#include <iostream>

static Value evalLiteral(Eval& eval, literalExpr const* e) {
    return e->getValue();
}

static Value evalId(Eval& eval, idExpr const* e) {
    Decl* d = e->getDeclaration();
    if (d->isFunction())
        return Value(static_cast<funcDecl*>(d));
    varDecl* var = static_cast<varDecl*>(d);
    Frame* f = eval.getCurrentFrame();
    return Value(addrValue{f->getIndex(), var});
}

template<typename T>
static Value evalBinaryOp(Eval& eval, binaryExpr const* e, T op) {
    Value v1 = evalExpr(eval, e->getFirst());
    Value v2 = evalExpr(eval, e->getSecond());
    if (e->getType()->isIntegral())
        return Value(op(v1.getInt(), v2.getInt()));
//    else if (e->getType()->isFloat())
//        return Value(op(v1.getFloat(), v2.getFloat()));
    else
        assert(false);
}

template<typename T>
static Value evalBinaryOp(Eval& eval, Expr const* e, T op) {
    return evalBinaryOp(eval, static_cast<binaryExpr const*>(e), op);
}

template<typename T = void>
struct invert {
    T operator()(T const& x) const { return T(1) / x; }
};

template<>
struct invert<void> {
    template<typename T>
    T operator()(T const& x) const { return T(1) / x; }
};

template<typename T>
static Value evalUnaryOp(Eval& eval, unaryExpr const* e, T op) {
    Value v1 = evalExpr(eval, e->getChild());
    if (e->getType()->isIntegral())
        return Value(op(v1.getInt()));
    else if (e->getType()->isFloat())
        return Value(op(v1.getFloat()));
    else
        assert(false);
}

template<typename T>
static Value evalUnaryOp(Eval& eval, Expr const* e, T op) {
    return evalUnaryOp(eval, static_cast<unaryExpr const*>(e), op);
}

template<typename T>
static Value evalRelation(Eval& eval, binaryExpr const* e, T cmp) {
    Value v1 = evalExpr(eval, e->getFirst());
    Value v2 = evalExpr(eval, e->getSecond());
    if (e->getType()->isIntegral())
        return Value(cmp(v1.getInt(), v2.getInt()));
    else if (e->getType()->isFloat())
        return Value(cmp(v1.getFloat(), v2.getFloat()));
    else
        assert(false);
}

template<typename T>
static Value evalRelation(Eval& eval, Expr const* e, T cmp) {
    return evalRelation(eval, static_cast<binaryExpr const*>(e), cmp);
}

static Value evalCond(Eval& eval, condExpr const* e) {
    Value v1 = evalExpr(eval, e->getCondition());
    if (v1.getInt())
        return evalExpr(eval, e->getTrueValue());
    else
        return evalExpr(eval, e->getFalseValue());
}

static Value evalAssign(Eval& eval, assignExpr const* e) {
    Value v1 = evalExpr(eval, e->getFirst());
    Value v2 = evalExpr(eval, e->getSecond());
    Object* obj = eval.locateObject(v1);
    obj->store(v2);
    return v1;
}

static Value evalVal(Eval& eval, valConv const* e) {
    Value v = evalExpr(eval, e->getSource());
    Object* obj = eval.locateObject(v);
    return obj->load();
}


Value evalExpr(Eval& eval, Expr const* e) {
    switch (e->getExprKind()) {
        case Expr::myBoolLit:
        case Expr::myIntLit:
        case Expr::myFloatLit:
            return evalLiteral(eval, static_cast<literalExpr const*>(e));
        case Expr::myIdExpr:
            return evalId(eval, static_cast<idExpr const*>(e));
        case Expr::myANDExpr:
        case Expr::myORExpr:
        case Expr::myNOTExpr:
            break;
        case Expr::myCondExpr:
            return evalCond(eval, static_cast<condExpr const*>(e));
        case Expr::myEqExpr:
            return evalRelation(eval, e, std::equal_to<>{});
        case Expr::myNEqExpr:
            return evalRelation(eval, e, std::not_equal_to<>{});
        case Expr::myLTExpr:
            return evalRelation(eval, e, std::less<>{});
        case Expr::myGTExpr:
            return evalRelation(eval, e, std::greater<>{});
        case Expr::myLTEqExpr:
            return evalRelation(eval, e, std::less_equal<>{});
        case Expr::myGTEqExpr:
            return evalRelation(eval, e, std::greater_equal<>{});
        case Expr::myAddExpr:
            return evalBinaryOp(eval, e, std::plus<>{});
        case Expr::mySubExpr:
            return evalBinaryOp(eval, e, std::minus<>{});
        case Expr::myMultExpr:
            return evalBinaryOp(eval, e, std::multiplies<>{});
        case Expr::myDivQuoExpr:
            return evalBinaryOp(eval, e, std::divides<>{});
        case Expr::myDivRemExpr:
            return evalBinaryOp(eval, e, std::modulus<>{});
        case Expr::myNegExpr:
            return evalUnaryOp(eval, e, std::negate<>{});
        case Expr::myRecExpr:
            return evalUnaryOp(eval, e, invert<>{});
        case Expr::myAssignExpr:
            return evalAssign(eval, static_cast<assignExpr const*>(e));
        case Expr::myCallExpr:
            break;
        case Expr::myValConv:
            return evalVal(eval, static_cast<valConv const*>(e));
  }
  assert(false);
}
