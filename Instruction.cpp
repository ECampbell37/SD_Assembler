/*
	Name: Elijah Campbell-Ihim
	Course: Software Design (CMPS 361)
	Professor: Victor Miller
	Project: Assembler for imaginary VC1620 Computer
	File: Instruction.cpp - Implementation of the Instruction class
*/

#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"
using namespace std;


/*
NAME

	ParseInstruction - parses the current instruction.

SYNOPSIS

	Instruction::InstructionType Instruction::ParseInstruction(string a_line);
		a_line -> the instruction to be parsed.

DESCRIPTION

	This function will analyze the components of the instruction, and then determine its respective instruction type.

RETURNS

	The type of instruction that was detected.
*/
Instruction::InstructionType Instruction::ParseInstruction(string a_line)
{
	//Return origial instruction
	m_instruction = a_line;
	//Remove comments
	a_line = RemoveComment(a_line);
	//if it cannot properly parse the line, we give an error
    if (!ParseLine(a_line, m_Label, m_OpCode, m_Operand1, m_Operand2, m_OperandValue))
    {
		Errors::RecordError("Extra Operand");
    }
	
	//Check what type of instruction it is and return that value
	if (IsMachineLanguage())
	{
		return m_type;
	}
	else if (IsAssemblyLanguage())
	{
		return m_type;
	}
	else
	{
		//If it is not machine or assembly language, it must be treated as a comment
		return InstructionType::ST_Comment;
	}
}
//Instruction::InstructionType Instruction::ParseInstruction(string a_line);




/*
NAME

	RemoveComment - parses out comments and blank lines.

SYNOPSIS

	string Instruction::RemoveComment(string line);
		a_line -> The line to be parsed.

DESCRIPTION

	This function will parse out comments and blank lines from the current instruction,
	and return the instruction without the comments or blank lines.

RETURNS

	The current instruction without any comments or blank lines.
*/
string Instruction::RemoveComment(string a_line) {
	size_t pos = a_line.find(';');
	if (pos == string::npos)
	{
		return a_line;
	}
	return a_line.erase(pos);
}
//string Instruction::RemoveComment(string line);





/*
NAME

	ParseLine - parses the current line.

SYNOPSIS

	bool Instruction::ParseLine(const string& a_line, string& a_label, string& a_opcode, string& a_operand1, 
																			string& operand2, int& opValue);
		a_line		-> The line to be parsed.
		a_label		-> The label of the current line.
		a_opcode	-> The opcode of the current line.
		a_operand1	-> The first operand of the current line.
		a_operand2	-> The second operand of the current line.
		a_opValue	-> The numeric value of operand 1 (if applicable in the case of an 
														Assembly Language instruction)

DESCRIPTION

	This function will parse the current line,
	and separate its components into the label, opcode, operand1 and operand 2.
	It will then set opValue to the appropriate value if applicable

RETURNS

	True if the line was parsed successfully, false otherwise (there was additional text detected).
*/
bool Instruction::ParseLine(string line, string& label, string& opcode, string& operand1, string& operand2, int& opValue)
{
    replace(line.begin(), line.end(), ',', ' ');
    istringstream ins(line);
    label = opcode = operand1 = operand2 = "";
	//If its an empty line, exit the function
    if (line.empty()) return true;


    string extra;

    if (line[0] != ' ' && line[0] != '\t')
    {
		//if there is a label, record it in label
        ins >> label;
    }
	//record op code, op1, and op2
    ins >> opcode >> operand1 >> operand2 >> extra;

	//If operand1 is a numeric value, we are dealing with assembler language, and we need to 
	//record the value in opValue
	if (operand1[0] == '1' || operand1[0] == '2' || operand1[0] == '3' || operand1[0] == '4' || operand1[0] == '5' || 
		operand1[0] == '6' || operand1[0] == '7' || operand1[0] == '8' || operand1[0] == '9' || operand1[0] == '0' )
	{
		opValue = stoi(operand1);
	}
	//If there is no extra information, we are good to return true
    return extra == "";
}
//bool Instruction::ParseLine(string line, string& label, string& opcode, string& operand1, string& operand2, int& opValue);



/*
NAME

	IsMachineLanguage - checks if the current instruction is a machine language instruction.

SYNOPSIS

	bool Instruction::IsMachineLanguage();

DESCRIPTION

	This function will check if the current instruction is a machine language instruction,
	and return true if it is, false otherwise. It also sets the opCode to the correct 
	numeric value, and the instruction type to the correct label

RETURNS

	True if the current instruction is a machine language instruction, false otherwise.
*/
bool Instruction::IsMachineLanguage() {
	string temp_buffer = GetOpCode();

	// Convert the temporary buffer to uppercase letters to make it easier to check.
	transform(temp_buffer.begin(), temp_buffer.end(), temp_buffer.begin(), ::toupper);

	// Check if the instruction is a machine language instruction.
	auto it = m_MachineLanguage.find(temp_buffer);
	if (it != m_MachineLanguage.end()) {
		switch (it->second) {
		case MachineLanguage::ADD:
			// Numeric code for ADD is 1
			m_NumOpCode = 1;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::SUB:
			// Numeric code for SUB is 2
			m_NumOpCode = 2;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::MULT:
			// Numeric code for MULT is 3
			m_NumOpCode = 3;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::DIV:
			// Numeric code for DIV is 4
			m_NumOpCode = 4;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::COPY:
			// Numeric code for LOAD is 5
			m_NumOpCode = 5;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::READ:
			// Numeric code for READ is 7
			m_NumOpCode = 7;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::WRITE:
			// Numeric code for WRITE is 8
			m_NumOpCode = 8;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::B:
			// Numeric code for BRANCH is 9
			m_NumOpCode = 9;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::BM:
			// Numeric code for BRANCH MINUS is 10
			m_NumOpCode = 10;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::BZ:
			// Numeric code for BRANCH ZERO is 11
			m_NumOpCode = 11;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::BP:
			// Numeric code for BRANCH POSITIVE is 12
			m_NumOpCode = 12;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		case MachineLanguage::HALT:
			// Numeric code for HALT is 13
			m_NumOpCode = 13;
			m_type = InstructionType::ST_MachineLanguage;
			return true;
			break;
		default:
			break;
		}
	}

	// If the instruction is not a machine language instruction, return false.
	return false;
}
//bool Instruction::IsMachineLanguage();



/*
NAME

	IsAssemblyLanguage - checks if the current instruction is an assembly language instruction.

SYNOPSIS

	bool Instruction::IsAssemblyLanguage();

DESCRIPTION

	This function will check if the current instruction is an assembly language instruction,
	and return true if it is, false otherwise. It also sets the instruction type to the correct label

RETURNS

	True if the current instruction is an assembly language instruction, false otherwise.
*/
bool Instruction::IsAssemblyLanguage() {
	string temp_buffer = GetOpCode();

	// Convert the temporary buffer to uppercase letters to make it easier to check.
	transform(temp_buffer.begin(), temp_buffer.end(), temp_buffer.begin(), ::toupper);

	// Check if the instruction is an assembly language instruction.
	auto it = m_AssemblerLanguage.find(temp_buffer);
	if (it != m_AssemblerLanguage.end()) {
		switch (it->second) {
		case AssemblerLanguage::END:
			m_type = InstructionType::ST_End;
			return true;
			break;
		default:
			m_type = InstructionType::ST_AssemblerInstr;
			return true;
			break;
		}
	}

	// If the instruction is not an assembly language instruction, return false.
	return false;
}
//bool Instruction::IsAssemblyLanguage();



/*
NAME

	LocationNextInstruction - calculates the location of the next instruction.

SYNOPSIS

	int Instruction::LocationNextInstruction(int a_loc);
		a_loc -> The location of the current instruction.

DESCRIPTION

	This function will calculate the location of the next instruction,
	depending on whether or not the current opcode is "ORG", "DS", or "END".

RETURNS

	The location of the next instruction.
*/
int Instruction::LocationNextInstruction(int a_loc) {
	string temp_instruction = GetOpCode();
	// Convert the temporary string to uppercase to make it easier to compare.
	transform(temp_instruction.begin(), temp_instruction.end(), temp_instruction.begin(), ::toupper);

	if (temp_instruction == "ORG") {
		// ORG specifies the address of the next instruction
		return m_OperandValue;
	}
	else if (temp_instruction == "DS") {
		// DS specifies the number of words of storage to be set aside
		return a_loc + m_OperandValue;
	}
	else if (temp_instruction == "")
	{
		//an empty line is likely a comment or blank line
		return a_loc;
	}
	else if (temp_instruction == "END")
	{
		//End signifies the end of instructions, so we do not have a next instruction
		return 0;
	}
	// If the opcode is none of these, then increase the current address by 1.
	else {
		return a_loc + 1;
	}
}
//int Instruction::LocationNextInstruction(int a_loc);
