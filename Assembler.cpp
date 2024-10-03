/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: Assembler.cpp - Implementation of the Assembler class.
*/


#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"


/*
NAME

    Assembler - Constructor for the Assembler class.

SYNOPSIS

    Assembler::Assembler(int argc, char *argv[]);
        argc --> The number of command line arguments.
        argv --> The array of command line arguments.

DESCRIPTION

    This function is the constructor for the Assembler class.

*/
Assembler::Assembler( int argc, char *argv[] )
: m_facc( argc, argv )
{
    // Nothing else to do here at this point.
}  
//Assembler::Assembler( int argc, char *argv[] );





/*
NAME

    PassI - establishes the locations of the labels

SYNOPSIS

    void Assembler::PassI();

DESCRIPTION

    This function will read the source code line by line and establish the locations of the labels (if the instruction has one).
    It also calculates the location of the next instruction.

*/
void Assembler::PassI( ) 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string line; 
        if( ! m_facc.GetNextLine( line ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }
        // Parse the line and get the instruction type.
        Instruction::InstructionType st = m_inst.ParseInstruction(line);

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement and report an error if it isn't.
        if( st == Instruction::InstructionType::ST_End ) return;

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip comments.
        if( st == Instruction::InstructionType::ST_Comment )
        {
        	continue;
	    }
        // If the instruction has a label, record it and its location in the
        // symbol table.
        if( m_inst.isLabel( ) ) {

            m_symtab.AddSymbol( m_inst.GetLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}
//void Assembler::PassI( );



/*
NAME

    PassII - generates the contents at each location and checks for errors

SYNOPSIS

    void Assembler::PassII();

DESCRIPTION

    This function will generate the contents at each location and check for errors.
    It will print information to the screen regarding location in memory, contents stored in 
    that location, and the original statement in the included text file.
    It will loop through this until it has reached the end of all stored information

*/
void Assembler::PassII() {
    // Rewind to the start of the file
    m_facc.rewind();
    cout << "__________________" << endl;
    cout << "Translation of Program:" << endl;
    cout << "Location\tContents\tOriginal Statement" << endl;

    int location = 0;
    for (;;) {
        // Reset the error reporting vector
        Errors::InitErrorReporting();

        // Read the next line from the source file.
        string current_line;
        
        if (!m_facc.GetNextLine(current_line)) {
            // If we get here, it means there is an end statement missing
            Errors::RecordError("Error: Missing END statement");
            Errors::DisplayErrors();
            system("pause");
            exit(1);
        }
        

        // Parse the line and get the instruction type, as well as the appropriate components.
        Instruction::InstructionType st = m_inst.ParseInstruction(current_line);
        string current_instruction = m_inst.GetInstruction(),
            label = m_inst.GetLabel(), opcode = m_inst.GetOpCode(),
            operand1 = m_inst.GetOperand1(), operand2 = m_inst.GetOperand2(), current_contents = "";
        int op_code_value = m_inst.GetOpCodeValue(), operand_location1 = m_symtab.FindLabelLocation(operand1), 
            operand_location2 = m_symtab.FindLabelLocation(operand2);



        // If there is a comment, print it out and continue to the next line
        if (st == Instruction::InstructionType::ST_Comment) {
            cout << " \t \t \t\t " << current_instruction << "\n";
            continue;
        }


        // If there is an end statement, print it out and exit the loop
        if (st == Instruction::InstructionType::ST_End) {
            // Make sure there is nothing after the end statement
            if (m_facc.GetNextLine(current_line)) {
                cout << " \t \t \t " << current_instruction << "\n";
                cout << " \t \t \t " << current_line << "\n";
                Errors::RecordError("Error: Additional statement(s) detected after END statement.");
                Errors::DisplayErrors();
                system("pause");
                exit(1);
            }
            else {
                // simply print out the instruction
                cout << " \t \t \t " << current_instruction << "\n";
                Errors::DisplayErrors();
                break;
            }
        }


        // When we are dealing with machine langauge
        if (st == Instruction::InstructionType::ST_MachineLanguage) {
            current_contents = PrintMachineTranslation(location, operand_location1, operand_location2, op_code_value, opcode, current_instruction);
            m_emul.insertMemory(location, stoll(current_contents));
        }

        // When we are dealing with assembler langauge
        if (st == Instruction::InstructionType::ST_AssemblerInstr) {
            current_contents = PrintAssemblerTranslation(location, opcode, operand1, current_instruction);
            if (!current_contents.empty()) {
                m_emul.insertMemory(location, stoll(current_contents));
            }
        }


        // Check if the current location exceeds the memory limit of the VC1620
        if (location > 100'000) {
            Errors::RecordError("Error: Memory limit exceeded");
        }

        // Display all the errors that were encountered
        Errors::DisplayErrors();

        // If we are still within the memory limit, calculate the location of the next instruction
        location = m_inst.LocationNextInstruction(location);
    }

}
//void Assembler::PassII();



/*
NAME

    PrintMachineTranslation - prints out the translation of the machine instruction

SYNOPSIS

    string Assembler::PrintMachineTranslation(const int a_location,
                                              const int a_operand1location,
                                              const int a_operand2location,
                                              const int a_opcodevalue,
                                              const string& a_opcode,
                                              const string& a_instruction);
        a_location -> the current location
        a_operand1location -> the location of the first operand
        a_operand2location -> the location of the second operand
        a_opcodevalue -> the numeric value of the opcode
        a_opcode -> the opcode
        a_instruction -> the instruction

DESCRIPTION

    This function will print out the translation of the machine instruction.
    It will also generate the contents to be stored in memory using
    a stringstream object.

RETURNS

    The contents to be stored in memory.
*/
string Assembler::PrintMachineTranslation(const int a_location,
    const int a_operand1location,
    const int a_operand2location,
    const int a_opcodevalue,
    const string& a_opcode,
    const string& a_instruction) {
    stringstream contents;
    string temp_opcode = a_opcode;
    transform(temp_opcode.begin(), temp_opcode.end(), temp_opcode.begin(), ::toupper);
    if (temp_opcode == "HALT") {
        // If the opcode is HALT, print out the location, the numeric opcode, and the original statement
        contents << setw(2) << to_string(a_opcodevalue) << setw(10) << setfill('0') << "";
        cout << a_location << "     \t" << contents.str() << " \t " << a_instruction << "\n";
    }
    else {
        contents << setfill('0') << setw(2) << to_string(a_opcodevalue) << setw(5) << to_string(a_operand1location) << setw(5) << to_string(a_operand2location);
        cout << a_location << "     \t" << contents.str() << "  \t  " << a_instruction << "\n";
    }
    return contents.str();
}
/*string Assembler::PrintMachineTranslation(const int a_location,
const int a_operand1location,
const int a_operand2location,
const int a_opcodevalue,
const string& a_opcode,
const string& a_instruction);*/



/*
NAME

    PrintAssemblerTranslation - prints out the translation of the assembler instruction

SYNOPSIS

    string Assembler::PrintAssemblerTranslation(const int a_location,
                                                const string& a_opcode,
                                                const string& a_operand1,
                                                const string& a_instruction);
            a_location -> the current location
            a_opcode -> the opcode
            a_operand1 -> the operand (Assembler language only has one operand)
            a_instruction -> the instruction

DESCRIPTION

    This function will print out the translation of the assembler instruction.
    It will also generate the contents to be stored in memory using
    a stringstream object.

RETURNS

    The contents to be stored in memory.
*/
string Assembler::PrintAssemblerTranslation(const int a_location,
    const string& a_opcode,
    const string& a_operand1,
    const string& a_instruction) 
{
    stringstream contents;
    string temp_opcode = a_opcode;
    transform(temp_opcode.begin(), temp_opcode.end(), temp_opcode.begin(), ::toupper);
    if (temp_opcode == "ORG") {
        // If the opcode is ORG, print out the location and the original statement
        cout << a_location << "    \t\t          " << a_instruction << "\n";
    }
    if (temp_opcode == "DC") {
        // If the opcode is DC, print out the location, the operand, and the original statement
        contents << setfill('0') << setw(12) << a_operand1;
        cout << a_location << "  \t        " << contents.str() << " \t    " << a_instruction << "\n";
    }
    if (temp_opcode == "DS") {
        // If the opcode is DS, print out the location and the original statement
        cout << a_location << "  \t    \t\t    \t    " << a_instruction << "\n";
    }
    return contents.str();
}
/*string Assembler::PrintAssemblerTranslation(const int a_location,
    const string& a_opcode,
    const string& a_operand1,
    const string& a_instruction);*/



/*
NAME

	RunProgramInEmulator - runs the program in an emulator

SYNOPSIS

    void Assembler::RunProgramInEmulator();

DESCRIPTION

    This function will attempt to run the program in an emulator,
	and generates appropriate output based on the results.

*/
void Assembler::RunProgramInEmulator() {
    Errors::InitErrorReporting();
    bool emulation_success = m_emul.runProgram();
    if (emulation_success) {
        // If we get here, the emulation was successful.
        Errors::DisplayErrors();
        cout << "End of emulation." << endl;
    }
    else {
        // If we get here, the emulation failed.
        Errors::RecordError("Error: Emulation failed.");
        Errors::DisplayErrors();
        system("pause");
        exit(1);
    }
}
//void Assembler::RunProgramInEmulator();
