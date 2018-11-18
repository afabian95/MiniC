/* type.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "type.hpp"

char const* Type::getTypeName() const {
    switch (myKind) {
        case myBoolType:
            return "bool_type";
        case myIntType:
            return "int_type";
        case myFloatType:
            return "float_type";
        case myRefType:
            return "ref_type";
        case myFuncType:
            return "func_type";
    }
    assert(false);
}

bool Type::isReferenceTo(Type const* inputType) const {
    if (isReference()) {
        refType const* rType = static_cast<refType const*>(this);
    if (isSameType(rType->getObjectType(), inputType))
        return true;
    }
    return false;
}

// Support functions for isSameType
bool isSameAs(Type const* typeOne, Type const* typeTwo) {
    return isSameType(typeOne, typeTwo);
}

static bool isSameRef(refType const* refOne, refType const* refTwo) {
    return isSameType(refOne->getChild(), refTwo->getChild());
}

static bool isSameFunc(funcType const* funcOne, funcType const* funcTwo) {
    return std::equal(funcOne->begin(), funcOne->end(),
                      funcTwo->begin(), funcTwo->end(), isSameType);
}

// Function to determine if two values have the same type
bool isSameType(Type const* typeOne, Type const* typeTwo) {
    //If different base types, return false
    if (typeOne->getTypeKind() != typeTwo->getTypeKind())
        return false;
    //If reference or function, look at operands
    switch (typeOne->getTypeKind()) {
        case Type::myRefType:
            return isSameRef(static_cast<refType const*>(typeOne),
                             static_cast<refType const*>(typeTwo));
        case Type::myFuncType:
            return isSameFunc(static_cast<funcType const*>(typeOne),
                              static_cast<funcType const*>(typeTwo));
        // Bool, int, and float already covered
        default:
            return true;
    }
}
