/* type.print.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "type.hpp"
#include "printer.hpp"

#include <iostream>

// Prints literal type
static void printLiteral(Printer& p, char const* str) {
    p.getStream() << str;
}

// Prints reference type
static void printRef(Printer& p, refType const* t) {
    p.getStream() << "ref ";
    printType(p, t->getObjectType());
}

// Prints function type
static void printFunc(Printer& p, funcType const* t) {
    p.getStream() << '(';
    NodeRange<const Type> params = t->getParameterTypes();
    for (Type* const* i = params.begin(); i != params.end(); i++) {
        printType(p, *i);
    if (std::next(i) != params.end())
        p.getStream() << ',';
    }
    p.getStream() << ')' << "->";
    printType(p, t->getReturnType());
}

// Prints any type
void printType(Printer& p, Type const* t) {
    switch (t->getTypeKind()) {
        case Type::myBoolType:
            return printLiteral(p, "bool");
        case Type::myIntType:
            return printLiteral(p, "int");
        case Type::myFloatType:
            return printLiteral(p, "float");
        case Type::myRefType:
            return printRef(p, static_cast<refType const*>(t));
        case Type::myFuncType:
            return printFunc(p, static_cast<funcType const*>(t));
    }
}

std::ostream& operator<<(std::ostream& os, Type const& t) {
    Printer p(os);
    printType(p, &t);
    return os;
}
