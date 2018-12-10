/* parser.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "parser.hpp"

#include <iostream>

Parser::Parser(symbolTable& syms, std::string const& input) : myLex(syms, input) {
    // Pull all of the tokens in one shot.
    while (Token tok = myLex.getNextToken())
        myTokens.push_back(tok);

    myLookahead = myTokens.data();
    myLast = myLookahead + myTokens.size();
}

Token Parser::consume() {
    assert(!isEndOfFile());
    Token ret = *myLookahead;
    ++myLookahead;
    return ret;
}

Token Parser::match(Token::Name n) {
    if (nextTokenIs(n))
        return consume();
    return Token();
}

Token Parser::expect(Token::Name n) {
    if (nextTokenIs(n))
        return consume();

    throw std::runtime_error("Syntax error");
    return Token();
}

Token Parser::require(Token::Name n) {
    assert(nextTokenIs(n));
    return consume();
}
