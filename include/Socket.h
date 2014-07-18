/* 
 * File:   Socket.h
 * Author: pedro
 *
 * Created on July 17, 2014, 8:26 AM based on previous version Oct 17, 2010 11:56 AM
 */

#ifndef _SOCKET_H
#define	_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <ctime>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <strings.h>

#include <netdb.h>

#include <errno.h>
#include "ISocket.h"

class Socket : public ISocket {
public:
    Socket();
    Socket(const Socket& orig);
    Socket(int socket_id,sockaddr_in addr);
    Socket(SocketInfo info);
    virtual ~Socket();

    const SocketInfo getSocketInfo() const;
    bool create();
    bool bind ( const int port );
    bool listen();
    bool listen(const int p_max_connections);
    SocketInfo accept ( /*Socket&*/ );
    void accepted(clock_t pTime);
    void close();
    void shutdown();
    bool is_open();
    clock_t get_last_time();
    void set_last_time(clock_t time);

    // Client initialization
    bool connect ( const std::string host, const int port );
    bool is_loggedin();
    void login(bool p_result, std::string p_user_id);
    clock_t get_accepted_time();

    // Data Transmission
    bool send ( const std::string& ) ;
    int recv ( std::string& msg ) const;

    std::string get_user_id();

    void operator = (int p_socket_id);

    int last_error;

    static const int NULL_SOCKET=-100;
    static const int DEFAULT_MAXCONNECTIONS=1000;
private:
    struct sockaddr_in serv_addr;
    int socketID;
    int max_connections;
    bool m_is_open;
    bool m_is_loggedin;
    clock_t m_accepted_time;
    clock_t m_last_time_message;
    std::string userId;

    void setSocketInfo(const SocketInfo info);
    void init_variables();
};


#endif	/* _SOCKET_H */

