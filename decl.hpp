/* decl.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

class Type;
class Expr;
class Stmt;
class Printer;

// Name class for declarations
class Name {
private:
    char const* myName;
public:
    Name(const char* name);
    char const* getString() const { return myName; }
};
inline Name::Name(const char* name) :
    myName(name) {}

// The general declaration class
class Decl {
public:
    // Kinds of declarations
    enum Kind {
        myObject,
        myReference,
        myFunction
    };

protected:
    Decl(Kind k);

private:
    Kind myKind;

public:
    // Queries
    Kind getDeclaration() const { return myKind; }
    bool isObject() const { return myKind == myObject; }
    bool isReference() const { return myKind == myReference; }
    bool isFunction() const { return myKind == myFunction; }
    virtual Name* getName() const { return nullptr; }
    virtual Type* getType() const { return nullptr; }
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
private:
    Decl* const* firstOp;
    Decl* const* lastOp;
public:
    Decl* const* getFirst() const { return firstOp; }
    Decl* const* getLast() const { return lastOp; }
};
inline knaryDecl::knaryDecl(Kind k, std::initializer_list<Decl*> ops) :
    Decl(k), firstOp(ops.begin()), lastOp(ops.end()) {}

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
class varDecl : public valDecl {
protected:
    varDecl(Name* n, Type* t, Expr* e);
private:
    Expr* myInitializer;
public:
    Expr* getInitializer() const { return myInitializer; }
};
inline varDecl::varDecl(Name* n, Type* t, Expr* e) :
    valDecl(n, t), myInitializer(e) {}

// Declarations

// Object declaration
class objDecl : public nullaryDecl, public varDecl {
public:
    objDecl(Name* n, Type* t, Expr* e);
    Name* getName() const override { return varDecl::getName(); }
    Type* getType() const override { return varDecl::getType(); }
};
inline objDecl::objDecl(Name* n, Type* t, Expr* e) :
    nullaryDecl(myObject), varDecl(n, t, e) {}

// Reference declaration
class refDecl : public nullaryDecl, public varDecl {
public:
    refDecl(Name* n, Type* t, Expr* e);
    Name* getName() const override { return varDecl::getName(); }
    Type* getType() const override { return varDecl::getType(); }
};
inline refDecl::refDecl(Name* n, Type* t, Expr* e) :
    nullaryDecl(myObject), varDecl(n, t, e) {}

// Function declaration
class funcDecl : public knaryDecl, public valDecl {
private:
    Stmt* myBody;
public:
    funcDecl(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s);
    Name* getName() const override { return valDecl::getName(); }
    Type* getType() const override { return valDecl::getType(); }
    Stmt* getBody() const { return myBody; }
};
inline funcDecl::funcDecl(Name* n, Type* t, std::initializer_list<Decl*> ops, Stmt* s) :
    knaryDecl(myFunction, ops), valDecl(n, t), myBody(s) {}

// Operations
void Print(Printer& p, Decl const* d);

std::ostream& operator<<(std::ostream& os, Decl const* d);
