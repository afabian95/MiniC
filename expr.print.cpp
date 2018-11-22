/* expr.print.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "expr.hpp"
#include "name.hpp"
#include "type.hpp"
#include "decl.hpp"
#include "printer.hpp"

#include <iostream>

// Prints boolean expression
static void printBool(Printer& p, boolExpr const* e){
    if (e->getBoolValue())
        p.getStream() << "true";
    else
        p.getStream() << "false";
}

// Prints integer expression
static void printInt(Printer& p, intExpr const* e){
    p.getStream() << e->getIntValue();
}

// Prints floating point expression
static void printFloat(Printer& p, floatExpr const* e){
    p.getStream() << e->getFloatValue();
}

// Prints identifier expression
static void printId(Printer& p, idExpr const* e){
    p.getStream() << e->getDeclaration()->getName()->getString();
}

// Prints any expression
void printExpr(Printer& p, Expr const* e){
    switch (e->getExprKind()) {
        case Expr::myBoolLit:
            return printBool(p, static_cast<boolExpr const*>(e));
        case Expr::myIntLit:
            return printInt(p, static_cast<intExpr const*>(e));
        case Expr::myFloatLit:
            return printFloat(p, static_cast<floatExpr const*>(e));
        case Expr::myIdExpr:
            return printId(p, static_cast<idExpr const*>(e));
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Expr const& e) {
    Printer p(os);
    printExpr(p, &e);
    return os;
}
