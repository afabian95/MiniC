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
private:
    T** myFirst;
    T** myLast;

public:
    using iterator = T**;
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
private:
    T** myFirst;
    T** myLast;

public:
    using iterator = T* const*;
    NodeRange(T** const* first, T** const* last) : myFirst(first), myLast(last) { }
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

// Nodes
/*
template<typename T, int N>
class Node
{
private:
  std::array<T*, N> myOps;

public:
    Node();
    Node(T* e);
    Node(T* e1, T* e2);
    Node(T* e1, T* e2, T* e3);

    // Accessors
    static constexpr int getArity() { return N; }
    T* getChild(int n) const;
    T* getChild() const;
    T** begin() { return myOps.data(); }
    T** end() { return myOps.data() + myOps.size(); }
    T* const* begin() const { return myOps.data(); }
    T* const* end() const { return myOps.data() + myOps.size(); }
    NodeRange<T> getChildren() { return {begin(), end()}; }
    NodeRange<T const> getChildren() const { return {begin(), end()}; }
};


template<typename T, int N>
inline Node<T, N>::Node() : myOps() {
    assert(N == 0);
}

template<typename T, int N>
inline Node<T, N>::Node(T* e) : myOps {e} {
    assert(N == 1);
}

template<typename T, int N>
inline Node<T, N>::Node(T* e1, T* e2) : myOps {e1, e2} {
    assert(N == 2);
}

template<typename T, int N>
inline Node<T, N>::Node(T* e1, T* e2, T* e3) : myOps {e1, e2, e3} {
    assert(N == 3);
}

template<typename T, int N>
inline T* Node<T, N>::getChild(int n) const {
  assert(0 <= n && n < N);
  return myOps[n];
}

template<typename T, int N>
inline T* Node<T, N>::getChild() const {
  static_assert(N == 1);
  return myOps[0];
}
*/
