/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: Assembler.h - Assembler class.  This is a container for all the components that make up the assembler.
*/


#pragma once 

#include "SymTab.h"
#include "Instruction.h"
#include "FileAccess.h"
#include "Emulator.h"


class Assembler {

public:
    //Constructor 
    Assembler( int argc, char *argv[] );


    // Pass I - establish the locations of the symbols
    void PassI();


    // Pass II - generate a translation
    void PassII();


    // Display the symbols in the symbol table.
    void DisplaySymbolTable() { m_symtab.DisplaySymbolTable(); }
    

    // Run emulator on the translation.
    void RunProgramInEmulator();


private:

    FileAccess m_facc;	    // File Access object
    SymbolTable m_symtab;   // Symbol table object
    Instruction m_inst;	    // Instruction object
    Emulator m_emul;        // Emulator object



    // Print Assembler Language Translation - prints the translation from the inputed data to the pass II table format
    string PrintAssemblerTranslation(const int a_location,
        const string& a_opcode,
        const string& a_operand1,
        const string& a_instruction);


    // Print Machine Language Translation - prints the translation from the inputed data to the pass II table format
    string PrintMachineTranslation(const int a_location,
        const int a_operand1location,
        const int a_operand2location,
        const int a_opcodevalue,
        const string& a_opcode,
        const string& a_instruction);

};

