/* type.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "type.hpp"

char const* Type::getTypeName() const {
    switch (myKind) {
        case myBoolType:
            return "bool type";
        case myIntType:
            return "int type";
        case myFloatType:
            return "float type";
        case myRefType:
            return "reference type";
        case myFuncType:
            return "function type";
    }
    assert(false);
}

bool Type::isReferenceTo(Type const* that) const {
    if (isReference()) {
        refType const* thisRef = static_cast<refType const*>(this);
    if (isSame(thisRef->getObjectType(), that))
        return true;
    }
    return false;
}

// Support functions for isSameType
bool isSame(Type const* typeOne, Type const* typeTwo) {
    return typeOne->isSameType(typeTwo);
}

static bool isSameRef(refType const* refOne, refType const* refTwo) {
    return isSame(refOne->getChild(), refTwo->getChild());
}

static bool isSameFunc(funcType const* funcOne, funcType const* funcTwo) {
    return std::equal(funcOne->begin(), funcOne->end(),
                      funcTwo->begin(), funcTwo->end(), isSame);
}

// Function to determine if two values have the same type
bool Type::isSameType(Type const* that) const {
    //If different base types, return false
    if (myKind != that->myKind)
        return false;
    //If reference or function, look at operands
    if (myKind == myRefType)
        return isSameRef(static_cast<refType const*>(this), static_cast<refType const*>(that));
    if (myKind == myFuncType)
        return isSameFunc(static_cast<funcType const*>(this), static_cast<funcType const*>(that));
    // Remaining types are bool, int, and float (already checked)
    return true;
}
