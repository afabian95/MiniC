/* eval.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "value.hpp"
#include "store.hpp"
#include "frame.hpp"

class Expr;
class Stmt;
class Decl;

// The evaluation class
class Eval {
public:
    Eval() = default;
    Eval(Eval const& x) = delete;
    Eval(Eval&& x) = delete;

private:
    MonotonicStore myGlobalVars;
    CallStack myStack;

public:
    MonotonicStore& getGlobalVars() { return myGlobalVars; }
    Object* allocateStatic(Decl* d);
    Object* allocateAutomatic(Decl* d);
    Object* locateObject(Value const& val);

    // Call stack
    CallStack& getStack() { return myStack; }
    Decl* getCurrentFunction() const;
    Frame* getCurrentFrame() const { return myStack.getTop(); }
    Frame* pushFrame(Decl* func);
    void popFrame();
};

// Operations
enum Control {
    nextFunc,
    breakFunc,
    contFunc,
    returnFunc,
};

Value evalExpr(Eval& eval, Expr const* e);
Control evalStmt(Eval& eval, Stmt const* e);
void evalDecl(Eval& eval, Decl const* e);
