/*
	Name: Elijah Campbell-Ihim
	Course: Software Design (CMPS 361)
	Professor: Victor Miller
	Project: Assembler for imaginary VC1620 Computer
	File: Errors.cpp - Implementation of the Errors class
*/


#include "stdafx.h"
#include "Errors.h"

vector<string>Errors::m_errorMsgs;
int Errors::m_total_messages;


/*
NAME

	InitErrorReporting - initializes the error reporting vector.

SYNOPSIS

	void InitErrorReporting();

DESCRIPTION

	This function will initialize the error reporting vector, and reset the amount of
	total error messages to 0.

*/
void Errors::InitErrorReporting() {
	m_total_messages = 0;
	if (m_errorMsgs.empty()) {
		return;
	}
	// Clear the vector
	m_errorMsgs.clear();
	return;
}
//void Errors::InitErrorReporting();


/*
NAME

	RecordError - records an error message.

SYNOPSIS

	void RecordError(string a_emsg);
		a_emsg	-> The error message to be recorded.

DESCRIPTION

	This function will record an error message in the error reporting vector,
	and increase the total amount of error messages.

*/
void Errors::RecordError(string a_emsg) {
	if (a_emsg.empty()) {
		return;
	}
	// Record the error message.
	m_errorMsgs.push_back(a_emsg);

	// Increase the total amount of error messages.
	m_total_messages++;
	return;
}
//void Errors::RecordError(string a_emsg);


/*
NAME

	DisplayErrors - displays all the error messages.

SYNOPSIS

	void DisplayErrors();

DESCRIPTION

	This function will display all the error messages stored
	in the error reporting vector.

*/
void Errors::DisplayErrors() {
	if (m_total_messages == 0) {
		return;
	}
	// Display the error messages
	for (auto message : m_errorMsgs) {
		cout << message << endl;
	}
	return;
}
//void Errors::DisplayErrors()

