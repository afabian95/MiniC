/* parser.stmt.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "parser.hpp"
#include "stmt.hpp"

#include <iostream>

Stmt* Parser::parseStmt() {
    switch (lookahead()) {
        case Token::mySColonToken:
            return parseEmptyStmt();
        case Token::myLBraceToken:
            return parseBlockStmt();
        case Token::myIfKW:
            return parseIfStmt();
        case Token::myWhileKW:
            return parseWhileStmt();
        case Token::myBreakKW:
            return parseBreakStmt();
        case Token::myContKW:
            return parseContStmt();
        case Token::myVarKW:
        case Token::myRefKW:
            return parseDeclStmt();
        default:
            return parseExprStmt();
    }
}

Stmt* Parser::parseEmptyStmt() {
    require(Token::mySColonToken);
    return new skipStmt();
}

Stmt* Parser::parseBlockStmt() {
    require(Token::myLBraceToken);

    std::vector<Stmt*> ss;
    while (nextTokenIsNot(Token::myRBraceToken)) {
        Stmt * s = parseStmt();
        ss.push_back(s);
    }

    expect(Token::myRBraceToken);
    return new blockStmt(std::move(ss));
}

Stmt* Parser::parseIfStmt() {
    require(Token::myIfKW);
    expect(Token::myLParenToken);
    Expr *cond = parseExpr();
    expect(Token::myRParenToken);
    Stmt* ts = parseStmt();
    expect(Token::myElseKW);
    Stmt* fs = parseStmt();
    return new ifStmt(cond, ts, fs);
}

Stmt* Parser::parseWhileStmt() {
    require(Token::myWhileKW);
    expect(Token::myLParenToken);
    Expr *cond = parseExpr();
    expect(Token::myRParenToken);
    Stmt* body = parseStmt();
    return new whileStmt(cond, body);
}

Stmt* Parser::parseBreakStmt() {
    require(Token::myBreakKW);
    expect(Token::mySColonToken);
    return new breakStmt();
}

Stmt* Parser::parseContStmt() {
    require(Token::myContKW);
    expect(Token::mySColonToken);
    return new contStmt();
}

Stmt* Parser::parseReturnStmt() {
    require(Token::myRetKW);
    Expr* ret = parseExpr();
    expect(Token::mySColonToken);
    return new returnStmt(ret);
}

Stmt* Parser::parseDeclStmt() {
    Decl* d = parseLocalDecl();
    return new declStmt(d);
}

Stmt* Parser::parseExprStmt() {
    Expr *expr = parseExpr();
    expect(Token::mySColonToken);
    return new exprStmt(expr);
}
