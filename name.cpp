/* name.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "name.hpp"
#include "printer.hpp"

#include <iostream>

// Prints name
void printName(Printer& p, Name const* n) {
  p.getStream() << n->getString();
}

std::ostream& operator<< (std::ostream& os, Name const& n) {
  Printer p(os);
  printName(p, &n);
  return os;
}
