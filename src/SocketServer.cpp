#include <SocketServer.h>
#include <iostream>
#include <bits/basic_string.h>
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <algorithm>
#include <errno.h>
#include <CarbonApp.h>

bool SocketServer::create(int port)
{
    if ( ! m_socket.create() )
    {
        error( "Couldn't create the socket", {{"reason", strerror(m_socket.last_error)}});
        return false;
    }

    if ( ! m_socket.bind ( port ) )
    {
        error( "Couldn't bind the socket:", {{"reason", strerror(m_socket.last_error)}});
        m_socket.close();
        return false;
    }

    if ( ! m_socket.listen() )
    {
        error("Couldn't listen throught the socket");
        m_socket.close();
        return false;
    }

    return true;
}

bool SocketServer::isActive()
{
    return m_socket.is_open();
}

bool SocketServer::accept()
{
    bool res=false;
    SocketInfo newsocketinfo;
    newsocketinfo=m_socket.accept();

    log ("SocketServer::accept - New connection ");

    if(newsocketinfo.socketID>0)
    {
	socket_pool[newsocketinfo.socketID] = Socket(newsocketinfo);
	auto socket_descriptor_id = newsocketinfo.socketID;
        socket_pool[newsocketinfo.socketID].accepted(std::clock());
        log(fmt::format("Accepted this ip {}", inet_ntoa(newsocketinfo.serv_addr.sin_addr)) ,  
                {{"IP", inet_ntoa(newsocketinfo.serv_addr.sin_addr)}, 
                {"socket", std::to_string(newsocketinfo.socketID)}});
        
        CarbonApp::instance().loop().onReadable(newsocketinfo.socketID,
                [this, socket_descriptor_id]()->bool { this->handleInput(socket_descriptor_id); return true;  } );

        res = true;
    }
    else
    {
        res = false;
    }

    return res;
}

int SocketServer::receive_messages(std::string& msg, int socket_descriptor)
{
    int n=-1;
    auto& _socket = socket_pool[socket_descriptor];
    
    n = _socket.recv(msg);

    if (n>0)
    {
	    _socket.set_last_time(std::clock());
	    // Ignore empty messages
	    if(msg =="")
		    return n;

	    log("Receiving message", {{"incomming message", msg}});

	    _socket.send(msg);

	    //PM: ask for the socket credentials here.
	    if(msg=="!exit")
	    {
		    shutdown();
		    return SHUTDOWN;
	    }

    }

    return n;
}

void SocketServer::shutdown()
{
    //_Log << "Closing the server\n" ;
    for(auto _socket: socket_pool)
    {
        _socket.second.shutdown();
    }
    m_socket.shutdown();

}

void SocketServer::deliver(std::string msg, Socket& p_socket)
{
    int n;
    std::vector<Socket>::iterator it;

    if(p_socket.getSocketInfo().socketID != Socket::NULL_SOCKET )
    {
        p_socket.send(msg);
        return;
    }

    for(auto _socket: socket_pool)
    {
        n=_socket.second.send(msg);
        
        if(n<0)
        {
            // We have problems
            _socket.second.shutdown();
            // erase from socket pool
        }
    }
}

int SocketServer::handleInput(int socket_descriptor)
{
    std::string str;
    int n;

    n=receive_messages(str,socket_descriptor);

    if(n>=0)
    {
        if(n==SHUTDOWN)
        {
            //_Log << "Shutting Down (SocketServer::handleInput)"; 
            return SHUTDOWN;
        }
    }

    return n;
}

void SocketServer::broken_socket(int sig)
{
	//_Log << "Broken socket..."; 
}

void SocketServer::msleep(int milsec)
{
    struct timespec req={0};
    req.tv_nsec = milsec;
    req.tv_sec = 0;//sec;
 
    nanosleep(&req,NULL);
}
