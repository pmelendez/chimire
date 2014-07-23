/* 
 * File:   Socket.cpp
 * Author: pedro
 * 
 * Created on July 17, 2014, 8:26 AM based on previous version Oct 17, 2010 11:56 AM
 */

#include "Socket.h"



Socket::Socket() {
    socketID=NULL_SOCKET;
    max_connections= DEFAULT_MAXCONNECTIONS;

    init_variables();
}

Socket::Socket(int socket_id, sockaddr_in addr)
{
    max_connections= DEFAULT_MAXCONNECTIONS;
    socketID=socket_id;
    serv_addr=addr;

    init_variables();
}

Socket::Socket(const Socket& orig) {
    Socket& orig_socket=const_cast<Socket&>(orig);
    max_connections= DEFAULT_MAXCONNECTIONS;
    setSocketInfo(orig.getSocketInfo());

    //init_variables();
    m_is_open=orig_socket.is_open();
    last_error=orig_socket.last_error;
    m_is_loggedin=orig_socket.is_loggedin();
    userId = orig_socket.get_user_id();
}

Socket::Socket(SocketInfo info)
{
    serv_addr=info.serv_addr;
    socketID=info.socketID;

    init_variables();
}

Socket::~Socket() {

    if(m_is_open)
    {
        close();
        shutdown();
        m_is_open=false;
    }
}

void Socket::init_variables()
{
    m_is_open=false;
    last_error=0;
    m_is_loggedin=false;
}

void Socket::login(bool p_result,std::string p_user_id)
{
    m_is_loggedin=p_result;
    userId = p_user_id;
}

std::string Socket::get_user_id()
{
    return userId;
}

const SocketInfo Socket::getSocketInfo() const
{
    struct SocketInfo info;

    info.serv_addr=serv_addr;
    info.socketID=socketID;

    return info;
}

void Socket::setSocketInfo(const SocketInfo info)
{
    socketID=info.socketID;
    serv_addr=info.serv_addr;
}

SocketInfo Socket::accept()
{
    int clilen;
    struct sockaddr_in cli_addr;
    struct SocketInfo result;
    

    clilen=sizeof(cli_addr);
    result.socketID=-1;
    result.socketID=::accept(socketID, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
    result.serv_addr=cli_addr;

    /*if(result.socketID>0)
    {
        m_accepted_time = std::clock();
    }*/

    return result;
}

void Socket::accepted(clock_t pTime)
{
    m_accepted_time= pTime;
}

bool Socket::is_open()
{
    return m_is_open;
}


clock_t Socket::get_accepted_time()
{
    return m_accepted_time;
}

bool Socket::bind(const int port)
{
    bool result=true;
    int status;

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; //ntohl(INADDR_LOOPBACK);
    serv_addr.sin_port = htons(port);

    status=::bind(socketID, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    if(status<0)
    {
        result=false;
        last_error=errno;
        //EADDRINUSE;
    }
    else
    {
        m_is_open=true;
    }

    return result;
}

void Socket::close()
{
    ::close(socketID);
}

void Socket::shutdown()
{
    ::shutdown(socketID,SHUT_RDWR);
}

bool Socket::connect(const std::string host, const int port)
{
    struct hostent *server;
    int result;

    bzero((char *) &serv_addr, sizeof(serv_addr));

    server= gethostbyname(host.c_str());

    if(socketID==NULL_SOCKET)
    {
        create();
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr=*((unsigned long*)server->h_addr);

    result=false;

    if(socketID>0)
    {
        result=::connect(socketID,(const sockaddr*)&serv_addr,sizeof(serv_addr));

        if(result)
        {
            m_is_open=true;
        }
    }

    return result;
}

bool Socket::create()
{
    bool res=false;
    socketID = socket(AF_INET, SOCK_STREAM |SOCK_NONBLOCK , 0);

    if(socketID>0)
    {
        res=true;
    }
    else
    {
        last_error=errno;
        return false;
    }

    int optval = 1 ;
    if (setsockopt(socketID,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int)) == -1)
    {
        last_error=errno;
        return false;
    }
    //PM: check this... SO_LINGER
   
    return res;
}

bool Socket::listen() 
{
    int status;
    bool result=true;

    status=::listen(socketID,max_connections);

    if(status<0)
        result=false;

    return result;
}

bool Socket::listen(const int p_max_connections) 
{
    max_connections=p_max_connections;

    return listen();
}

int Socket::recv(std::string& msg) const
{
    int n;
    char buffer[256];
    bzero(buffer,256);

    n = ::recv(socketID,buffer,255,MSG_DONTWAIT);
    if (n >= 0)
    {
        msg=buffer;
    }

    return n;
}

bool Socket::send(const std::string &msg) 
{
    /*bool res=true;
    int status;

    status=write(socketID,msg.c_str(),msg.size());

    if(status==-1)
    {
        res=false;
    }*/



    return true; //send(new_msg);
}

void Socket::operator =(int p_socket_id)
{
    socketID=p_socket_id;
}

bool Socket::is_loggedin()
{
    return m_is_loggedin;
}

clock_t Socket::get_last_time()
{
    return m_last_time_message;
}

void Socket::set_last_time(clock_t time)
{
    m_last_time_message = time;
}
