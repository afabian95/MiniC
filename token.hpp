/* token.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "symbol.hpp"

class Location {};

class Token {
public:
    enum Kind {
    // punctuation
    myLBraceToken,  // [
    myRBraceToken,  // ]
    myLParenToken,  // (
    myRParenToken,  // )
    myColonToken,   // :
    mySColonToken,  // ;
    myCommaToken,   // ,
    myArrowToken,   // ->

    // operators
    myPlusToken,    // +
    myMinusToken,   // -
    myStarToken,    // *
    mySlashToken,   // /
    myPercentToken, // %
    myQuestionToken,// ?
    myEqToken,      // =
    myEqEqToken,    // ==
    myNEqToken,     // !=
    myLTToken,      // <
    myGTToken,      // >
    myLTEToken,     // <=
    myGTEToken,     // >=

    // keywords
    myAndKW,        // AND
    myBoolKW,       // bool
    myBreakKW,      // break
    myContKW,       // continue
    myElseKW,       // else
    myFalseKW,      // false
    myFuncKW,       // fun
    myIfKW,         // if
    myIntKW,        // int
    myNotKW,        // NOT
    myOrKW,         // OR
    myRefKW,        // ref
    myRetKW,        // return
    myTrueKW,       // true
    myVarKW,        // var
    myWhileKW,      // while

    // literals
    myIntLitToken,  // integer literal
    myFloatLitToken,// floating point literal

    //misc
    myIdToken,      // identifier
    myEOFToken,     // end of file
  };

private:
    Kind myKind;
    Symbol myLex;
    Location myLoc;

public:
    Token(Kind k, Symbol sym, Location = {}) :
        myKind(k), myLex(sym), myLoc() {}

    // Operators
    explicit operator bool() const { return myKind != myEOFToken; }
    Kind getTokenKind() const { return myKind; }
    Symbol getLexeme() const { return myLex; }
    bool isKeyword() const;
    bool isLogicalOperator() const;
};

std::ostream& operator<<(std::ostream& os, Token const& t);
