/*
    Name: Elijah Campbell-Ihim
    Course: Software Design (CMPS 361)
    Professor: Victor Miller
    Project: Assembler for imaginary VC1620 Computer
    File: FileAccess.cpp - Implementation of the FileAccess class
*/


#include "stdafx.h"
#include "FileAccess.h"


/*
NAME

    FileAccess - constructor for the FileAccess class.

SYNOPSIS

    FileAccess::FileAccess(int argc, char *argv[]);
        argc -> The number of command line arguments
        argv -> The array of command line arguments

DESCRIPTION

    This function will check to see if the file with the
    specified name exists, and will open it if such
    a file does exist. Otherwise, this function will terminate
    the program.

*/
FileAccess::FileAccess( int argc, char *argv[] )
{
    // Check that there is exactly one run time parameter.
    if( argc != 2 ) {
        cerr << "Usage: Assem <FileName>" << endl;
        exit( 1 );
    }
    // Open the file.  One might question if this is the best place to open the file.
    // One might also question whether we need a file access class.
    m_sfile.open( argv[1], ios::in );

    // If the open failed, report the error and terminate.
    if( ! m_sfile ) {
        cerr << "Source file could not be opened, assembler terminated."
            << endl;
        exit( 1 ); 
    }
}
//FileAccess::FileAccess(int argc, char* argv[]);


/*
NAME

    ~FileAccess - close the file

SYNOPSIS

    FileAccess::~FileAccess();

DESCRIPTION

    This function will close the specified file.

*/
FileAccess::~FileAccess( )
{
    // Not that necessary in that the file will be closed when the program terminates, but good form.
    m_sfile.close( );
}
//FileAccess::~FileAccess();



/*
NAME

    GetNextLine - get the next line in the file

SYNOPSIS

    bool FileAccess::GetNextLine(string &a_line);
        a_line -> the current line in the file

DESCRIPTION

    This function will read the current line in the file.
    Nothing will be read if the end of the file has been
    reached.

RETURNS

    True if a line was read (the end of the file has not yet been reached).
    False if there is no more data to be read (the end of the file was reached).
*/
bool FileAccess::GetNextLine( string &a_line )
{
    // If there is no more data, return false.
    if( m_sfile.eof() ) {
    
        return false;
    }
    getline( m_sfile, a_line );
    
    // Return indicating success.
    return true;
}
//bool FileAccess::GetNextLine( string &a_line );


/*
NAME

    Rewind - Clear all the flags and return to start of the file

SYNOPSIS

    void FileAccess::Rewind();

DESCRIPTION

    This function will clear all the file flags and
    go back to the start of the file.

*/
void FileAccess::rewind( )
{
    // Clean all file flags and go back to the beginning of the file.
    m_sfile.clear();
    m_sfile.seekg( 0, ios::beg );
}
//void FileAccess::rewind( );

