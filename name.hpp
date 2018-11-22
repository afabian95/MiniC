/* name.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <iosfwd>

class Printer;

// Represents the name of a declaration.
class Name
{
public:
    // Constructs the name using a string
    Name(const char* str);
    // Returns the spelling of the name
    char const* getString() const { return myStr; }

private:
    char const* myStr;
};
inline Name::Name(char const* str) : myStr(str) {}

// Operations
void printName(Printer& p, Name const* n);

std::ostream& operator<<(std::ostream& os, Name const& n);
