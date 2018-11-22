/* store.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "object.hpp"

#include <unordered_map>
#include <vector>

class Decl;

// A store in which all storage is returned simultaneously
class MonotonicStore {
public:
    // Allocates storage for an object
    Object* allocate(Decl* d);
    // Returns the object for the declaration
    Object* locate(Decl* d);
    // Create an alias for the given object
    void alias(Decl* d, Object* o);

private:
    // List of allocated objects
    std::vector<Object> myStorage;
    // Associates declarations with objects in the store
    std::unordered_map<Decl*, int> myLookup;
};

