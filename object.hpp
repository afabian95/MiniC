/* object.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "value.hpp"

#include <utility>

class Type;

class Object {
public:
    Object(Type* t);
    Object(Type* t, Value const& val);
    Object(Type* t, Value&& val);

private:
  Type* myType;
  Value myValue;

public:
  Type* getType() const { return myType; }
  bool isInit() const { return !myValue.isIndeterm(); }
  bool isUninit() const { return myValue.isIndeterm(); }
  Value const& load() const { return myValue; }
  void init(Value const& val);
  void init(Value&& val);
  void store(Value const& val);
  void store(Value&& val);
};
inline Object::Object(Type* t) :
    myType(t), myValue() {}
inline Object::Object(Type* t, Value const& val) :
    myType(t), myValue(val) {}
inline Object::Object(Type* t, Value&& val) :
    myType(t), myValue(std::move(val)) {}
inline void Object::init(Value const& val) {
  assert(isUninit());
  myValue = val;
}
inline void Object::init(Value&& val) {
  assert(isUninit());
  myValue = std::move(val);
}
inline void Object::store(Value const& val) {
  assert(isInit());
  myValue = val;
}
inline void Object::store(Value&& val) {
  assert(isInit());
  myValue = std::move(val);
}
