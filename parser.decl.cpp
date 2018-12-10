/* parser.decl.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "actions.hpp"
#include "parser.hpp"

void Parser::parseProgram() {
    myActions.enterScope();
    parseDeclStmt();
    myActions.leaveScope();
}

Decl* Parser::parseLocalDecl() {
  return parseObjectDef();
}

// object-definition -> var identifier : type = expression ;
Decl* Parser::parseObjectDef() {
    require(Token::myVarKW);
    Token id = expect(Token::myIdToken);
    expect(Token::myColonToken);
    Type* type = parseType();
    Decl* var = myActions.onObjectDecl(id, type);
    expect(Token::myEqToken);
    Expr* init = parseExpr();
    expect(Token::mySColonToken);

    myActions.finishObjectDecl(var, init);

    return var;
}

// function-definition -> fun identifier (parameter-list?) -> type block-statement
Decl* Parser::parseFuncDef() {
    require(Token::myFuncKW);
    Token id = expect(Token::myIdToken);

    expect(Token::myLParenToken);
    myActions.enterScope();

    std::vector<Decl*> params;
    if (nextTokenIsNot(Token::myRParenToken)) {
       // params = parseParamDecl();
    }
    expect(Token::myRParenToken);

    expect(Token::myArrowToken);
    Type* type = parseType();

    Decl* var = myActions.onFuncDecl(id, params, type);

    parseStmt();

    myActions.leaveScope();

    return var;
}
