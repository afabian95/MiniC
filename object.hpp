/* object.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "value.hpp"

#include <utility>

class Type;

// The general object class
class Object {
public:
    // Constructs the object with an indeterminate value
    Object(Type* t);
    // Constructs the object
    Object(Type* t, Value const& val);
    Object(Type* t, Value&& val);

private:
    Type* myType;
    Value myValue;

public:
    // Returns the type of object
    Type* getObjectType() const { return myType; }
    // Returns whether the object is initialized
    bool isInit() const { return !myValue.isIndeterm(); }
    // Returns whether the object is uninitialized
    bool isUninit() const { return myValue.isIndeterm(); }
    // Returns the value of the object
    Value const& load() const { return myValue; }
    // Initializes the object
    void init(Value const& val);
    void init(Value&& val);
    // Sets the value of the initialized object
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
