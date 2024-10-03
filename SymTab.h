/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: SymTab.h - Symbol table class
*/

#pragma once


// This class is our symbol table.
class SymbolTable {

public:

    // Constants for when dealing with multiply defined and undefined symbols
    const int multiplyDefinedSymbol = 0;
    const int undefinedSymbol = 0;


    // Add a new symbol to the symbol table.
    void AddSymbol( const string &a_symbol, int a_loc );

    // Display the symbol table.
    void DisplaySymbolTable();

    // Lookup a symbol in the symbol table.
    bool LookupSymbol(const string& a_symbol, int& a_loc);


    // Find the location for a label in the symbol table
    int FindLabelLocation(const string& a_symbol);

private:

    // This is the actual symbol table.  The symbol is the key to the map.  The value is the location.
    map<string, int> m_symbolTable;
};
