/* frame.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "store.hpp"

// The stack frame class
class Frame {
public:
    // Constructs the stack frame
    Frame(Frame* prev, Decl* func);

private:
    Frame* myPrev;
    Decl* myFunc;
    int myIndex;
    MonotonicStore myLocalVars;

public:
    // Returns the frame for the calling function
    Frame* getCaller() const { return myPrev; }
    // Returns the called function
    Decl* getFunction() const { return myFunc; }
    // Returns the index of the stack frame
    int getIndex() const { return myIndex; }
    // Returns the automatic store for local variables
    MonotonicStore& getLocalVars() { return myLocalVars; }
    // Allocates a local object
    Object* allocateLocalVars(Decl* d);
    // Returns the object defined by a declaration in this frame
    Object* locateLocalVars(Decl* d);
    // Creates an alias for an object in this frame
    void aliasLocalVars(Decl* d, Object* obj);
};
inline Frame::Frame(Frame* prev, Decl* d) :
    myPrev(prev), myFunc(d), myIndex(prev ? (prev->myIndex + 1) : 0) {}


// The call stack class
class CallStack {
public:
    CallStack();
    // Push a new frame onto the call stack
    Frame* push(Decl* func);
    // Pop a frame from the call stack
    void pop();

private:
    Frame* myTop;
    std::vector<Frame*> myFrames;

public:
    // Returns the top frame on the stack
    Frame* getTop() const { return myTop; }
    // Indexes into the call stack
    Frame* getFrame(int n) const { return myFrames[n]; }
};
inline CallStack::CallStack() :
    myTop(), myFrames() {}
