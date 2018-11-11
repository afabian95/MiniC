/* lexer.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <unordered_map>

#include "token.hpp"

class Lexer {
public:
    Lexer(symbolTable& symbs, char const* first, char const* limit);
    Lexer(symbolTable& symbs, std::string const& str);
    Token getNextToken();

private:
    symbolTable* mySymbs;
    char const* myFirst;
    char const* myLimit;
    int myLine;
    std::unordered_map<std::string, Token::Kind> myKWs;

public:
    bool isEOF(char const* ptr) const { return ptr == myLimit; }
    bool isEOF() const { return isEOF(myFirst); }
    char peek() const;
    char peek(int n) const;
    char consume() { return *myFirst++; }
    bool isDigit(char c);
    bool isNonDigit(char c);
    bool isDigitOrNonDigit(char c);
    bool isHexDigit(char c);
    Token match(Token::Kind k, int len);
    Token matchNumber();
    Token matchWord();
};

