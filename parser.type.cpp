/* parser.type.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "parser.hpp"
#include "type.hpp"

#include <iostream>

Type* Parser::parseType() {
    switch (lookahead()) {
        case Token::myBoolKW:
            return parseBoolType();
        case Token::myIntLitToken:
            return parseIntType();
        case Token::myFloatLitToken:
            return parseFloatType();
        case Token::myRefKW:
            return parseRefType();
        default:
            return parseFuncType();
    }
}

Type* Parser::parseBoolType() {
    require(Token::myBoolKW);
    return new boolType();
}

Type* Parser::parseIntType() {
    require(Token::myIntLitToken);
    return new intType();
}

Type* Parser::parseFloatType() {
    require(Token::myFloatLitToken);
    return new floatType();
}

Type* Parser::parseRefType() {
    require(Token::myRefKW);
    Type* t = parseType();
    return new refType(t);
}

Type* Parser::parseFuncType() {
    require(Token::myFuncKW);
    expect(Token::myLParenToken);

    std::vector<Type*> tt;
    while (nextTokenIsNot(Token::myRParenToken)) {
        Type * t = parseType();
        tt.push_back(t);
    }

    expect(Token::myRParenToken);
    expect(Token::myArrowToken);
    Type * t = parseType();
    tt.push_back(t);
    return new funcType(std::move(tt));
}
