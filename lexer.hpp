/* lexer.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <unordered_map>

#include "token.hpp"

// The general lexer class
class Lexer {
public:
    // Constructs the lexer
    Lexer(symbolTable& symbs, char const* first, char const* limit);
    // Constructs the lexer from a string
    Lexer(symbolTable& symbs, std::string const& str);
    // Returns the next token in the input buffer
    Token getNextToken();

private:
    symbolTable* mySymbs;
    char const* myFirst;
    char const* myLimit;
    int myLine;
    std::unordered_map<std::string, Token::Name> myKWs;

public:
    // True if all input is consumed
    bool isEOF(char const* ptr) const { return ptr == myLimit; }
    bool isEOF() const { return isEOF(myFirst); }
    // Returns the current character
    char peek() const;
    // Returns the nth character past the current character
    char peek(int n) const;
    // Returns the current character, increments
    char consume() { return *myFirst++; }
    // Returns whether the current character is a digit
    bool isDigit(char c);
    // Returns whether the current character is a non-digit
    bool isNonDigit(char c);
    // Returns whether the current character is a digit or non-digit
    bool isDigitOrNonDigit(char c);
    // Returns whether the current character is a hex digit
    bool isHexDigit(char c);
    // Returns the token that matches the string
    Token match(Token::Name n, int len);
    // Returns the token that matches the number
    Token matchNumber();
    // Returns the token that matches the word
    Token matchWord();
};

