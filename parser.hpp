/* parser.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "token.hpp"
#include "lexer.hpp"
#include "actions.hpp"

#include <cassert>
#include <vector>

class symbolTable;
class Type;
class Expr;
class Stmt;
class Decl;

// The parser class
class Parser {
public:
    Parser(symbolTable& syms, std::string const& input);

private:
    // The lexer
    Lexer myLex;
    // Holds the string being parsed
    std::vector<Token> myTokens;
    // The current token index
    Token* myLookahead;
    // Points past the end of the token buffer
    Token* myLast;
    // The semantic actions for the parser
    Actions myActions;

    // Helper functions
    // True if end of file
    bool isEndOfFile() const { return myLookahead == myLast; }
    // Peeks at the lookahead token
    const Token& peek() const { return *myLookahead; }
    // Returns the name of the lookahead token
    Token::Name lookahead() const { return peek().getTokenName(); }
    // True if the lookahead is n
    bool nextTokenIs(Token::Name n) const { return lookahead() == n; }
    // True if the lookahead is not n
    bool nextTokenIsNot(Token::Name n) { return lookahead() != n; }
    // Advance to the next token
    Token consume();
    // If lookahead is n, consume. Otherwise, return end of file
    Token match(Token::Name n);
    // If lookahead is n, consume. Otherwise, return an error
    Token expect(Token::Name n);
    // If lookahead is n, consume. Otherwise, unexpected behavior
    Token require(Token::Name n);

public:
    // Parsing functions
    // Parse a program
    void parseProgram();

    // Expressions
    // Parse an expression
    Expr* parseExpr();
    // Parse an assignment expression
    Expr* parseAssignExpr();
    // Parse an additive expression
    Expr* parseAddExpr();
    // Parse a multiplicative expression
    Expr* parseMultExpr();
    // Parse a prefix-expression
    Expr* parsePrefixExpr();
    // Parse a postfix expression
    Expr* parsePostfixExpr();
    // Parse a factor
    Expr* parsePrimaryExpr();

    // Statements
    // Parse a statement
    Stmt* parseStmt();
    // Parse an empty statement
    Stmt* parseEmptyStmt();
    // Parse a block statement
    Stmt* parseBlockStmt();
    // Parse an if statement
    Stmt* parseIfStmt();
    // Parse a while statement
    Stmt* parseWhileStmt();
    // Parse a break statement
    Stmt* parseBreakStmt();
    // Parse a continue statement
    Stmt* parseContStmt();
    // Parse a return statement
    Stmt* parseReturnStmt();
    // Parse a declaration statement
    Stmt* parseDeclStmt();
    // Parse an expression statement
    Stmt* parseExprStmt();

    // Types
    // Parse a type
    Type* parseType();
    // Parse a boolean type
    Type* parseBoolType();
    // Parse an integer type
    Type* parseIntType();
    // Parse a floating point type
    Type* parseFloatType();
    // Parse a reference type
    Type* parseRefType();
    // Parse a function type
    Type* parseFuncType();

    // Declarations
    // Parse a declaration
    Decl* parseDecl();
    // Parse a local declaration
    Decl* parseLocalDecl();
    // Parse a function definition
    Decl* parseFuncDef();
    // Parse an object definition
    Decl* parseObjectDef();

};
