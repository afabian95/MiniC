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

bool Type::isSameTypeAs(Type const* inputType) const {
    return isSameType(this, inputType);
}

// Support function for isSameType
static bool isSameRef(refType const* refOne, refType const* refTwo) {
    return isSameType(refOne->getChild(), refTwo->getChild());
}

// Support function for isSameType
static bool isSameFunc(funcType const* funcOne, funcType const* funcTwo) {
    return std::equal(funcOne->begin(), funcOne->end(),
                      funcTwo->begin(), funcTwo->end(), isSameType);
}

// Accepts two types and returns whether they are equal
bool isSameType(Type const* typeOne, Type const* typeTwo) {
    if (typeOne->getTypeKind() != typeTwo->getTypeKind())
        return false;
    switch (typeOne->getTypeKind()) {
        case Type::myRefType:
            return isSameRef(static_cast<refType const*>(typeOne),
                             static_cast<refType const*>(typeTwo));
        case Type::myFuncType:
            return isSameFunc(static_cast<funcType const*>(typeOne),
                              static_cast<funcType const*>(typeTwo));
        default:
            return true;
    }
}
