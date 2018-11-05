/* decl.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "decl.hpp"
#include "name.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "printer.hpp"

#include <iostream>

char const* Decl::getDeclName() const {
    switch (myKind) {
        case myVarDecl:
            return "variable declaration";
        case myFuncDecl:
            return "function declaration";
        case myProgDecl:
            return "program declaration";
    }
    assert(false);
}

bool Decl::isObject() const {
  return isVariable() && getType()->isObject();
}

bool Decl::isReference() const {
  return isVariable() && getType()->isReference();
}

valDecl* Decl::getAsValue() {
    switch (myKind) {
        case myVarDecl:
            return static_cast<varDecl*>(this);
        case myFuncDecl:
            return static_cast<funcDecl*>(this);
        default:
            return nullptr;
    }
}

valDecl const* Decl::getAsValue() const {
    return const_cast<Decl*>(this)->getAsValue();
}


funcType* funcDecl::getFuncType() const {
    return static_cast<funcType*>(getType());
}

std::size_t funcDecl::getParamCount() const {
    return getFuncType()->getParamCount();
}

//TODO: Add accessors to getChildren()
//NodeRange<Decl> funcDecl::getParams() {
//    return getChildren().front(getParamCount());
//}

//NodeRange<Decl const> funcDecl::getParams() const {
//    return getChildren().front(getParamCount());
//}

void funcDecl::setParams(std::vector<Decl*> const& params) {
    for (Decl* p : params)
        addParam(p);
}

void funcDecl::setParams(std::initializer_list<Decl*> params) {
    for (Decl* p : params)
        addParam(p);
}

void funcDecl::addParam(Decl* d) {
    assert(d->isVariable());
//    assert(getChildren().size() <= getParamCount());
//    addChild(d);
}

Decl* funcDecl::getReturn() {
    Decl* lastChild = nullptr;
    for (auto child:getChildren()){
        lastChild = child;
    }
    return lastChild;
}

Decl const* funcDecl::getReturn() const {
    Decl* lastChild = nullptr;
    for (auto child:getChildren()){
        lastChild = child;
    }
    return lastChild;
}

void funcDecl::setReturn(Decl* d) {
    assert(d->isVariable());
    //assert(getChildren().size() == getParamCount());
    //add_child(d);
}
