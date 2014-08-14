/* 
 * File:   ISocket.h
 * Author: pedro
 *
 * Created on January 19, 2011, 10:20 AM
 */

#ifndef _ISOCKET_H
#define	_ISOCKET_H

#include <netinet/in.h>
#include <arpa/inet.h>

struct SocketInfo
{
    struct sockaddr_in serv_addr;
    int socketID;
    std::string groupID;
};

struct ISocket
{
    virtual const SocketInfo getSocketInfo() const = 0;
    virtual bool create() = 0;
    virtual bool bind ( const int port ) = 0;
    virtual bool listen() = 0;
    virtual bool listen(const int p_max_connections) = 0;
    virtual SocketInfo accept ( /*Socket&*/ ) = 0;
    virtual void accepted(clock_t pTime) = 0;
    virtual void close() = 0;
    virtual void shutdown() = 0;
    virtual bool is_open() = 0;

    // Client initialization
    virtual bool connect ( const std::string host, const int port ) = 0;
    virtual bool is_loggedin() = 0;
    virtual void login(bool p_result, std::string p_user_id) = 0;
    virtual clock_t get_accepted_time() = 0;

    // Data Transmission
    virtual bool send ( const std::string& ) = 0 ;
    virtual int recv ( std::string& msg ) const = 0;

    virtual void operator = (int p_socket_id) = 0;
};

#endif	/* _ISOCKET_H */

