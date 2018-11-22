/* builder.type.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "type.hpp"

Type* Builder::getRefType(Type* t) {
    return new refType(t);
}

Type* Builder::getFuncType(std::initializer_list<Type*> const& ops) {
    return new funcType(ops);
}

