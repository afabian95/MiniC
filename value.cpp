/* value.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "value.hpp"
#include "name.hpp"
#include "decl.hpp"

#include <iostream>

// Prints value
std::ostream& operator<<(std::ostream& os, Value const& v) {
    switch (v.getValueKind()) {
        case Value::myNonVal:
            return os << "<indeterminate>";
        case Value::myIntVal:
            return os << v.getInt();
        case Value::myFloatVal:
            return os << v.getFloat();
        case Value::myFuncVal: {
            funcDecl* func = v.getFunction();
            os << '<' << "function" << ' ' << *func->getName() << ' ' << func << '>';
            return os;
        }
        case Value::myAddrVal: {
            addrValue const& addr = v.getAddress();
            os << '<';
            if (addr.store == -1) os << "static";
            else os << "auto" << '(' << addr.store << ')';
            os << ' ' << *addr.def->getName() << ' ' << addr.def << '>';
            return os;
        }
        default:
            break;
    }
    os << "<unknown>";
    return os;
}
