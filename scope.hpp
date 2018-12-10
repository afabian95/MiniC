/* scope.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <cassert>
#include <vector>
#include <unordered_map>

#include "decl.hpp"
#include "symbol.hpp"

// The scope class for parsing
struct Scope : std::unordered_map<Symbol, Decl*> {
    Decl* lookup(Symbol sym) {
        auto iter = find(sym);
        if (iter == end())
            return nullptr;
        return iter->second;
    }

    void declare(Decl* d) {
    // assert(count(d) == 0);
    // emplace(d->getName(), d);
    }
};

// The scope stack
struct scopeStack : std::vector<Scope> {
    Decl* lookup(Symbol symbol) {
        for (auto iter = rbegin(); iter != rend(); ++iter) {
            if (Decl * d = iter->lookup(symbol))
                return d;
        }
        return nullptr;
    }
};
