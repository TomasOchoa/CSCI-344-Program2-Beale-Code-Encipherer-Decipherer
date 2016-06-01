/*  Author:     Tomas Ochoa
 *
 *  Date:       4/28/15
 *
 *  Purpose:        This class header file defines a class for the client socket.
*/

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "socket.h"

class ClientSocket:private Socket
{
    public:
        // Default constructor
        ClientSocket(std::string host,int port);
        virtual ~ClientSocket(){};

        // Overloaded operators to make sending and recieving data
        // easier and also allows for neater code
        const ClientSocket& operator << ( const std::string& ) const;
        const ClientSocket& operator >> ( std::string& ) const;
};

#endif // CLIENTSOCKET_H
