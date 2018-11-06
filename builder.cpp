/* builder.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "builder.hpp"
#include "name.hpp"

Name* Builder::getName(char const* str) {
    return new Name(str);
}
