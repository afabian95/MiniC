/* main.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "token.hpp"
#include "lexer.hpp"

#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>

// Tests the lexer
int main(int argc, char* argv[]) {
    std::ifstream ifs(argv[1]);
    std::istreambuf_iterator<char> first(ifs);
    std::istreambuf_iterator<char> limit;
    std::string input(first, limit);

    symbolTable symbs;

    Lexer lexer(symbs, input);

    while (Token tok = lexer.getNextToken()) {
        std::cout << tok << '\n';
    }
}
