/*  Author:     Tomas Ochoa
 *
 *  Date:       4/28/15
 *
 *  Purpose:        This class header file defines a class for the server socket.
*/

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "socket.h"


class ServerSocket : private Socket
{
    public:
        ServerSocket (int port);
        ServerSocket (){};
        virtual ~ServerSocket();

        const ServerSocket& operator << (const std::string&)const;
        const ServerSocket& operator >> (std::string&)const;

        void accept(ServerSocket&);
};

#endif // end if SERVERSOCKET_H
