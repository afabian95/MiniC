/* store.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "object.hpp"

#include <unordered_map>
#include <vector>

class Decl;

class MonotonicStore {
public:
  Object* allocate(Decl* d);
  Object* locate(Decl* d);
  void alias(Decl* d, Object* o);

private:
  std::vector<Object> myStorage;
  std::unordered_map<Decl*, int> myLookup;
};

