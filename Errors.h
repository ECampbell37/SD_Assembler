/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: Errors.h - Class to manage error reporting
*/


#ifndef _ERRORS_H
#define _ERRORS_H

#include <string>
#include <vector>

class Errors {

public:
    
    // Initializes error reports.
    static void InitErrorReporting();


    // Records an error message.
    static void RecordError(string a_emsg);


    // Displays the collected error message.
    static void DisplayErrors();



private:

    static vector<string> m_errorMsgs;  //Vector to hold error messages

    static int m_total_messages;        //Tracks total number of error messages in vector
};
#endif