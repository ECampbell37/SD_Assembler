/*
	Name: Elijah Campbell-Ihim
	Course: Software Design (CMPS 361)
	Professor: Victor Miller
	Project: Assembler for imaginary VC1620 Computer
	File: Emulator.cpp - Implementation of the Emulator class
*/


#include "stdafx.h"
#include "Errors.h"
#include "Emulator.h"


/*
NAME

	InsertMemory - inserts contents into memory.

SYNOPSIS

	bool Emulator::InsertMemory(int a_location, long long a_contents);
		a_location	--> The location in memory to insert the contents.
		a_contents	--> The contents to insert into memory.

DESCRIPTION

	This function will insert contents into the VC1620's memory vector at a given location.

RETURNS

	True if the contents were inserted into memory, false otherwise.
*/
bool Emulator::insertMemory(int a_location, long long a_contents) {
	// Check for valid location.
	if (a_location < 0 || a_location > MEMSZ) {
		// Location is out of range.
		Errors::RecordError("Error: Location is out of range for emulator.");
		return false;
	}

	// Check for valid contents.
	if (a_contents < 0 || a_contents > 999'999'999'999) {
		// Contents are out of range.
		Errors::RecordError("Errors: Contents are out of range for emulator.");
		return false;
	}
	
	// Everything is ok, so record the contents in memory.
	m_memory[a_location] = (a_contents);
	return true;
}
//bool Emulator::InsertMemory(int a_location, long long a_contents);




/*
NAME

	RunProgram - runs the program in the emulator

SYNOPSIS

	bool Emulator::RunProgram();

DESCRIPTION

	This function will run the program in the emulator.

RETURNS

	True if the program ran successfully, false otherwise.
*/
bool Emulator::runProgram() {
	cout << "Results from emulating program:" << endl;
	int user_input = 0;
	for (long long temp_location = 0; temp_location < MEMSZ; temp_location++) {
		if (m_memory[temp_location] != 0) {
			long long instr = m_memory[temp_location];
			long long opCode = instr / 10'000'000'000;				//Gets first 2 digits of instruction
			long long addr1 = (instr % 1'000'000'00) / 100'000;		//Gets middle 5 digits of instruction
			long long addr2 = instr % 100'000;						//Gets last 5 digits of instruction
			switch (opCode) {
			case 0:
				break;
			case 1:
				// ADD
				addr1 = m_memory[addr1] + m_memory[addr2];
				break;
			case 2:
				// SUB
				addr1 = m_memory[addr1] + m_memory[addr2];
				break;
			case 3:
				// MULT
				addr1 = m_memory[addr1] * m_memory[addr2];
				break;
			case 4:
				// DIV
				if (m_memory[addr2] == 0) {
					Errors::RecordError("Error: Cannot divide by zero.");
					return false;
				}
				addr1 = m_memory[addr1] / m_memory[addr2];
				break;
			case 5:
				// COPY
				m_memory[addr1] = m_memory[addr2];
				break;
			
			case 7:
				// READ
				cout << "? ";
				cin >> user_input;
				m_memory[addr1] = user_input;
				break;
			case 8:
				// WRITE
				cout << m_memory[addr1] << endl;
				break;
			case 9:
				// BRANCH
				temp_location = addr1-1;
				break;
			case 10:
				// BRANCH MINUS
				if (m_memory[addr2] < 0) {
					temp_location = addr1-1;
				}
				break;
			case 11:
				// BRANCH ZERO
				if (m_memory[addr2] == 0) {
					temp_location = addr1-1;
				}
				break;
			case 12:
				// BRANCH POSITIVE
				if (m_memory[addr2] > 0) {
					temp_location = addr1-1;
				}
				break;
			case 13:
				// HALT
				return true;
				break;
			default:
				// If we get here, it means there was an invalid opcode in memory.
				Errors::RecordError("Error: Invalid opcode detected.");
				return false;
				break;
			}
		}
	}
	return true;
}
//bool Emulator::runProgram()

