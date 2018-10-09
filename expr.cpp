/* expr.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include<iostream>
#include "decl.hpp"
#include "expr.hpp"
#include "printer.hpp"

// Print functions

static void printBool(Printer& p, boolExpr const* e){
    if (e->getBoolValue())
        p.getStream() << "true";
    else
        p.getStream() << "false";
}

static void printInt(Printer& p, intExpr const* e){
    p.getStream() << e->getIntValue();
}

static void printFloat(Printer& p, floatExpr const* e){
    p.getStream() << e->getFloatValue();
}

static void printId(Printer& p, idExpr const* e){
    p.getStream() << e->getDeclaration()->getName()->getString();
}

void print(Printer& p, Expr const* e){
    switch (e->getExpression()) {
        case Expr::myBoolean:
            return printBool(p, static_cast<boolExpr const*>(e));
        case Expr::myInteger:
            return printInt(p, static_cast<intExpr const*>(e));
        case Expr::myFloat:
            return printFloat(p, static_cast<floatExpr const*>(e));
        case Expr::myIdentifier:
            return printId(p, static_cast<idExpr const*>(e));
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Expr const& s){
    Printer p(os);
    print(p, &s);
    return os;
}
