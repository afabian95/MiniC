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
    T** myFirst;
    T** myLast;

public:
    NodeRange() : myFirst(), myLast() { }
    NodeRange(T** first, T** last) : myFirst(first), myLast(last) { }
    bool isEmpty() const { return myFirst == myLast; }
    std::size_t getSize() const { return myLast - myFirst; }
    T* getFront() const { return *myFirst; }
    T* getBack() const { return *(myLast - 1); }
    T* getPosition(std::size_t n) const { return *(myFirst + n); }
    NodeRange getFront(std::size_t n) const { return {myFirst, myFirst + n}; }
    NodeRange getBack(std::size_t n) const { return {myLast - n, myLast}; }
    T** begin() { return myFirst; }
    T** end() { return myLast; }
    NodeRange getTail() const { return {myFirst + 1, myLast}; }
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

// Returns all but front
template<typename T>
inline NodeRange<T> getTail(std::vector<T*>& v) {
    assert(v.size() > 1);
    return NodeRange<T>(v.data() + 1, v.data() + v.size());
}

// Returns all but back
template<typename T>
inline NodeRange<T> getRevTail(std::vector<T*>& v) {
    assert(v.size() > 1);
    return NodeRange<T>(v.data(), v.data() - 1);
}
