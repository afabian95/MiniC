/* type.print.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "type.hpp"
#include "printer.hpp"

#include <iostream>

static void printLiteral(Printer& p, char const* str) {
    p.getStream() << str;
}

static void printRef(Printer& p, refType const* t) {
    p.getStream() << "ref ";
    printType(p, t->getObjectType());
}

static void printFunc(Printer& p, funcType const* t) {
    p.getStream() << '(';
    //NodeRange<const Type> parms = t->getParameterTypes();
    //for (Type* const* i = parms.begin(); i != parms.end(); i++) {
    //    printType(p, *i);
    //    if (std::next(i) != parms.end())
            p.getStream() << ',';
    //}
    p.getStream() << ')' << "->";
    //printType(p, t->getReturnType());
}

void printType(Printer& p, Type const* t) {
    switch (t->getTypeKind()) {
        case Type::myBoolType:
            return printLiteral(p, "boolean literal");
        case Type::myIntType:
            return printLiteral(p, "integer literal");
        case Type::myFloatType:
            return printLiteral(p, "floating point literal");
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
