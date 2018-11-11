/* lexer.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include <iostream>

#include "lexer.hpp"

Lexer::Lexer(symbolTable& symbs, char const* first, char const* limit) :
    mySymbs(&symbs), myFirst(first), myLimit(limit), myLine(1) {
    myKWs.emplace("and", Token::myAndKW);
    myKWs.emplace("bool", Token::myBoolKW);
    myKWs.emplace("break", Token::myBreakKW);
    myKWs.emplace("continue", Token::myContKW);
    myKWs.emplace("else", Token::myElseKW);
    myKWs.emplace("false", Token::myFalseKW);
    myKWs.emplace("fun", Token::myFuncKW);
    myKWs.emplace("if", Token::myIfKW);
    myKWs.emplace("int", Token::myIntKW);
    myKWs.emplace("not", Token::myNotKW);
    myKWs.emplace("or", Token::myOrKW);
    myKWs.emplace("ref", Token::myRefKW);
    myKWs.emplace("return", Token::myRetKW);
    myKWs.emplace("true", Token::myTrueKW);
    myKWs.emplace("var", Token::myVarKW);
    myKWs.emplace("while", Token::myWhileKW);
}

Lexer::Lexer(symbolTable& symbs, std::string const& str) :
    Lexer(symbs, str.data(), str.data() + str.size()) {}

Token Lexer::getNextToken() {
    while (true) {
        switch (peek()) {
        case ' ':
        case '\t': consume(); continue;
        case '\n': myLine++; consume(); continue;
        case '{': return match(Token::myLBraceToken, 1);
        case '}': return match(Token::myRBraceToken, 1);
        case '(': return match(Token::myLParenToken, 1);
        case ')': return match(Token::myRParenToken, 1);
        case ',': return match(Token::myCommaToken, 1);
        case ';': return match(Token::mySColonToken, 1);
        case ':': return match(Token::myColonToken, 1);
        case '+': return match(Token::myPlusToken, 1);
        case '-': return match(Token::myMinusToken, 1);
        case '*': return match(Token::myStarToken, 1);
        case '/': return match(Token::mySlashToken, 1);
        case '%': return match(Token::myPercentToken, 1);
        case '<':
            if (peek(1) == '=')
                return match(Token::myLTEToken, 2);
            return match(Token::myLTToken, 1);
        case '>':
            if (peek(1) == '=')
                return match(Token::myGTEToken, 2);
            return match(Token::myGTToken, 1);
        case '=':
            if (peek(1) == '=')
                return match(Token::myEqEqToken, 2);
            return match(Token::myEqToken, 1);
        case '!':
            if (peek(1) == '=')
                return match(Token::myNEqToken, 2);
            consume();
            std::cerr << "Error: " << myLine << ": " << "expected '=' after '!'.\n";
            continue;
        default:
            if (isDigit(*myFirst)) {
                return matchNumber();
                continue;
            }
            if (isNonDigit(*myFirst)) {
                return matchWord();
                continue;
            }
            std::cerr << "Error: " << myLine << ": invalid character.";
            consume();
            continue;
        }
    }
}

char Lexer::peek() const {
    if (isEOF())
        return 0;
    return *myFirst;
}

char Lexer::peek(int n) const {
    if (myLimit - myFirst <= n)
        return 0;
    return *(myFirst + n);
}

Token Lexer::match(Token::Kind k, int len) {
    std::string str(myFirst, myFirst + len);
    Symbol symb = mySymbs->get(str);
    Token tok = Token(k, symb);
    myFirst += len;
    return tok;
}

bool Lexer::isDigit(char c) {
    return std::isdigit(c);
}

bool Lexer::isNonDigit(char c) {
    return std::isalpha(c) || c == '_';
}

bool Lexer::isDigitOrNonDigit(char c) {
    return isDigit(c) || isNonDigit(c);
}

bool Lexer::isHexDigit(char c) {
    return std::isxdigit(c);
}

Token Lexer::matchWord() {
    char const* word = myFirst + 1;
    while (!isEOF(word) && isDigitOrNonDigit(*word))
        word++;
    myFirst = word;

    std::string id(myFirst, word);
    Symbol symb = mySymbs->get(id);

    Token::Kind kind;
    auto kw = myKWs.find(id);
    kind = kw->second;
    return Token(kind, symb);
}

Token Lexer::matchNumber() {
    char const* number = myFirst + 1;
    while (!isEOF(number) && isDigit(*number))
        number++;
    myFirst = number;

    std::string id(myFirst, number);
    Symbol symb = mySymbs->get(id);

    Token::Kind kind;
    auto kw = myKWs.find(id);
    kind = kw->second;
    return Token(kind, symb);
}
