/*  Author:     Tomas Ochoa
 *
 *  Date:       4/28/15
 *
 *  Purpose:        This is the main of the server. Main put's everything together for
 *              the server to work. It does NOT do ANY of the I/O stuff. The server does the
 *              command that was recieved from the client and sends the result back to the
 *              client. Any screen I/O is done by the client.
 *
 */

// Include neccesarry files
#include "serversocket.h"
#include "socketexception.h"
#include "BCipher.h"
// Include vital c++ librarys
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

// Function headers for the server processes
string encipher(string clientData);
string decipher(string clientData);

int main(void)
{
    cout << "Server Running...\n";

    try
    {
        // Create the socket server
        ServerSocket server(10291991);

        while(true)
        {
            // Create a socket for the incoming client and accept it
            ServerSocket new_client;
            server.accept(new_client);

            try
            {
                while(true)
                {
                    // Recieve the data from the client
                    std::string data;
                    std::string new_data;
                    // Now because the commands by definition will be the first char
                    // of the string, check to first char to either decipher or encipher
                    new_client >> data;
                    // If the first letter in the string is 'E', then that means encipher
                    // else if its a 'D', then decipher
                    if(data.at(0) == 'E')
                    {
                        new_data = encipher(data.substr(2));
                        new_client << new_data;
                    }
                    else if (data.at(0) == 'D')
                    {
                        new_data = decipher(data.substr(2));
                        new_client << new_data;
                    }

                }
            }
            catch (SocketException&) {}

        }
    }
    catch (SocketException& e)
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
  return 0;
}
// ******************************************* FUNCTION IMPLEMENTATIONS FOR MAIN *******************************************
// "Stuff" that does the enciphering
string encipher(string clientData)
{
    // Declare Basic Variables
    BCipher bealer;
    int     ciphervalue,
                      i,
                      inputsize;
    // String variable to send back
    string encoded_data;
    string converted_number;

    inputsize = clientData.size();
    // For loop for cipher and to encode the string (also convert the int back to a string to store into a string)
    for (i = 0;i < inputsize;i++)
    {
        if(((clientData[i] >= ASCIIa) && (clientData[i] <= ASCIIz)) ||       // Lower case letters or
           ((clientData[i] >= ASCIIA) && (clientData[i] <= ASCIIZ)))         // Upper case letter
           {
                ciphervalue = bealer.encode(clientData[i]);
                converted_number = static_cast<ostringstream*>( &(ostringstream() << ciphervalue) )->str();
                encoded_data.append(converted_number);
                encoded_data.append(" ");
           }
    }
    return encoded_data;
}
// "Stuff" that does the deciphering
string decipher(string clientData)
{
    // Declare neccesary variables
    BCipher bealer;
    char    letter;
    int     i = 0,
            decodesize;
    // String variable to send back
    string encoded_data;
    string string_letter;

    // Since the input was taken as a string, convert the string into an int vector
    // Declare a vector to store the string ints
    std::vector<int> decoded_messege;
    std::stringstream ss(clientData);
    // Take the integers of the string and store in into a vector
    while (ss >> i)
    {
        decoded_messege.push_back(i);
        // String delimeted by white space so ignore that
        if (ss.peek() == ' ')
            ss.ignore();
    }

    // Now decode the messege and display the messege one line
    decodesize = decoded_messege.size();
    for (i = 0; i < decodesize; i++)
    {
        letter = bealer.decode(decoded_messege[i]);
        string_letter = letter;
        encoded_data.append(string_letter);
        encoded_data.append(" ");
    }

    return encoded_data;
}
