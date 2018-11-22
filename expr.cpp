/* expr.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "expr.hpp"

char const* Expr::getExprName() const {
    switch (myKind) {
        case myBoolLit:
            return "bool_lit";
        case myIntLit:
            return "int_lit";
        case myFloatLit:
            return "float_lit";
        case myIdExpr:
            return "id_expr";
        case myANDExpr:
            return "and_expr";
        case myORExpr:
            return "or_expr";
        case myNOTExpr:
            return "not_expr";
        case myCondExpr:
            return "cond_expr";
        case myEqExpr:
            return "eq_expr";
        case myNEqExpr:
            return "ne_expr";
        case myLTExpr:
            return "lt_expr";
        case myGTExpr:
            return "gt_expr";
        case myLTEqExpr:
            return "le_expr";
        case myGTEqExpr:
            return "ge_expr";
        case myAddExpr:
            return "add_expr";
        case mySubExpr:
            return "sub_expr";
        case myMultExpr:
            return "mul_expr";
        case myDivQuoExpr:
            return "div_expr";
        case myDivRemExpr:
            return "rem_expr";
        case myNegExpr:
            return "neg_expr";
        case myRecExpr:
            return "rec_expr";
        case myAssignExpr:
            return "assign_expr";
        case myCallExpr:
            return "call_expr";
        case myValConv:
            return "value_conv";
    };
    assert(false);
}
