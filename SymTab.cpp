/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: SymTab.cpp - Implementation of the SymbolTable class
*/


#include "stdafx.h"
#include "SymTab.h"
#include "Errors.h"


/*
NAME

    AddSymbol - adds a new symbol to the symbol table.

SYNOPSIS

    void AddSymbol( const string &a_symbol, int a_loc );
    	a_symbol	-> The name of the symbol to be added to the symbol table.
    	a_loc		-> the location to be associated with the symbol.

DESCRIPTION

    This function will place the symbol "a_symbol" and its location "a_loc"
    in the symbol table.
*/
void SymbolTable::AddSymbol( const string &a_symbol, int a_loc )
{
    // If the symbol is already in the symbol table, record it as multiply defined.
    map<string, int>::iterator st = m_symbolTable.find( a_symbol );
    if( st != m_symbolTable.end() ) {

        st->second = multiplyDefinedSymbol;
        return;
    }
    // Record a the  location in the symbol table.
    m_symbolTable[a_symbol] = a_loc;
}
//void SymbolTable::AddSymbol( const string &a_symbol, int a_loc );



/*
NAME

    DisplaySymbolTable - displays the contents of the symbol table

SYNOPSIS

    void DisplaySymbolTable();
        

DESCRIPTION

    This function will use an iterator to go through the m_symbolTable map.
    It will display the Symbol Number, Symbol Name, and Symbol Location
*/
void SymbolTable::DisplaySymbolTable()
{
    map<string, int>::iterator it;
    int symbol_index = 0;
    cout << "Symbol Table:" << endl;
    cout << "Symbol #\tSymbol Name\tLocation" << endl;
    /*
    Iterate through the map, displaying the symbol and location,
    as well as the respective index of the symbol.
    */
    for (it = m_symbolTable.begin(); it != m_symbolTable.end(); it++) {
        cout << symbol_index << "\t\t" << it->first << "\t\t" << it->second << endl;
        symbol_index++;
    }
}
//void SymbolTable::DisplaySymbolTable()



/*
NAME

    LookupSymbol - displays the contents of the symbol table

SYNOPSIS

    bool LookupSymbol(const string& a_symbol, int& a_loc);
        a_symbol	-> The name of the symbol to be searched for in the symbol table.
    	a_loc		-> the location to be associated with the symbol.


DESCRIPTION

    This function will use an iterator to go through the m_symbolTable map.
    It will look up a symbol in the symbol table


RETURNS

    returns true if symbol is found, false if not found
*/
bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc) {
    //Makes an iterator for looking through symbol table map
    auto it = m_symbolTable.find(a_symbol);
    //If value was found, sets a_loc to the value, and returns true
    if (it != m_symbolTable.end()) {
        a_loc = it->second;
        return true;
    }
    //If value not found, sets a_loc to default value and return false
    else {
        a_loc = undefinedSymbol;
        return false;
    }
}
//bool SymbolTable::LookupSymbol(const string& a_symbol, int& a_loc);



/*
NAME

    FindLabelLocation - find the location of a label in the symbol table.

SYNOPSIS

    int FindLabelLocation(const string& a_symbol);
        a_symbol	-> The name of the symbol to look for.

DESCRIPTION

    This function will look for a symbol in the symbol table. If the symbol
    is found, the location of the symbol will be returned. If the symbol is
    not found, the undefined value will be returned.

RETURNS

    The location of the symbol, if found. Otherwise,
    the undefined value.
*/
int SymbolTable::FindLabelLocation(const string& a_symbol) {
    // use find method to search for the symbol
    auto it = m_symbolTable.find(a_symbol);
    // if the symbol is found, return the location of the symbol
    if (it != m_symbolTable.end()) {
        if (it->second == multiplyDefinedSymbol && !a_symbol.empty() && a_symbol.find_first_not_of("0123456789") != string::npos) {
            Errors::RecordError("Error: Symbol " + a_symbol + " is multiply defined.");
            return multiplyDefinedSymbol;
        }
        else {
            return it->second;
        }
    }
    // if the symbol is not found, return undefined
    else {
        if (!a_symbol.empty() && a_symbol.find_first_not_of("0123456789") != string::npos) {
            Errors::RecordError("Error: Symbol " + a_symbol + " is undefined.");
        }
        return undefinedSymbol;
    }
}
//int SymbolTable::FindLabelLocation(const string& a_symbol);