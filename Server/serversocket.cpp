/*  Author:     Tomas Ochoa
 *
 *  Date:       3/31/15
 *
 *  Purpose:        This file is the implementation of the ServerSocket class defined in
 *              "serversocket.h"
*/

#include "serversocket.h"
#include "socketexception.h"

ServerSocket::ServerSocket ( int port )
{
    if (!Socket::create())
    {
        throw SocketException("Could not create server socket.");
    }

    if (!Socket::bind(port))
    {
        throw SocketException("Could not bind to port.");
    }

    if (!Socket::listen())
    {
        throw SocketException("Could not listen to socket.");
    }
}

ServerSocket::~ServerSocket()
{
}

const ServerSocket& ServerSocket::operator << (const std::string& s)const
{
    if(!Socket::send(s))
    {
        throw SocketException("Could not write to socket.");
    }

    return *this;
}

const ServerSocket& ServerSocket::operator >> (std::string& s)const
{
    if(!Socket::recieve(s))
    {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
    if(!Socket::accept(sock))
    {
        throw SocketException("Could not accept socket.");
    }
}
