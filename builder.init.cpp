/* builder.init.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"

void Builder::copyInit(Decl* d, Expr* e) {
    assert(d->isVariable());
    varDecl* var = static_cast<varDecl*>(d);
    if (d->isReference())
        return refInit(d, e);
    e = requireType(e, d->getType());
    var->setInit(e);
}

void Builder::refInit(Decl* d, Expr* e) {
    assert(d->isVariable());
    varDecl* var = static_cast<varDecl*>(d);
    e = requireType(e, d->getType());
    var->setInit(e);
}
