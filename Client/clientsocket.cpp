/*  Author:     Tomas Ochoa
 *
 *  Date:       3/31/15
 *
 *  Purpose:        This file is the implementation of the ClientSocket class defined in
 *              clientsocket.h.
*/

#include "clientsocket.h"
#include "socketexception.h"

// Default constructor for the client socket class
ClientSocket::ClientSocket(std::string host, int port)
{
    if(!Socket::create())
    {
        throw SocketException("Could not create client socket.");
    }

    if(!Socket::connect(host,port))
    {
        throw SocketException("Could not bind to port.");
    }
}

// Overloading of the operators for clientsocket class to make
// sending information between the server and client much easier to code
const ClientSocket& ClientSocket::operator << (const std::string& s)const
{
    if(!Socket::send(s))
    {
        throw SocketException("Could not write to socket.");
    }
    return *this;
}

// Overloading of the operators for clientsocket class to make
// recieving information between the server and client much easier to code
const ClientSocket& ClientSocket::operator >>(std::string& s) const
{
    if(!Socket::recieve(s))
    {
        throw SocketException("Could not read from socket.");
    }
    return *this;
}
