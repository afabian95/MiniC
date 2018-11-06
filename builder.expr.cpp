/* builder.expr.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"

#include <iostream>
#include <tuple>

Expr* Builder::makeBool(bool b) {
    return new boolExpr(getBoolType(), Value(b));
}

Expr* Builder::makeTrue() {
    return makeBool(true);
}

Expr* Builder::makeFalse() {
    return makeBool(false);
}

Expr* Builder::makeInt(int n) {
    return new intExpr(getIntType(), Value(n));
}

Expr* Builder::makeAND(Expr* e1, Expr* e2) {
    e1 = requireBool(e1);
    e2 = requireBool(e2);
    return new andExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeOR(Expr* e1, Expr* e2) {
    e1 = requireBool(e1);
    e2 = requireBool(e2);
    return new orExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeNOT(Expr* e1) {
    e1 = requireBool(e1);
    return new notExpr(e1->getType(), e1);
}

Expr* Builder::makeCond(Expr* e1, Expr* e2, Expr* e3) {
    e1 = requireBool(e1);
    std::tie(e2, e3) = requireCommon(e2, e3);
    return new condExpr(e2->getType(), e1, e2, e3);
}

Expr* Builder::makeId(Decl* d) {
    Type* t;
    if (d->isObject() || d->isReference())
        t = getRefType(d->getType());
    else if (d->isFunction())
        t = d->getType();
    else
        throw std::logic_error("Error: invalid ID expression");
    return new idExpr(t, d);
}

Expr* Builder::makeEq(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameVal(e1, e2);
    return new equalExpr(getBoolType(), e1, e2);
}

Expr* Builder::makeNEq(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameVal(e1, e2);
    return new notEqualExpr(getBoolType(), e1, e2);
}

Expr* Builder::makeLT(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameVal(e1, e2);
    return new lessThanExpr(getBoolType(), e1, e2);
}

Expr* Builder::makeGT(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameVal(e1, e2);
    return new greaterThanExpr(getBoolType(), e1, e2);
}

Expr* Builder::makeLTEq(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameVal(e1, e2);
    return new lessThanOrEqualExpr(getBoolType(), e1, e2);
}

Expr* Builder::makeGTEq(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameVal(e1, e2);
    return new greaterThanOrEqualExpr(getBoolType(), e1, e2);
}

Expr* Builder::makeAdd(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameArmtc(e1, e2);
    return new addExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeSub(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameArmtc(e1, e2);
    return new subExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeMult(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameArmtc(e1, e2);
    return new multExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeDivQuo(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameArmtc(e1, e2);
    return new divQuoExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeDivRem(Expr* e1, Expr* e2) {
    std::tie(e1, e2) = requireSameArmtc(e1, e2);
    return new divRemExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeNeg(Expr* e1) {
    e1 = requireArmtc(e1);
    return new negationExpr(e1->getType(), e1);
}

Expr* Builder::makeAssign(Expr* e1, Expr* e2) {
    e2 = convertToVal(e2);
    e1 = requireRefTo(e1, e2->getType());
    return new assignExpr(e1->getType(), e1, e2);
}

Expr* Builder::makeCall(std::vector<Expr*> const& es) {
    std::vector<Expr*> conv = es;
    Expr*& func = conv[0];
    func = requireFunc(func);
    funcType* ft = static_cast<funcType*>(func->getType());

    NodeRange<Type> params = ft->getParameterTypes();
    std::vector<Expr*> args = conv;
    args.erase(args.begin());

    assert(params.getSize() == conv.size());

    auto pi = params.begin();
    auto ai = args.begin();
    while (pi != params.end()) {
        varDecl var(nullptr, *pi);
        copyInit(&var, *ai);
        *ai = var.getInit();
        ++pi;
        ++ai;
    }

    // TODO: Fix return values
    std::initializer_list<Expr*> temp;
    return new callExpr(ft->getReturnType(), temp);
}
