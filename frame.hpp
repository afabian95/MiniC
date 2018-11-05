/* frame.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "store.hpp"

// The stack frame class
class Frame {
public:
    Frame(Frame* prev, Decl* func);

private:
    Frame* myPrev;
    Decl* myFunc;
    int myIndex;
    MonotonicStore myLocalVars;

public:
    Frame* getCaller() const { return myPrev; }
    Decl* getFunction() const { return myFunc; }
    int getIndex() const { return myIndex; }
    MonotonicStore& getLocalVars() { return myLocalVars; }
    Object* allocateLocalVars(Decl* d);
    Object* locateLocalVars(Decl* d);
    void aliasLocalVars(Decl* d, Object* obj);
};
inline Frame::Frame(Frame* prev, Decl* d) :
    myPrev(prev), myFunc(d), myIndex(prev ? (prev->myIndex + 1) : 0) {}


// The call stack class
class CallStack {
public:
    CallStack();
    Frame* push(Decl* func);
    void pop();

private:
    Frame* myTop;
    std::vector<Frame*> myFrames;

public:
    Frame* getTop() const { return myTop; }
    Frame* getFrame(int n) const { return myFrames[n]; }
};
inline CallStack::CallStack() :
    myTop(), myFrames() {}
