#ifndef CARBONAPP
#define CARBONAPP
#include <iostream>
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdexcept> 
#include <SocketServer.h>

SocketServer server;
static const int port = 20111;


void leave(int sig);
void start();
void killed(int sig);

class CarbonApp {
    public:
        static void start()
        {
            int n=-1,pid;
            bool accepted;
            std::string msg;

            (void) signal(SIGKILL,killed);
            (void) signal(SIGSTOP,killed);
            (void) signal(SIGTERM,killed);
            (void) signal(SIGHUP,killed);

            (void) signal(SIGINT,leave);
            (void) signal(SIGQUIT,leave);
//            (void) signal(SIGPIPE,SocketServer::broken_socket);

//            ~_Log << "Starting server\n\n";
//            _Log.close();

            if(!server.create(port))
            {
//                _Log << "Error creating the server. Exiting\n";
                exit(1);
            }


            while(1)
            {
                server.msleep(100);

                accepted=server.accept();

                if(accepted)
                {
//                    _Log << "Accepted new connection\n";
                }

                if(server.handleInput()==server.SHUTDOWN)
                {
//                    _Log.close();
                    exit(0);
                }
            }

        }

    private:
        CarbonApp() {}

};

void leave(int sig) {
    //        _Log << "Interrupted..\n";// << endl;
    //        server.shutdown();
    exit(sig);
}

void killed(int sig)
{
    //	_Log << "Process Killed ...\n" ;
    //	_Log << "Shutting down server because a signal:" << sig << "\n";
    //	server.shutdown();
    exit(sig);
}

#endif
