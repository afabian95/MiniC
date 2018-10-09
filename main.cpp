/* main.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include <iostream>

#include "decl.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "type.hpp"
#include "printer.hpp"

// Main class not described in instructions
// Implementing code from online example

Decl* makeMin() {
    Type* b = new boolType();
    Type* z = new intType();
    Decl* p1 = new objDecl(new Name("a"), z, nullptr);
    Decl* p2 = new objDecl(new Name("b"), z, nullptr);
    Decl* r = new objDecl(nullptr, z, nullptr);

    // p1 < p2 ? p1 : p2
    Expr* expr = new condExpr(z, new lessThanExpr(b, new idExpr(z, p1), new idExpr(z, p2)),
                              new idExpr(z, p1), new idExpr(z, p2));
    Stmt* body = new blockStmt({ new returnStmt(expr) });
    Type* func = new funcType({ z, z, z});
    return new funcDecl(new Name("min"), func, {p1, p2, r}, body);
}

int main()
{
    Decl* test = makeMin();
    std::cout << *test << '\n';
    return 0;
}
