/* stmt.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "stmt.hpp"

char const* Stmt::getStmtName() const {
    switch (myKind) {
        case mySkipStmt:
            return "skip statement";
        case myBlockStmt:
            return "block statement";
        case myIfStmt:
            return "if statement";
        case myWhileStmt:
            return "while statement";
        case myBreakStmt:
            return "break statement";
        case myContStmt:
            return "continue statement";
        case myRetStmt:
            return "return statement";
        case myExprStmt:
            return "expression statement";
        case myDeclStmt:
            return "declaration statement";
    }
    assert(false);
}

