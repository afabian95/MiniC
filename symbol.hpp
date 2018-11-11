/* symbol.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <string>
#include <unordered_set>

class Symbol {
    class symbolTable;

private:
    std::string const* myStr;

public:
    Symbol(std::string const* str) : myStr(str) { }
    std::string const& str() const { return *myStr; }
    friend bool operator ==(Symbol a, Symbol b) { return a.myStr == b.myStr; }
    friend bool operator !=(Symbol a, Symbol b) { return a.myStr != b.myStr; }
};


class symbolTable : std::unordered_set<std::string> {
public:
    Symbol get(std::string const& str);
    Symbol get(char const* str);
};
inline Symbol symbolTable::get(std::string const& str) {
    return &*emplace(str).first;
}
inline Symbol symbolTable::get(char const* str) {
    return &*emplace(str).first;
}
