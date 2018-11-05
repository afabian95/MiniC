/* expr.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "expr.hpp"

char const* Expr::getExprName() const {
    switch (myKind) {
        case myBoolLit:
            return "boolean literal";
        case myIntLit:
            return "integer literal";
        case myFloatLit:
            return "floating point literal";
        case myIdExpr:
            return "ID expression";
        case myANDExpr:
            return "AND expression";
        case myORExpr:
            return "OR expression";
        case myNOTExpr:
            return "NOT expression";
        case myCondExpr:
            return "ID expression";
        case myEqExpr:
            return "equals expression";
        case myNEqExpr:
            return "not equals expression";
        case myLTExpr:
            return "less than expression";
        case myGTExpr:
            return "greater than expression";
        case myLTEqExpr:
            return "less than or equals expression";
        case myGTEqExpr:
            return "greater than or equals expression";
        case myAddExpr:
            return "addition expression";
        case mySubExpr:
            return "subtraction expression";
        case myMultExpr:
            return "multiplication expression";
        case myDivQuoExpr:
            return "division (quotient) expression";
        case myDivRemExpr:
            return "division (remainder) expression";
        case myNegExpr:
            return "negation expression";
        case myRecExpr:
            return "reciprocal expression";
        case myAssignExpr:
            return "assignment expression";
        case myCallExpr:
            return "call expression";
        case myValConv:
            return "value conversion";
    };
    assert(false);
}
