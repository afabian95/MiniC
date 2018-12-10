/* token.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "symbol.hpp"

class Location {};

class Token {
public:
    enum Name {
    // punctuation
    myLBraceToken,  // [ token
    myRBraceToken,  // ] token
    myLParenToken,  // ( token
    myRParenToken,  // ) token
    myColonToken,   // : token
    mySColonToken,  // ; token
    myCommaToken,   // , token
    myArrowToken,   // -> token

    // operators
    myPlusToken,    // + token
    myMinusToken,   // - token
    myStarToken,    // * token
    mySlashToken,   // / token
    myPercentToken, // % token
    myQuestionToken,// ? token
    myEqToken,      // = token
    myEqEqToken,    // == token
    myNEqToken,     // != token
    myLTToken,      // < token
    myGTToken,      // > token
    myLTEToken,     // <= token
    myGTEToken,     // >= token

    // keywords
    myAndKW,        // AND keyword
    myBoolKW,       // boolean keyword
    myBreakKW,      // break keyword
    myContKW,       // continue keyword
    myElseKW,       // else keyword
    myFalseKW,      // false keyword
    myFuncKW,       // function keyword
    myIfKW,         // if keyword
    myIntKW,        // integer keyword
    myNotKW,        // NOT keyword
    myOrKW,         // OR keyword
    myRefKW,        // reference keyword
    myRetKW,        // return keyword
    myTrueKW,       // true keyword
    myVarKW,        // variable keyword
    myWhileKW,      // while keyword

    // literals
    myIntLitToken,  // integer literal
    myFloatLitToken,// floating point literal

    //misc
    myIdToken,      // identifier
    myEOFToken,     // end of file
  };

private:
    Name myName;
    Symbol myLex;
    Location myLoc;

public:
    Token() :
        Token(myEOFToken, Symbol()) {}
    Token(Name n, Symbol sym, Location = {}) :
        myName(n), myLex(sym), myLoc() {}

    // Operators
    // Converts to true when this is not end of file
    explicit operator bool() const { return myName != myEOFToken; }
    // Returns the name of the token
    Name getTokenName() const { return myName; }
    // Returns the spelling of the token
    Symbol getLexeme() const { return myLex; }
    // Returns whether this is the same keyword
    bool isSameAs(Name name) const { return myName == name; }
    // Returns whether this is a keyword
    bool isKeyword() const;
    // Returns whether this is a logical operator
    bool isLogicalOperator() const;
};

std::ostream& operator<<(std::ostream& os, Token const& t);
