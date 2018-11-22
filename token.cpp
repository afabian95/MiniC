/* token.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "token.hpp"

#include <cassert>
#include <iostream>

// Converts tokens to strings
static char const* str(Token::Kind k) {
    switch (k) {
        case Token::myLBraceToken: return "lbrace";
        case Token::myRBraceToken: return "rbrace";
        case Token::myLParenToken: return "lparen";
        case Token::myRParenToken: return "rparen";
        case Token::myColonToken: return "colon";
        case Token::mySColonToken: return "semicolon";
        case Token::myCommaToken: return "comma";
        case Token::myArrowToken: return "arrow";

        case Token::myPlusToken: return "plus";
        case Token::myMinusToken: return "minus";
        case Token::myStarToken: return "star";
        case Token::mySlashToken: return "slash";
        case Token::myPercentToken: return "percent";
        case Token::myQuestionToken: return "question";
        case Token::myEqToken: return "equal";
        case Token::myEqEqToken: return "equal_equal";
        case Token::myNEqToken: return "bang_equal";
        case Token::myLTToken: return "less";
        case Token::myGTToken: return "greater";
        case Token::myLTEToken: return "less_equal";
        case Token::myGTEToken: return "greater_equal";

        case Token::myAndKW: return "and_kw";
        case Token::myBoolKW: return "bool_kw";
        case Token::myBreakKW: return "break_kw";
        case Token::myContKW: return "continue_kw";
        case Token::myElseKW: return "else_kw";
        case Token::myFalseKW: return "false_kw";
        case Token::myFuncKW: return "fun_kw";
        case Token::myIfKW: return "if_kw";
        case Token::myIntKW: return "int_kw";
        case Token::myNotKW: return "not_kw";
        case Token::myOrKW: return "or_kw";
        case Token::myRefKW: return "ref_kw";
        case Token::myRetKW: return "return_kw";
        case Token::myTrueKW: return "true_kw";
        case Token::myVarKW: return "var_kw";
        case Token::myWhileKW: return "while_kw";

        case Token::myIntLitToken: return "integer_literal";
        case Token::myFloatLitToken: return "float_literal";

        case Token::myIdToken: return "identifier";
        case Token::myEOFToken: return "eof";
    }
    assert(false);
}

std::ostream& operator<<(std::ostream& os, Token const& t) {
    return os << "<" << str(t.getTokenKind()) << ">";
}
