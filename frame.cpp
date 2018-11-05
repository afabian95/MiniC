/* frame.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "frame.hpp"

#include <iostream>

Object* Frame::allocateLocalVars(Decl* d) {
    return myLocalVars.allocate(d);
}

Object* Frame::locateLocalVars(Decl* d) {
    return myLocalVars.locate(d);
}

void Frame::aliasLocalVars(Decl* d, Object* obj) {
    myLocalVars.alias(d, obj);
}

Frame* CallStack::push(Decl* func) {
    myTop = new Frame(myTop, func);
    myFrames.push_back(myTop);
    return myTop;
}

void CallStack::pop() {
    myTop = myTop->getCaller();
    delete myFrames.back();
    myFrames.pop_back();
}
