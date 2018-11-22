/* store.cpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include "store.hpp"
#include "type.hpp"
#include "decl.hpp"

#include <algorithm>
#include <iostream>

Object* MonotonicStore::allocate(Decl* d) {
    assert(myLookup.count(d) == 0);
    assert(d->isObject());
    myStorage.emplace_back(d->getType());
    myLookup.emplace(d, myStorage.size() - 1);
    return &myStorage.back();
}

Object* MonotonicStore::locate(Decl* d) {
    assert(myLookup.count(d) != 0);
    return &myStorage[myLookup.find(d)->second];
}

// Checks if a store contains an object
static bool containsObject(std::vector<Object> const& store, Object* obj) {
    auto i = std::find_if(store.begin(), store.end(), [obj](Object const& x) {
        return &x == obj;
    });
    return i != store.end();
}

void MonotonicStore::alias(Decl* d, Object* obj) {
    assert(myLookup.count(d) == 0);
    assert(containsObject(myStorage, obj));
    myLookup.emplace(d, obj - myStorage.data());
}
