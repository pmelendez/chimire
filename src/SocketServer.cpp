#include <SocketServer.h>
#include <iostream>
#include <bits/basic_string.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <errno.h>


SocketServer::SocketServer() {
}

SocketServer::SocketServer(const SocketServer& orig) {
}

SocketServer::~SocketServer() {
}

bool SocketServer::create(int port)
{
    if ( ! socket.create() )
    {
        _Log << "Couldn't create the socket:" < strerror(socket.last_error) < "\n";
        return false;
    }

    if ( ! socket.bind ( port ) )
    {
      _Log << "Couldn't bind the socket:" < strerror(socket.last_error) < "\n";// << std::endl;
      socket.close();
      return false;
    }

    if ( ! socket.listen() )
    {
      _Log << "Couldn't listen throught the socket\n";
      socket.close();
      return false;
    }

    return true;
}

bool SocketServer::isActive()
{
    return socket.is_open();
}

bool SocketServer::accept()
{
    bool res=false;
    SocketInfo newsocketinfo;
    newsocketinfo=socket.accept();

    if(newsocketinfo.socketID>0)
    {
        socket_pool.push_back(Socket(newsocketinfo));
        auto last = socket_pool.back();
        last.accepted(std::clock());
        //~_Log << "Accepted Socket #" < socket_pool[socket_pool.size()-1].getSocketInfo().socketID < "\n";
        res = true;
    }
    else
    {
        res = false;
    }

    return res;
}

int SocketServer::receive_messages(std::string& msg)
{
    int n=-1;

    //PM@TODO Probably using epoll would be better than this

    for (auto& _socket : socket_pool )
    {
        n = _socket.recv(msg);
        if(n>=0)
        {
            _socket.set_last_time(std::clock());
            
            if(msg!="")
            {
                ~_Log < "Processing message :" < msg < "\n";
            }

            //PM: ask for the socket credentials here.
            if(msg=="!exit\r\n")
            {
                shutdown();
                return SHUTDOWN;
            }

            // Ignore empty messages
            if(msg =="")
                continue;

        }
        else
        {
            /* We have no pending messages, let's check if the socket is logged in
               if not we are closing it if the time is out*/

            // PM@TODO In the case of last message time we should try to write on the socket to see if it is responding.
            // some like <if last_msg_delta >= MAXTIME*3/4 then send a keep alive message>

            clock_t current= std::clock();
            clock_t clock_delta, last_msg_delta, accepted_time;

            accepted_time = _socket.get_accepted_time();
            clock_delta=current - accepted_time;
            last_msg_delta = current - _socket.get_last_time();

            //if((!it->is_loggedin() && clock_delta >= LOGIN_TIMEOUT*CLOCKS_PER_SEC)/* || ( last_msg_delta >= MAX_TIME_BETWEEN_MSG_TIMEOUT*CLOCKS_PER_SEC)*/)
            if(errno != EWOULDBLOCK || errno != EAGAIN )
            {                
                /*~_Log < "Erasing socket #" < it->getSocketInfo().socketID < "\n";
                _Log < "\t\t Reason: Timeout " < (clock_delta/CLOCKS_PER_SEC) < "\n";
                _Log < "\t\t         Login " < it->is_loggedin() < "\n";
*/
                _socket.close();
                _socket.shutdown();

                //socket_pool.erase(it);
            }
        }
    }

    return n;
}

void SocketServer::shutdown()
{
    ~_Log << "Closing the server\n" ;
    for(auto _socket: socket_pool)
    {
        _socket.shutdown();
    }
    socket.shutdown();

}

void SocketServer::deliver(std::string msg, Socket& p_socket)
{
    int n;
    std::vector<Socket>::iterator it;
    //DeliverableMessage dm;

    //dm.set(msg);

    if(p_socket.getSocketInfo().socketID != Socket::NULL_SOCKET )
    {
        p_socket.send(msg);
        return;
    }

    for(auto _socket: socket_pool)
    {
        n=_socket.send(msg);
        
        if(n<0)
        {
            // We have problems
            _socket.shutdown();
            // erase from socket pool
        }
    }
}

int SocketServer::handleInput()
{
    std::string str;
    int n;

    n=receive_messages(str);

    if(n>=0)
    {
        if(n==SHUTDOWN)
        {
            ~_Log << "Shutting Down (SocketServer::handleInput)" << endl;
            return SHUTDOWN;
        }
    }
    else
    {
        int a;
        a=0;
    }

}

void SocketServer::acceptConnections()
{
    
}


void SocketServer::broken_socket(int sig)
{
	~_Log << "Broken socket..." << endl;
}

void SocketServer::msleep(int milsec)
{
    struct timespec req={0};
    req.tv_nsec = milsec;
    req.tv_sec = 0;//sec;
 
    nanosleep(&req,NULL);
}
