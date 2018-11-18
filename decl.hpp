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
class karyDecl : public Decl {
protected:
    karyDecl(Kind k);
    karyDecl(Kind k, std::initializer_list<Decl*> list);
    karyDecl(Kind k, std::vector<Decl*> const& vec);
    karyDecl(Kind k, std::vector<Decl*>&& vec);

private:
    std::vector<Decl*> myOps;

public:
    void addChild(Decl* child) { myOps.push_back(child); }
    Decl** begin() { return myOps.data(); }
    Decl** end() { return myOps.data() + myOps.size(); }
    Decl* const* begin() const { return myOps.data(); }
    Decl* const* end() const { return myOps.data() + myOps.size(); }
    NodeRange<Decl> getChildren() { return { begin(), end()}; }
    NodeRange<Decl const> getChildren() const { return { begin(), end()}; }
};
inline karyDecl::karyDecl(Kind k) :
    Decl(k) {}
inline karyDecl::karyDecl(Kind k, std::initializer_list<Decl*> list) :
    Decl(k), myOps(list) {}
inline karyDecl::karyDecl(Kind k, std::vector<Decl*> const& vec) :
    Decl(k), myOps(vec) {}
inline karyDecl::karyDecl(Kind k, std::vector<Decl*>&& vec) :
    Decl(k), myOps(std::move(vec)) {}

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
class funcDecl : public karyDecl, public valDecl {
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
    karyDecl(myFuncDecl, ops), valDecl(n, t), myBody(s) {}

// Program declaration
class progDecl : public karyDecl {
public:
    progDecl(std::initializer_list<Decl*> list);
    progDecl(std::vector<Decl*> const& vec);
    progDecl(std::vector<Decl*>& vec);
};
inline progDecl::progDecl(std::initializer_list<Decl*> list) :
    karyDecl(myProgDecl, list) {}
inline progDecl::progDecl(std::vector<Decl*> const& vec) :
    karyDecl(myProgDecl, vec) {}
inline progDecl::progDecl(std::vector<Decl*>& vec) :
    karyDecl(myProgDecl, vec) {}

// Operations
void printDecl(Printer& p, Decl const* d);

std::ostream& operator<<(std::ostream& os, Decl const& d);
