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
    // Returns the global store
    MonotonicStore& getGlobalVars() { return myGlobalVars; }
    // Allocate static storage for a declaration
    Object* allocateStatic(Decl* d);
    // Allocate automatic storage for a declaration in the current frame
    Object* allocateAutomatic(Decl* d);
    // Locate the object for an address value
    Object* locateObject(Value const& val);

    // Call stack
    // Returns the call stack
    CallStack& getStack() { return myStack; }
    // Returns the current function
    Decl* getCurrentFunction() const;
    // Returns the current frame
    Frame* getCurrentFrame() const { return myStack.getTop(); }
    // Push a frame onto the call stack
    Frame* pushFrame(Decl* func);
    // Pop a frame from the call stack
    void popFrame();
};

// Operations
// Determines flow control after executing a statement
enum Control {
    nextFunc,
    breakFunc,
    contFunc,
    returnFunc,
};

// Evaluate an expression in the given context
Value evalExpr(Eval& eval, Expr const* e);
// Evaluate a statement in the given context
Control evalStmt(Eval& eval, Stmt const* e);
// Evaluate a declaration in the given context
void evalDecl(Eval& eval, Decl const* e);
