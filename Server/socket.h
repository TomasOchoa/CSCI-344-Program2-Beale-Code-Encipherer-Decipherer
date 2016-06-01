/*  Author:     Tomas Ochoa
 *
 *  Date:       4/28/15
 *
 *  Purpose:        The purpose of this header file is to define the socket class to
 *              make implementation of a client to server connection much easier and
 *              less tedious for implementations of ANY socket-client based programs
 *              in the future.
 *
 */

// Necessary function headers for the socket class
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

#ifndef SOCKET_H
#define SOCKET_H

// Global variables for max amount of:
const int MAXHOSTNAME    = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV        = 100000;

class Socket
{
    public:
        Socket();
        virtual ~Socket();          // Virtual to allow to be overriden

        // Server Initialization
        bool create();
        bool bind(const int port);
        bool listen() const;
        bool accept(Socket&) const;
        // Client Initialization
        bool connect(const std::string host, const int port);
        // Data Transmission
        bool send(const std::string) const;
        int  recieve(std::string&) const;
        // Error checking
        void setNonBblocking(const bool);
        bool isValid() const
        {
            return sockDescriptor != -1;
        }
    private:
        int sockDescriptor;
        sockaddr_in DictServer;
};

#endif // SOCKET_H
