/* expr.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

class Type;
class Decl;
class Printer;

// Value class for expressions
class Value {
public:
    explicit Value(int v);
    int getInt() const;
    float getFloat() const;
private:
    int myValue;
};
inline Value::Value(int v) :
    myValue(v) {}
inline int Value::getInt() const { return myValue; }
inline float Value::getFloat() const { return myValue; }

// The general expression class
class Expr {
public:
    // Kinds of expressions
    enum Kind{
        myBoolean,
        myInteger,
        myFloat,
        myIdentifier,
        myAND,
        myOR,
        myNOT,
        myConditional,
        myEqual,
        myNotEqual,
        myLessThan,
        myGreaterThan,
        myLessThanOrEqual,
        myGreaterThanOrEqual,
        myAddition,
        mySubtraction,
        myMultiplication,
        myDivisionQuotient,
        myDivisionRemainder,
        myNegation,
        myReciprocal
    };

protected:
    Expr(Kind k, Type* t);

private:
    Kind myKind;
    Type* myType;

public:
    Kind getExpression() const { return myKind; }
};
inline Expr::Expr(Kind k, Type* t) :
    myKind(k), myType(t) {}

// For expressions with no operands
class nullaryExpr : public Expr {
protected:
   nullaryExpr(Kind k, Type* T);
};
inline nullaryExpr::nullaryExpr(Kind k, Type* t) :
    Expr(k, t) {}

// For expressions with one operand
class unaryExpr : public Expr {
protected:
    unaryExpr(Kind k, Type* t, Expr* op);
private:
    Expr* myOp;
public:
    Expr* getChild() const { return myOp; }
};
inline unaryExpr::unaryExpr(Kind k, Type* t, Expr* op) :
    Expr(k, t), myOp(op) {}

// For expressions with two operands
class binaryExpr : public Expr {
protected:
    binaryExpr(Kind k, Type* t, Expr* op1, Expr* op2);
private:
    Expr* firstOp;
    Expr* secondOp;
public:
    Expr* getFirst() const { return firstOp; }
    Expr* getSecond() const { return secondOp; }
};
inline binaryExpr::binaryExpr(Kind k, Type* t, Expr* op1, Expr* op2) :
    Expr(k, t), firstOp(op1), secondOp(op2) {}

// For expressions with three operands
class ternaryExpr : public Expr {
protected:
    ternaryExpr(Kind k, Type* t, Expr* op1, Expr* op2, Expr* op3);
private:
    Expr* firstOp;
    Expr* secondOp;
    Expr* thirdOp;
public:
    Expr* getFirst() const { return firstOp; }
    Expr* getSecond() const { return secondOp; }
    Expr* getThird() const { return thirdOp; }
};
inline ternaryExpr::ternaryExpr(Kind k, Type* t, Expr* op1, Expr* op2, Expr* op3) :
    Expr(k, t), firstOp(op1), secondOp(op2), thirdOp(op3) {}

// For expressions with k operands
class knaryExpr : public Expr {
protected:
    knaryExpr(Kind k, Type* t, std::initializer_list<Expr*> ops);
private:
    Expr* const* firstOp;
    Expr* const* lastOp;
public:
    Expr* const* getFirst() const { return firstOp; }
    Expr* const* getLast() const { return lastOp; }
};
inline knaryExpr::knaryExpr(Kind k, Type* t, std::initializer_list<Expr*> ops) :
    Expr(k, t), firstOp(ops.begin()), lastOp(ops.end()) {}

// For literal expressions
class literalExpr : public nullaryExpr {
private:
    Value myValue;
protected:
    literalExpr(Kind k, Type* t, Value const& v);
    Value const& getValue() const { return myValue; }
};
inline literalExpr::literalExpr(Kind k, Type* t, Value const& v):
    nullaryExpr(k, t), myValue(v) {}

//Expressions

// The boolean literal expression
class boolExpr : public literalExpr {
public:
    boolExpr(Type* t, Value const& v);
    bool getBoolValue() const { return getValue().getInt(); }
};
inline boolExpr::boolExpr(Type* t, Value const& v) :
    literalExpr(myBoolean, t, v) {}

// The integer literal expression
class intExpr : public literalExpr {
public:
    intExpr(Type* t, Value const& v);
    int getIntValue() const { return getValue().getInt(); }
};
inline intExpr::intExpr(Type* t, Value const& v) :
    literalExpr(myInteger, t, v) {}

// The float literal expression
class floatExpr : public literalExpr {
public:
    floatExpr(Type* t, Value const& v);
    int getFloatValue() const { return getValue().getFloat(); }
};
inline floatExpr::floatExpr(Type* t, Value const& v) :
    literalExpr(myFloat, t, v) {}

// The identifier expression
class idExpr : public nullaryExpr {
private:
    Decl* myDecl;
public:
    idExpr(Type* t, Decl* d);
    Decl* getDeclaration() const { return myDecl; }
};
inline idExpr::idExpr(Type*t, Decl* d) :
    nullaryExpr(myIdentifier, t), myDecl(d) {}

// The logical AND expression
class andExpr : public binaryExpr {
public:
    andExpr(Type* t, Expr* e1, Expr* e2);
};
inline andExpr::andExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myAND, t, e1, e2) {}

// The logical OR expression
class orExpr : public binaryExpr {
public:
    orExpr(Type* t, Expr* e1, Expr* e2);
};
inline orExpr::orExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myOR, t, e1, e2) {}

// The logical negation expression
class notExpr : public unaryExpr {
public:
    notExpr(Type* t, Expr* e);
};
inline notExpr::notExpr(Type* t, Expr* e) :
    unaryExpr(myNOT, t, e) {}

// The conditional expression
class condExpr : public ternaryExpr {
public:
    condExpr(Type* t, Expr* e1, Expr* e2, Expr* e3);
};
inline condExpr::condExpr(Type* t, Expr* e1, Expr* e2, Expr* e3) :
    ternaryExpr(myConditional, t, e1, e2, e3) {}

// The "equal to" expression
class equalExpr : public binaryExpr {
public:
    equalExpr(Type* t, Expr* e1, Expr* e2);
};
inline equalExpr::equalExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myEqual, t, e1, e2) {}

// The "not equal to" expression
class notEqualExpr : public binaryExpr {
public:
    notEqualExpr(Type* t, Expr* e1, Expr* e2);
};
inline notEqualExpr::notEqualExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myNotEqual, t, e1, e2) {}

// The "less than" expression
class lessThanExpr : public binaryExpr {
public:
    lessThanExpr(Type* t, Expr* e1, Expr* e2);
};
inline lessThanExpr::lessThanExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myLessThan, t, e1, e2) {}

// The "greater than" expression
class greaterThanExpr : public binaryExpr {
public:
    greaterThanExpr(Type* t, Expr* e1, Expr* e2);
};
inline greaterThanExpr::greaterThanExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myGreaterThan, t, e1, e2) {}

// The "less than or equal to" expression
class lessThanOrEqualExpr : public binaryExpr {
public:
    lessThanOrEqualExpr(Type* t, Expr* e1, Expr* e2);
};
inline lessThanOrEqualExpr::lessThanOrEqualExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myLessThanOrEqual, t, e1, e2) {}

// The "greater than or equal to" expression
class greaterThanOrEqualExpr : public binaryExpr {
public:
    greaterThanOrEqualExpr(Type* t, Expr* e1, Expr* e2);
};
inline greaterThanOrEqualExpr::greaterThanOrEqualExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myGreaterThanOrEqual, t, e1, e2) {}

// The addition expression
class addExpr : public binaryExpr {
public:
    addExpr(Type* t, Expr* e1, Expr* e2);
};
inline addExpr::addExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myAddition, t, e1, e2) {}

// The subtraction expression
class subExpr : public binaryExpr {
public:
    subExpr(Type* t, Expr* e1, Expr* e2);
};
inline subExpr::subExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(mySubtraction, t, e1, e2) {}

// The multiplication expression
class mulExpr : public binaryExpr {
public:
    mulExpr(Type* t, Expr* e1, Expr* e2);
};
inline mulExpr::mulExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myMultiplication, t, e1, e2) {}

// The division quotient expression
class divQuoExpr : public binaryExpr {
public:
    divQuoExpr(Type* t, Expr* e1, Expr* e2);
};
inline divQuoExpr::divQuoExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myDivisionQuotient, t, e1, e2) {}

// The division remainder expression
class divRemExpr : public binaryExpr {
public:
    divRemExpr(Type* t, Expr* e1, Expr* e2);
};
inline divRemExpr::divRemExpr(Type* t, Expr* e1, Expr* e2) :
    binaryExpr(myDivisionRemainder, t, e1, e2) {}

// The (-) negation expression
class negationExpr : public unaryExpr {
public:
    negationExpr(Type* t, Expr* e);
};
inline negationExpr::negationExpr(Type* t, Expr* e) :
    unaryExpr(myNegation, t, e) {}

// The reciprocal expression
class reciprocalExpr : public unaryExpr {
public:
    reciprocalExpr(Type* t, Expr* e);
};
inline reciprocalExpr::reciprocalExpr(Type* t, Expr* e) :
    unaryExpr(myReciprocal, t, e) {}

// Operations
void Print(Printer& p, Expr const* e);

std::ostream& operator<<(std::ostream& os, Expr const* e);
