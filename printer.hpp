/* printer.hpp
 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#include <iosfwd>

// Printer class not described in instructions
// Implementing code from online example

// Printer class for output stream
class Printer {
public:
    Printer(std::ostream& os);

private:
    std::ostream& myOstream;
    int myIndent;

public:
    //Queries
    std::ostream& getStream() { return myOstream; }
    void indent() { ++myIndent; }
    void undent() { --myIndent; }
    void printIndentation();
    void printNewLine();
    void printString(char const* str);
    void printAddress(void const* ptr);
};
inline Printer::Printer(std::ostream& os) :
    myOstream(os), myIndent() {}

// Print class for indented text
class PrintIndented {
public:
    PrintIndented(Printer& p);
    ~PrintIndented();

private:
    Printer& myPrinter;
};
inline PrintIndented::PrintIndented(Printer& p) :
    myPrinter(p) { myPrinter.indent(); }
inline PrintIndented::~PrintIndented() { myPrinter.undent(); }
