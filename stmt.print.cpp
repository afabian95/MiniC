/* stmt.print.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "stmt.hpp"
#include "expr.hpp"
#include "decl.hpp"
#include "printer.hpp"

#include<iostream>

// Print functions

static void printLiteral(Printer& p, char const* str) {
    p.getStream() << str << ';';
}

static void printBlock(Printer& p, blockStmt const* s){
    p.getStream() << '{';
    for (Stmt* sub : *s) {
        printStmt(p, sub);
        p.printNewline();
    }
    p.getStream() << '}';
}

static void printExpression(Printer& p, exprStmt const* s){
    printExpr(p, s->getExpression());
}

static void printReturn(Printer& p, returnStmt const* s){
    p.getStream() << "return ";
    printExpr(p, s->getReturn());
}

void printStmt(Printer& p, Stmt const* s){
    switch (s->getStmtKind()) {
        case Stmt::mySkipStmt:
            return printLiteral(p, "skip");
        case Stmt::myBreakStmt:
            return printLiteral(p, "break");
        case Stmt::myContStmt:
            return printLiteral(p, "continue");
        case Stmt::myBlockStmt :
            return printBlock(p, static_cast<blockStmt const*>(s));
        case Stmt::myExprStmt :
            return printExpression(p, static_cast<exprStmt const*>(s));
        case Stmt::myRetStmt :
            return printReturn(p, static_cast<returnStmt const*>(s));
        default:
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Stmt const& s){
    Printer p(os);
    printStmt(p, &s);
    return os;
}
