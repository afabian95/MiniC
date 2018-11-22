/* tree.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include <array>
#include <cassert>
#include <vector>

// Node ranges

// Traversable range of nodes
template<typename T>
class NodeRange {
public:
    using iterator = T**;

private:
    // Iterator to the first element in the range
    T** myFirst;
    // Iterator to the last element in the range
    T** myLast;

public:
    // Constructs an empty range
    NodeRange() : myFirst(), myLast() { }
    // Constructs the range
    NodeRange(T** first, T** last) : myFirst(first), myLast(last) { }
    // Returns whether the range is empty
    bool isEmpty() const { return myFirst == myLast; }
    // Returns the number of elements in the range
    std::size_t getSize() const { return myLast - myFirst; }
    // Returns the first element in the range
    T* getFront() const { return *myFirst; }
    // Returns the last element in the range
    T* getBack() const { return *(myLast - 1); }
    // Returns the position of an element in the range
    T* getPosition(std::size_t n) const { return *(myFirst + n); }
    // Returns the first n elements in the range
    NodeRange getFront(std::size_t n) const { return {myFirst, myFirst + n}; }
    // Returns the last n elements in the range
    NodeRange getBack(std::size_t n) const { return {myLast - n, myLast}; }
    // Returns an iterator to the first element in the range
    T** begin() { return myFirst; }
    // Returns an iterator to the last element in the range
    T** end() { return myLast; }
    // Returns all but the first element in the range
    NodeRange getTail() const { return {myFirst + 1, myLast}; }
    // Returns all but the last element in the range
    NodeRange getRevTail() const { return {myFirst, myLast - 1}; }
};

// Const version of NodeRange
template<typename T>
class NodeRange<T const> {
public:
    using iterator = T* const*;

private:
    T* const* myFirst;
    T* const* myLast;

public:
    NodeRange(T* const* first, T* const* last) : myFirst(first), myLast(last) { }
    bool isEmpty() const { return myFirst == myLast; }
    std::size_t getSize() const { return myLast - myFirst; }
    T const* getFront() const { return *myFirst; }
    T const* getBack() const { return *(myLast - 1); }
    T const* getPosition(std::size_t n) const { return *(myFirst + n); }
    NodeRange getFront(std::size_t n) const { return {myFirst, myFirst + n}; }
    NodeRange getBack(std::size_t n) const { return {myLast - n, myLast}; }
    T* const* begin() { return myFirst; }
    T* const* end() { return myLast; }
    NodeRange getTail() const { return {myFirst + 1, myLast}; }
    NodeRange getRevTail() const { return {myFirst, myLast - 1}; }
};

// Range operations

template<typename T>
inline NodeRange<T> getTail(std::vector<T*>& v) {
    assert(v.size() > 1);
    return NodeRange<T>(v.data() + 1, v.data() + v.size());
}

template<typename T>
inline NodeRange<T> getRevTail(std::vector<T*>& v) {
    assert(v.size() > 1);
    return NodeRange<T>(v.data(), v.data() - 1);
}
