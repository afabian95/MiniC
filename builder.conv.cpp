/* builder.conv.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "type.hpp"
#include "expr.hpp"

Expr* Builder::convertToVal(Expr* e) {
    Type* t = e->getType();
    if (t->isReference()) {
        refType* ref = static_cast<refType*>(t);
        return new valConv(ref->getObjectType(), e);
    }
    return e;
}
