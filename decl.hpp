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
        myVarDecl,      // variable declaration
        myFuncDecl,     // function declaration
        myProgDecl,     // program declaration
    };

protected:
    Decl(Kind k);

private:
    Kind myKind;

public:
    // Queries
    // Returns the kind of the declaration
    Kind getDeclKind() const { return myKind; }
    // Returns the name of the declaration
    char const* getDeclName() const;
    // Returns whether the declaration is a variable
    bool isVariable() const { return myKind == myVarDecl; }
    // Returns whether the declaration is an object
    bool isObject() const;
    // Returns whether the declaration is a reference
    bool isReference() const;
    // Returns whether the declaration is a function
    bool isFunction() const { return myKind == myFuncDecl; }
    // Returns the name of the declaration, if any
    virtual Name* getName() const { return nullptr; }
    // Returns the type of the declaration, if any
    virtual Type* getType() const { return nullptr; }

    // Returns this cast as a value declaration or null
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
    // Initialized with no arguments
    karyDecl(Kind k);
    // Initialized with a list of arguments
    karyDecl(Kind k, std::initializer_list<Decl*> list);
    karyDecl(Kind k, std::vector<Decl*> const& vec);
    karyDecl(Kind k, std::vector<Decl*>&& vec);

private:
    std::vector<Decl*> myOps;

public:
    // Adds an additional argument
    void addChild(Decl* child) { myOps.push_back(child); }
    // Returns the first argument
    Decl** begin() { return myOps.data(); }
    Decl* const* begin() const { return myOps.data(); }
    // Returns the last argument
    Decl** end() { return myOps.data() + myOps.size(); }
    Decl* const* end() const { return myOps.data() + myOps.size(); }
    // Returns a range of arguments
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
    // Returns the name of the declaration, if any
    Name* getName() const override { return valDecl::getName(); }
    // Returns the type of the declaration, if any
    Type* getType() const override { return valDecl::getType(); }
    // Returns the name of the declaration
    funcType* getFuncType() const;

    // Parameters
    // Returns the number of parameters
    std::size_t getParamCount() const;
    // Returns the parameters of the function
    NodeRange<Decl> getParams();
    NodeRange<Decl const> getParams() const;
    // Sets the parameters of the function
    void setParams(std::vector<Decl*> const& params);
    void setParams(std::initializer_list<Decl*> params);
    // Adds an additional parameter
    void addParam(Decl* d);

    // Return value
    // Returns the return object of the function
    Decl* getReturn();
    Decl const* getReturn() const;
    // Sets the return object of the function
    void setReturn(Decl* d);

    // Body
    // Sets the body of the function
    Stmt* getBody() const { return myBody; }
    // Sets the body of the function
    void setBody(Stmt* s) { myBody = s; }
};
inline funcDecl::funcDecl(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s) :
    karyDecl(myFuncDecl, ops), valDecl(n, t), myBody(s) {}

// Program declaration
class progDecl : public karyDecl {
public:
    // Constructs the program declaration from a list of arguments
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
