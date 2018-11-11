/* token.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "token.hpp"

#include <cassert>
#include <iostream>

static char const* str(Token::Kind k) {
    switch (k) {
        case Token::myLBraceToken: return "left_brace";
        case Token::myRBraceToken: return "right_brace";
        case Token::myLParenToken: return "left_parenthesis";
        case Token::myRParenToken: return "right_parenthesis";
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
        case Token::myNEqToken: return "not_equal";
        case Token::myLTToken: return "less_than";
        case Token::myGTToken: return "greater_than";
        case Token::myLTEToken: return "less_than_or_equal";
        case Token::myGTEToken: return "greater_than_or_equal";

        case Token::myAndKW: return "and_keyword";
        case Token::myBoolKW: return "boolean_keyword";
        case Token::myBreakKW: return "break_keyword";
        case Token::myContKW: return "continue_keyword";
        case Token::myElseKW: return "else_keyword";
        case Token::myFalseKW: return "false_keyword";
        case Token::myFuncKW: return "function_keyword";
        case Token::myIfKW: return "if_keyword";
        case Token::myIntKW: return "integer_keyword";
        case Token::myNotKW: return "not_keyword";
        case Token::myOrKW: return "or_keyword";
        case Token::myRefKW: return "reference_keyword";
        case Token::myRetKW: return "return_keyword";
        case Token::myTrueKW: return "true_keyword";
        case Token::myVarKW: return "variable_keyword";
        case Token::myWhileKW: return "while_keyword";

        case Token::myIntLitToken: return "integer_literal";
        case Token::myFloatLitToken: return "float_literal";

        case Token::myIdToken: return "identifier";
        case Token::myEOFToken: return "end_of_file";
    }
    assert(false);
}

std::ostream& operator<<(std::ostream& os, Token const& t) {
    return os << "<" << str(t.getTokenKind()) << ">";
}
