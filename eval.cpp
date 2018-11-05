/* eval.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "eval.hpp"
#include "decl.hpp"

Object* Eval::allocateStatic(Decl* d) {
    return myGlobalVars.allocate(d);
}

Object* Eval::allocateAutomatic(Decl* d) {
    return getCurrentFrame()->allocateLocalVars(d);
}

static MonotonicStore& getStore(Eval& eval, int store) {
    if (store == -1)
        return eval.getGlobalVars();
    return eval.getStack().getFrame(store)->getLocalVars();
}

Object* Eval::locateObject(Value const& val) {
    addrValue addr = val.getAddress();
    MonotonicStore& store = getStore(*this, addr.store);
    return store.locate(addr.def);
}

Decl* Eval::getCurrentFunction() const {
    return getCurrentFrame()->getFunction();
}

Frame* Eval::pushFrame(Decl* d) {
    assert(d->isFunction());
    funcDecl* func = static_cast<funcDecl*>(d);
    Frame* frame = myStack.push(func);

    for (Decl* localVar : func->getChildren()) {
    if (!localVar->isVariable())
      continue;
    frame->allocateLocalVars(localVar);
    }
    return frame;
}

void Eval::popFrame() {
    myStack.pop();
}
