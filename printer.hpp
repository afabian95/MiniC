/* printer.hpp

 * Fabian Ardeljan
 * Compiler Design, Fall 2018, The University of Akron
 * Based on code examples by Dr. A. Sutton */

#pragma once

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
    // Queries
    // Returns the output stream
    std::ostream& getStream() { return myOstream; }
    // Increases indentation
    void indent() { ++myIndent; }
    // Decreases indentation
    void undent() { --myIndent; }

    // Printing
    // Prints the indentation
    void printIndentation();
    // Prints a newline character
    void printNewline();
    // Prints the string
    void printString(char const* str);
    // Prints the address
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

// Print class for last newline
class PrintFinalNewline {
public:
    PrintFinalNewline(Printer& p);
    ~PrintFinalNewline();

private:
    Printer& myPrinter;
};
inline PrintFinalNewline::PrintFinalNewline(Printer& p) :
    myPrinter(p) {}
inline PrintFinalNewline::~PrintFinalNewline() {
  myPrinter.printNewline();
}

