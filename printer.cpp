/* printer.cpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include <iostream>
#include "printer.hpp"

void Printer::printIndentation() {
    for (int i = 0; i < myIndent; i++)
        myOstream << " ";
}

void Printer::printNewline() {
    myOstream << "\n";
}

void Printer::printString(char const* str) {
    myOstream << str;
}

void Printer::printAddress(void const* ptr) {
    myOstream << ptr;
}
