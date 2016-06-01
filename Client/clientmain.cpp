/*  Author:     Tomas Ochoa
 *
 *  Date:       4/28/15
 *
 *  Purpose:        This is the main of the client. Main put's everything together for
 *              the client to work. It also does ALL the I/O stuff. The server does the stuff,
 *              client fetches result and displays it FROM the client.
 *
 */

#include "clientsocket.h"
#include "socketexception.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

// Function Headers for main functions
void show_menu();
void menu_options();
void encipher_option();
void decipher_option();

// main
int main (void)
{
    // Open the file
    ofstream session;
    session.open("BCsession.txt",ios::out|ios::trunc);
    // Show menu and get option
    menu_options();

    return 0;
}

// ******************************************* FUNCTION IMPLEMENTATIONS FOR MAIN ONLY *******************************************
// Show menu function
void show_menu()
{
    // Output File
    ofstream session;
    session.open("BCsession.txt",ios::app);
    // Wrtiting to the output file
    session << endl;
    session << "******************** Beale Cypher Program ********************" << endl;
    session << "                                                              " << endl;
    session << "OPTIONS:                                                      " << endl;
    session << "                                                              " << endl;
    session << "   1. E (Enciphers a line of text using the MBC method)       " << endl;
    session << "   2. D (Deciphers a line of numbers using the MBC method)    " << endl;
    session << "   3. Q (Quits the program)                                   " << endl;
    session << "                                                              " << endl;
    session << "Please enter an option: ";

    cout    << "******************** Beale Cypher Program ********************" << endl;
    cout    << "                                                              " << endl;
    cout    << "OPTIONS:                                                      " << endl;
    cout    << "                                                              " << endl;
    cout    << "   1. E (Enciphers a line of text using the MBC method)       " << endl;
    cout    << "   2. D (Deciphers a line of numbers using the MBC method)    " << endl;
    cout    << "   3. Q (Quits the program)                                   " << endl;
    cout    << "                                                              " << endl;
    cout    << "Please enter an option: ";

    return;
}
// Menu Options
void menu_options()
{
    // Open the output file
    ofstream session;
    session.open("BCsession.txt",ios::app);

    // Basic Variables
    bool quit = true;           // Bool flag while user doesnt want to quit
    char option;                // User's choice

    // Do menu and options while the user doesnt quit
    while(quit)
    {
        // Show menu
        show_menu();
        // Get user option and check for choices
        cin     >> option;
        session << option << endl;
        if ((option == 'e') || (option == 'E'))
            encipher_option();
        else if ((option == 'D') || (option == 'd'))
            decipher_option();
        else if ((option == 'Q') || (option == 'q'))
        {
            session << "Press <RETURN> to close this window...";
            quit = false;
        }
        else
        {
            cout    << "Invalid choice try again! " << endl;
            session << "Invalid choice try again! " << endl;
        }
    }

    // Close the file
    session.close();

    return;
}
// Encipher Option
void encipher_option()
{
    // Open the output file
    ofstream session;
    session.open("BCsession.txt",ios::app);

    // String declarations gor the appropriate command
    // which will then be appeneded to the user input
    // so server can know what to do with it
    string send;
    string ENCIPHER = "E ";

    // Variable for input
    string input;
    int inputsize = 0;

    // Ask user for the input string
    cout    << "Please enter a word(s) or sentence to encode: ";
    session << "Please enter a word(s) or sentence to encode: " << input << endl << endl;

    // Get input (whole line)
    cin.ignore();
    getline(cin,input);
    inputsize = input.size();

    // Show the user his input and the result
    cout    << "Your input: " <<  endl << input << endl << endl;
    session << "Your input: " <<  endl << input << endl << endl;

    // Setup the command to get the enciphered input
    send.append(ENCIPHER);
    send.append(input);
    // NOTE! Server can only recieve 80 characters at a time (including command)
    unsigned size = 80;
    //send.resize(size);

    // Do stuff
    try
    {
        // Create a linux socket to connect to a server
        ClientSocket client_socket ("127.0.0.1",10291991);
        // To get the reply from server
        std::string reply;

        // Try doing stuff, If any errors occur, a messege from the server is displayed
        try
        {
            // Send the input to server
            client_socket << send;
            // Get back response from server
            client_socket >> reply;
        }
        catch(SocketException&){}
            std::cout << "Server response:" << endl << reply << endl << endl;
            session   << "Server response:" << endl << reply << endl << endl;
    }
    catch(SocketException& e)
    {
        std::cout << "Error:" << e.description() << "\n";
        session   << "Error:" << e.description() << "\n";
    }

    // Close the file
    session.close();

    return;
}
//Decipher Option
void decipher_option()
{
    // Open the output file
    ofstream session;
    session.open("BCsession.txt",ios::app);

    // String declarations gor the appropriate command
    // which will then be appeneded to the user input
    // so server can know what to do with it
    string send;
    string DECIPHER = "D ";

    // Declare neccesary variables
    string  the_cipher; // input

    // Get user input (this time it would be encoded ints)
    cout    << "NOTE! Seperate each int with at least one space!" << endl
            << "Please enter encoded text to decode: "            << endl;
    session << "NOTE! Seperate each int with at least one space!" << endl
            << "Please enter encoded text to decode: "            << endl;
    cin.ignore();
    getline(cin,the_cipher);

    // To display the contents of a vector (via c++ refference)
    cout    << endl << "Your coded messege: " << endl << the_cipher << endl << endl;
    session << endl << "Your coded messege: " << endl << the_cipher << endl << endl;

    // Setup the command to get the enciphered input
    send.append(DECIPHER);
    send.append(the_cipher);
    // NOTE! Server can only recieve 80 characters at a time (including command)
    unsigned size = 80;
    send.resize(size);

    // Do stuff
    try
    {
        // Create a linux socket to connect to a server
        ClientSocket client_socket ("127.0.0.1",10291991);
        // To get the reply from server
        std::string reply;

        // Try doing stuff, If any errors occur, a messege from the server is displayed
        try
        {
            // Send the input to server
            client_socket << send;
            // Get back response from server
            client_socket >> reply;
        }
        catch(SocketException&){}
            std::cout << "Server response:" << endl << reply << endl << endl;
            session   << "Server response:" << endl << reply << endl << endl;
    }
    catch(SocketException& e)
    {
        std::cout << "Error:" << e.description() << "\n";
        session   << "Error:" << e.description() << "\n";
    }

    // Close the file
    session.close();

    return;
}

