/* stmt.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include<iostream>
#include "stmt.hpp"
#include "printer.hpp"

// Print functions

static void printBlock(Printer& p, blockStmt const* s){
    p.getStream() << '{';
    p.printNewLine();
    p.indent();
    print(p, s);
    p.printNewLine();
    p.getStream() << '}';
}

static void printExpression(Printer& p, exprStmt const* s){
    print(p, s);
}

static void printReturn(Printer& p, returnStmt const* s){
    p.getStream() << "return ";
    print(p, s);
}

void print(Printer& p, Stmt const* s){
    switch (s->getStatement()) {
        case Stmt::myBlock :
            return printBlock(p, static_cast<blockStmt const*>(s));
        case Stmt::myExpression :
            return printExpression(p, static_cast<exprStmt const*>(s));
        case Stmt::myReturn :
            return printReturn(p, static_cast<returnStmt const*>(s));
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Stmt const& s){
    Printer p(os);
    print(p, &s);
    return os;
}
