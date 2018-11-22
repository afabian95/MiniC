/* builder.decl.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "decl.hpp"

varDecl* Builder::makeVar(Name* n, Type* t) {
    return new varDecl(n, t);
}

funcDecl* Builder::makeFunc(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s) {
    return new funcDecl(n, t, ops, s);
}
