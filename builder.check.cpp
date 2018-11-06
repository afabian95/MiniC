/* builder.check.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "type.hpp"
#include "expr.hpp"

Expr* Builder::requireBool(Expr* e) {
    Expr* c = convertToVal(e);
    Type* t = c->getType();
    if (!t->isBool())
        throw std::runtime_error("Error: operand is not a boolean value");
    return c;
}

Expr* Builder::requireArmtc(Expr* e) {
    Expr* c = convertToVal(e);
    Type* t = c->getType();
    if (!t->isArithmetic())
        throw std::runtime_error("Error: operand is not an arithmetic value");
    return c;
}

Expr* Builder::requireFunc(Expr* e) {
    Expr* c = convertToVal(e);
    Type* t = c->getType();
    if (!t->isFunction())
        throw std::runtime_error("Error: not a function");
    return c;
}

Expr* Builder::requireType(Expr* e, Type* t) {
    if (t->isReference())
        return requireRefTo(e, t);
    else
        return requireValOf(e, t);
}

Expr* Builder::requireValOf(Expr* e, Type* t) {
    assert(t->isObject());
    e = convertToVal(e);
    if (!e->getType()->isSameType(t))
        throw std::runtime_error("Error: invalid operand");
    return e;
}

Expr* Builder::requireRefTo(Expr* e, Type* t) {
    Type* t1 = e->getType();
    if (!t1->isReferenceTo(t))
        throw std::runtime_error("Error: invalid operand reference");
    return e;
}

std::pair<Expr*, Expr*> Builder::requireSame(Expr* e1, Expr* e2) {
    Type* t1 = e1->getType();
    Type* t2 = e2->getType();
    if (!t1->isSameType(t2))
        throw std::runtime_error("Error: operands have different types");
    return {e1, e2};
}

std::pair<Expr*, Expr*> Builder::requireSameVal(Expr* e1, Expr* e2) {
    e1 = convertToVal(e1);
    e2 = convertToVal(e2);
    return requireSame(e1, e2);
}

std::pair<Expr*, Expr*> Builder::requireSameArmtc(Expr* e1, Expr* e2) {
    e1 = convertToVal(e1);
    e2 = convertToVal(e2);
    std::pair<Expr*, Expr*> p = requireSame(e1, e2);

    Type* t = p.first->getType();
    if (!t->isArithmetic())
        throw std::runtime_error("Error: operands are not arithmetic");
    return p;
}

std::pair<Expr*, Expr*> Builder::requireCommon(Expr* e1, Expr* e2) {
    Type* t1 = e1->getType();
    Type* t2 = e2->getType();
    if (t1->isReference() && t2->isReference())
        return requireSame(e1, e2);
    return requireSameVal(e1, e2);
}
