/* 
 * File:   SocketServer.h
 * Author: pedro
 *
 */

#ifndef _SOCKETSERVER_H
#define	_SOCKETSERVER_H

#include "Socket.h"
#include "LogSystem.h"
#include <ctime>
#include <list>
#include <set>

class SocketServer {
public:
    SocketServer() {};
    bool create(int port);
    bool accept();
    virtual ~SocketServer() {};
    int receive_messages(std::string& msg);
    void deliver(std::string msg, Socket& p_socket);
    int handleInput();
    void shutdown();
    static const int SHUTDOWN=1000;
    std::string get_user_list(std::string group_id);
    std::string get_groups();
    bool isActive();
    inline const Socket& socket() { return m_socket; }

    // PM: Time out from accepting the socket until the client perform the login
    static const int LOGIN_TIMEOUT=15;
    static const int MAX_TIME_BETWEEN_MSG_TIMEOUT=120;

    static void broken_socket(int sig);
    static void msleep(int milsec );
    
private:
    Socket m_socket;
    std::list<Socket> socket_pool;

 };

#endif	/* _SOCKETSERVER_H */

