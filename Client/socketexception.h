/*  Author:     Tomas Ochoa
 *
 *  Date:       4/28/15
 *
 *  Purpose:        This header file is to define the socket exception class. Because
 *              the program requires the CLIENT to do the I/O stuff and NOT the SERVER,
 *              this program uses C++'s throw catch mechanism to make it easier for communication
 *              between server/client, and display any erros that may occur.
*/

#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <string>

class SocketException
{
    public:
        SocketException(std::string s):m_s(s){};
        ~SocketException(){};

        std::string description()
        {
            return m_s;
        }

    private:
        std::string m_s;
};

#endif // SOCKETEXCEPTION_H
