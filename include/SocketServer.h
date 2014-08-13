/* 
 * File:   SocketServer.h
 * Author: pedro
 *
 * Created on October 17, 2010, 2:43 PM
 */

#ifndef _SOCKETSERVER_H
#define	_SOCKETSERVER_H

#include "Socket.h"
#include "LogSystem.h"
#include <ctime>
#include <list>
#include <set>
//#include <boost/shared_ptr.hpp>

//#include <boost/array.hpp>


//typedef boost::shared_ptr<Message> MessagePtr;


class SocketServer {
public:
    SocketServer();
    SocketServer(const SocketServer& orig);
    bool create(int port);
    bool accept();
    virtual ~SocketServer();
    int receive_messages(std::string& msg);
    void deliver(std::string msg, Socket& p_socket);
    int handleInput();
    void shutdown();
    static const int SHUTDOWN=1000;
    std::string get_user_list(std::string group_id);
    std::string get_groups();
    bool isActive();

    // PM: Time out from accepting the socket until the client perform the login
    static const int LOGIN_TIMEOUT=15;
    static const int MAX_TIME_BETWEEN_MSG_TIMEOUT=120;

    static void broken_socket(int sig);
    static void msleep(int milsec );
    
private:
    Socket socket;
    std::list<Socket> socket_pool;

    // PM: The problem is here. It is allocating Message objects and no the real subclass.
    // the problem is how to call the proper version of the function without an explicit cast.
   // std::vector<MessagePtr> message_manager;

};

#endif	/* _SOCKETSERVER_H */

