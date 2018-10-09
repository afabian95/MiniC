/* type.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include<iostream>
#include "type.hpp"
#include "printer.hpp"

// Support functions for isSameType
static bool isSame(Type const* typeOne, Type const* typeTwo) {
    return typeOne->isSameType(typeTwo);
}

static bool isSameRef(refType const* refOne, refType const* refTwo) {
    return isSame(refOne->getChild(), refTwo->getChild());
}

static bool isSameFunc(funcType const* funcOne, funcType const* funcTwo) {
    return std::equal(funcOne->getFirst(), funcOne->getLast(),
                      funcTwo->getFirst(), funcTwo->getLast(), isSame);
}

// Function to determine if two values have the same type
bool Type::isSameType(Type const* that) const {
    //If different base types, return false
    if (myKind != that->myKind)
        return false;
    //If reference or function, look at operands
    if (myKind == myRef)
        return isSameRef(static_cast<refType const*>(this), static_cast<refType const*>(that));
    if (myKind == myFunc)
        return isSameFunc(static_cast<funcType const*>(this), static_cast<funcType const*>(that));
    // Remaining types are bool, int, and float (already checked)
    return true;
}

// Print functions

static void printType(Printer& p, char const* str){
    p.getStream() << str << '\n';
}

void print(Printer& p, Type const* t){
    switch (t->getType()) {
        case Type::myBool :
            return printType(p, "bool");
        case Type::myInt :
            return printType(p, "int");
        case Type::myFloat :
            return printType(p, "float");
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Type const& t){
    Printer p(os);
    print(p, &t);
    return os;
}
