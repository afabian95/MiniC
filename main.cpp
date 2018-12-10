/* main.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "parser.hpp"

#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>

// Tests the parser
int main(int argc, char* argv[]) {
  std::ifstream ifs(argv[1]);
  std::istreambuf_iterator<char> first(ifs);
  std::istreambuf_iterator<char> limit;
  std::string input(first, limit);

  symbolTable syms;

  Parser parse(syms, input);
  parse.parseExpr();
}


