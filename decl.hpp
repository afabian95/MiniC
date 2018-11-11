/* decl.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

#include "tree.hpp"

class Name;
class Type;
class refType;
class funcType;
class Expr;
class Stmt;
class Decl;
class valDecl;
class varDecl;
class Printer;


// The general declaration class
class Decl {
public:
    // Kinds of declarations
    enum Kind {
        myVarDecl,
        myFuncDecl,
        myProgDecl,
    };

protected:
    Decl(Kind k);

private:
    Kind myKind;

public:
    // Queries
    Kind getDeclKind() const { return myKind; }
    char const* getDeclName() const;
    bool isVariable() const { return myKind == myVarDecl; }
    bool isObject() const;
    bool isReference() const;
    bool isFunction() const { return myKind == myFuncDecl; }
    virtual Name* getName() const { return nullptr; }
    virtual Type* getType() const { return nullptr; }

    // Casting
    valDecl* getAsValue();
    valDecl const* getAsValue() const;
};
inline Decl::Decl(Kind k) :
    myKind(k) {}

// For declarations with no operands
class nullaryDecl : public Decl {
protected:
    nullaryDecl(Kind k);
};
inline nullaryDecl::nullaryDecl(Kind k) :
    Decl(k) {}

// For declarations with k operands
class knaryDecl : public Decl {
protected:
    knaryDecl(Kind k, std::initializer_list<Decl*> ops);
//    knaryDecl(Kind k, std::vector<Decl*> const& ops);
//    knaryDecl(Kind k, std::vector<Decl*>& ops);
private:
    Decl* const* firstOp;
    Decl* const* lastOp;
    std::initializer_list<Decl*> allOps;
//    std::vector<Decl*> const& constVecOps;
//    std::vector<Decl*>& vecOps;
public:
    Decl* const* getFirst() const { return firstOp; }
    Decl* const* getLast() const { return lastOp; }
    std::initializer_list<Decl*> getChildren() const { return allOps; }
//    std::vector<Decl*> const& getChildrenConstVector() const { return constVecOps; }
//    std::vector<Decl*>& getChildrenVector() const { return vecOps; }
};
inline knaryDecl::knaryDecl(Kind k, std::initializer_list<Decl*> ops) :
    Decl(k), firstOp(ops.begin()), lastOp(ops.end()), allOps(ops) {}
//inline knaryDecl::knaryDecl(Kind k, std::vector<Decl*> const& ops) :
//    Decl(k), firstOp(ops.begin()), lastOp(ops.end()), constVecOps(ops) {}
//inline knaryDecl::knaryDecl(Kind k, std::vector<Decl*>& ops) :
//    Decl(k), firstOp(ops.begin()), lastOp(ops.end()), constVecOps(ops) {}

// For declarations containing values
class valDecl {
protected:
    valDecl(Name* n, Type* t);
private:
    Name* myName;
    Type* myType;
public:
    Name* getName() const { return myName; }
    Type* getType() const { return myType; }
};
inline valDecl::valDecl(Name* n, Type* t) :
    myName(n), myType(t) {}

// For variable declarations (objects and references)
class varDecl : public nullaryDecl, public valDecl {
public:
    varDecl(Name* n, Type* t);
private:
    Expr* myInit;
public:
    Expr* getInit() const { return myInit; }
    void setInit(Expr* e);
    Name* getName() const override { return valDecl::getName(); }
    Type* getType() const override { return valDecl::getType(); }
};
inline varDecl::varDecl(Name* n, Type* t) :
    nullaryDecl(myVarDecl), valDecl(n, t), myInit() {}
inline void varDecl::setInit(Expr* e) {
    assert(!myInit);
    myInit = e;
}

// Function declaration
class funcDecl : public knaryDecl, public valDecl {
public:
    funcDecl(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s);
private:
    Stmt* myBody;
public:
    Name* getName() const override { return valDecl::getName(); }
    Type* getType() const override { return valDecl::getType(); }
    funcType* getFuncType() const;

    // Parameters
    std::size_t getParamCount() const;
    NodeRange<Decl> getParams();
    NodeRange<Decl const> getParams() const;
    void setParams(std::vector<Decl*> const& params);
    void setParams(std::initializer_list<Decl*> params);
    void addParam(Decl* d);

    // Return value
    Decl* getReturn();
    Decl const* getReturn() const;
    void setReturn(Decl* d);

    // Body
    Stmt* getBody() const { return myBody; }
    void setBody(Stmt* s);
};
inline funcDecl::funcDecl(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s) :
    knaryDecl(myFuncDecl, ops), valDecl(n, t), myBody(s) {}

// Program declaration
class progDecl : public knaryDecl {
public:
    progDecl(std::initializer_list<Decl*> list);
    progDecl(std::vector<Decl*> const& vec);
    progDecl(std::vector<Decl*>& vec);
};
inline progDecl::progDecl(std::initializer_list<Decl*> list) :
    knaryDecl(myProgDecl, list) {}
//inline progDecl::progDecl(std::vector<Decl*> const& vec) :
//    knaryDecl(myProgDecl, vec) {}
//inline progDecl::progDecl(std::vector<Decl*>& vec) :
//    Kary_decl(prog_decl, vec) {}

// Operations
void printDecl(Printer& p, Decl const* d);

std::ostream& operator<<(std::ostream& os, Decl const& d);
