/* decl.print.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "decl.hpp"
#include "name.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "printer.hpp"

#include <iostream>

template<typename T>
void printVar(Printer& p, T const* d) {
    if (d->isObject())
        p.getStream() << "var ";
    else
        p.getStream() << "ref ";

    if (Name const* n = d->getName())
        printName(p, n);

    if (Type const* t = d->getType())
        printType(p, t);

    if (Expr const* e = d->getInit())
        printExpr(p, e);
}

void printFunc(Printer& p, funcDecl const* d) {
    p.getStream() << "fun ";

    if (Name const* n = d->getName())
        printName(p, n);

//    if (Stmt* s = d->getBody())
//        printStmt(p, s);
}

void printProg(Printer& p, progDecl const* d) {
//    for (Decl* member : *d)
//        printDecl(p, member);
}

void printDecl(Printer& p, Decl const* d) {
    switch (d->getDeclKind()) {
        case Decl::myVarDecl:
            return printVar(p, static_cast<varDecl const*>(d));
        case Decl::myFuncDecl:
            return printFunc(p, static_cast<funcDecl const*>(d));
        case Decl::myProgDecl:
            return printProg(p, static_cast<progDecl const*>(d));
    }
}

std::ostream& operator<<(std::ostream& os, Decl const& d) {
    Printer p(os);
    printDecl(p, &d);
    return os;
}
