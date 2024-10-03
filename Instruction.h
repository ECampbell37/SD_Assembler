/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: Instruction.h - Class to parse and provide information about instructions.
*/


#pragma once

// The elements of an instruction.
class Instruction {

public:

    // Enum class to hold VC1620 Instruction Types
    enum class InstructionType {
        ST_MachineLanguage, 	// A machine language instruction.
        ST_AssemblerInstr,      // Assembler Language instruction.
        ST_Comment,             // Comment or blank line
        ST_End,                  // end instruction.
    };



    // Enum class to hold machine language instructions (comments: Name, opcode, function)
    enum class MachineLanguage {
        //Addr == literal address    (Addr) == content stored at Addr

        ADD,    //ADD               01     (Addr1) + (Addr2) --> Addr1
        SUB,    //SUBTRACT          02     (Addr1) - (Addr2) --> Addr1
        MULT,   //MULTIPLY          03     (Addr1) * (Addr2) --> Addr1
        DIV,    //DIVIDE            04     (Addr1) / (Addr2) --> Addr1
        COPY,   //COPY              05     (Addr2) --> Addr1
        READ,   //READ              06     reads line and puts content in Addr1
        WRITE,  //WRITE             07     writes (Addr1)
        B,      //BRANCH            08     go to Addr1 for next instruction
        BM,     //BRANCH MINUS      09     go to Addr1 if (Addr2) < 0
        BZ,     //BRANCH ZERO       10     go to Addr1 if (Addr2) = 0
        BP,     //BRANCH POSITIVE   11     go to Addr1 if (Addr2) > 0
        HALT    //HALT              12     terminate execution
    };


    // Enum class to hold assembler language instructions
    enum class AssemblerLanguage
    {
        DC,     //Define constant.  The constant is a decimal integer placed in the operand field.
        DS,     //Define storage.   The operand specifies the number of words of storage to be set aside.
        ORG,    //Define origin.    The operand specifies the address at which the translation of the next instruction will be generated,
        END     //Indicates that there are no additional statements to translate.
    };





    // Parse the Instruction.
    InstructionType ParseInstruction(string a_line);




    // Compute the location of the next instruction.
    int LocationNextInstruction(int a_loc);



    // To access the label
    inline string& GetLabel() {

        return m_Label;
    };


    // To determine if a label is blank.
    inline bool isLabel() {

        return !m_Label.empty();
    };


    // To access the instruction
    inline string& GetInstruction() {
        return m_instruction;
    }


    // To access the opcode.
    inline string& GetOpCode() {
        return m_OpCode;
    }


    //To access numeric value for op code
    inline int GetOpCodeValue() {
        return m_NumOpCode;
    }


    // To access the operand 1.
    inline string& GetOperand1() {
        return m_Operand1;
    }

    // To access the operand 2.
    inline string& GetOperand2() {
        return m_Operand2;
    }


private:


    // The elemements of a instruction
    string m_Label;        // The label.
    string m_OpCode;       // The symbolic op code.
    string m_Operand1;      // The operands. 
    string m_Operand2;

    string m_instruction;    // The original instruction.

    // Derived values.
    int m_NumOpCode;     // The numerical value of the op code for machine language equivalents.
    InstructionType m_type; // The type of instruction.


    int m_OperandValue;    // The value of the operand if it is numeric.





    // link strings to the proper machine language instruction
    const unordered_map<string, MachineLanguage> m_MachineLanguage = {
        {"ADD", MachineLanguage::ADD},
        {"SUB", MachineLanguage::SUB},
        {"MULT", MachineLanguage::MULT},
        {"DIV", MachineLanguage::DIV},
        {"COPY", MachineLanguage::COPY},
        {"READ", MachineLanguage::READ},
        {"WRITE", MachineLanguage::WRITE},
        {"B", MachineLanguage::B},
        {"BM", MachineLanguage::BM},
        {"BZ", MachineLanguage::BZ},
        {"BP", MachineLanguage::BP},
        {"HALT", MachineLanguage::HALT}
    };


    // link strings to the proper assembler language instruction
    const unordered_map<string, AssemblerLanguage> m_AssemblerLanguage = {
        {"DC", AssemblerLanguage::DC},
        {"DS", AssemblerLanguage::DS},
        {"ORG", AssemblerLanguage::ORG},
        {"END", AssemblerLanguage::END}
    };



    // Determine if the instruction is machine or assembly language.
    bool IsMachineLanguage();
    bool IsAssemblyLanguage();



    //Parses the information in the line to match VC1620 format
    bool ParseLine(string line, string& label, string& opcode, string& operand1, string& operand2, int& opVal);



    //Function to removes text after ';' to signify comment
    string RemoveComment(string a_line);



};