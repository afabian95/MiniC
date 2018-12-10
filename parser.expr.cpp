/* parser.expr.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "parser.hpp"

#include <iostream>

Expr* Parser::parseExpr() {
    return parseAssignExpr();
}

// Parse an assignment expression
// assignment-expression -> additive-expression '='
// assignment-expression | additive-expression
Expr* Parser::parseAssignExpr() {
    Expr *expr = parseAddExpr();
    if (match(Token::myEqToken))
        return parseAssignExpr();
    return expr;
}

// Parse an additive expression
// additive-expression -> multiplicative-expression additive-expression-rest
Expr* Parser::parseAddExpr() {
    Expr *expr = parseMultExpr();
    while (match(Token::myPlusToken) || match(Token::myMinusToken))
        parseMultExpr();
    return expr;
}

// multiplicative-expression -> multiplicative-expression '*' postfix-expression
// multiplicative-expression -> multiplicative-expression '/' postfix-expression
// multiplicative-expression -> multiplicative-expression '%' postfix-expression
// multiplicative-expression -> prefix-expression
Expr* Parser::parseMultExpr() {
    Expr* lhs = parsePrefixExpr();
    while (true) {
        if (Token star = match(Token::myStarToken)) {
            Expr* rhs = parsePrefixExpr();
            lhs = myActions.onMultExpr(lhs, rhs);
        } else if (Token slash = match(Token::mySlashToken)) {
            Expr* rhs = parsePrefixExpr();
            lhs = myActions.onDivQuoExpr(lhs, rhs);
        } else if (Token percent = match(Token::myPercentToken)) {
            Expr* rhs = parsePrefixExpr();
            lhs = myActions.onDivRemExpr(lhs, rhs);
        }
    }
}

// prefix-expression -> '-' prefix-expression
// prefix-expression -> '/' prefix-expression
// prefix-expression -> postfix-expression
Expr* Parser::parsePrefixExpr() {
    if (Token op = match(Token::myMinusToken)) {
        Expr* arg = parsePrefixExpr();
        return myActions.onNegExpr(arg);
    } else if (Token op = match(Token::mySlashToken)) {
        Expr* arg = parsePrefixExpr();
        return myActions.onRecExpr(arg);
    }
    parsePostfixExpr();
    return nullptr;
}

// postfix-expression -> postfix-expression '(' argument-list ')'
// postfix-expression -> primary-expression
Expr* Parser::parsePostfixExpr() {
    parsePrimaryExpr();
    while (true) {
        if (match(Token::myLParenToken)) {
            expect(Token::myRParenToken);
        } else {
            break;
        }
    }
    return nullptr;
}

// Parse a primary-expression.
// primary-expression -> integer-literal
// primary-expression -> float-literal
// primary-expression -> identifier
// primary-expression -> '(' expression ')'
Expr* Parser::parsePrimaryExpr() {
    if (Token tok = match(Token::myIntLitToken))
        return myActions.onIntLit(tok);
    else if (Token tok = match(Token::myIdToken))
        return myActions.onIdExpr(tok);
    else if (match(Token::myLParenToken)) {
        Expr* expr = parseExpr();
        expect(Token::myRParenToken);
        return expr;
    }
    throw std::runtime_error("expected factor");
}
