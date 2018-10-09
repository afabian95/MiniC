/* decl.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include <iostream>
#include "decl.hpp"
#include "printer.hpp"

void printObj(Printer& p, objDecl const* d){
    p.getStream() << "var ";
//    if (Name const* n = d->getName())
//        print(p, n);
//    if (Stmt const* t = d->getType())
//        print(p, t);
//    if (Stmt const* i = d->getInitializer())
//        print(p, i);
}

void printRef(Printer& p, refDecl const* d){
    p.getStream() << "ref ";
//    if (Name const* n = d->getName())
//        print(p, n);
//    if (Stmt const* t = d->getType())
//        print(p, t);
//    if (Stmt const* i = d->getInitializer())
//        print(p, i);
}

void printFunc(Printer& p, funcDecl const* d){
    p.getStream() << "fun ";
//    if (Name const* n = d->getName())
//        print(p, n);
//    if (Stmt const* s = d->getBody())
//        print(p, s);
}

void print(Printer& p, Decl const* d){
    switch (d->getDeclaration()) {
        case Decl::myObject:
            return printObj(p, static_cast<objDecl const*>(d));
        case Decl::myReference:
            return printRef(p, static_cast<refDecl const*>(d));
        case Decl::myFunction:
            return printFunc(p, static_cast<funcDecl const*>(d));
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Decl const& d){
    Printer p(os);
    print(p, &d);
    return os;
}
