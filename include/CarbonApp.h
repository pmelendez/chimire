#ifndef CARBONAPP
#define CARBONAPP
#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdexcept> 
#include <thread>
#include <reactwrapper.h>
#include <SocketServer.h>

static const int port = 20111;
static const int sleep_in_ms = 100;

void leave(int sig);
void start();
void killed(int sig);

class CarbonApp {
    public:
        static void start()
        {
            static bool run_once=true;

            if(run_once)
            {
                run_once = false;
                std::string msg;

                (void) signal(SIGKILL,killed);
                (void) signal(SIGSTOP,killed);
                (void) signal(SIGTERM,killed);
                (void) signal(SIGHUP,killed);

                (void) signal(SIGINT,leave);
                (void) signal(SIGQUIT,leave);
                //(void) signal(SIGPIPE,SocketServer::broken_socket);
                CarbonApp::instance().initialize();
            }
        }

    private:
        static CarbonApp& instance()
        {
            static CarbonApp m_instance;
            return m_instance;

        }

        void initialize() 
        {
            if(!server.create(port))
            {
                // PM@TODO Launch an error
            }

           
            // PM@TODO We probably would need to use epoll or something like it instead of sleep.
            std::thread conn_accepter_thread( [this]() { while(server.isActive()) { server.accept(); std::this_thread::sleep_for(std::chrono::milliseconds(sleep_in_ms)); }  } );
            std::thread conn_handler_thread( [this]() { while(server.isActive()) { server.handleInput();  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_in_ms)); }  } );
            conn_handler_thread.join();

            loop.run();
        }

        CarbonApp() {}
        SocketServer server;
        React::MainLoop loop;
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
