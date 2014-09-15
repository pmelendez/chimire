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
#include <functional>

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
                auto handler = []() -> bool { log("Shutting down Carbon") ;  exit(0); return false; };
                auto error_handler = []() -> bool { log("Interrupting Carbon") ;  exit(1); return false; };
                CarbonApp::instance().loop().onSignal(SIGINT, handler);
                CarbonApp::instance().loop().onSignal(SIGQUIT, handler);
                
                CarbonApp::instance().loop().onSignal(SIGKILL, error_handler);
                CarbonApp::instance().loop().onSignal(SIGSTOP, error_handler);
                CarbonApp::instance().loop().onSignal(SIGTERM, error_handler);
                CarbonApp::instance().loop().onSignal(SIGHUP, error_handler);
                CarbonApp::instance().initialize();
            }
        }

        inline React::MainLoop& loop() 
        {
            return m_loop;
        }

        static CarbonApp& instance()
        {
            static CarbonApp m_instance;
            return m_instance;

        }

    private:
        void initialize() 
        {
            if(!server.create(port))
            {
                // We could not bind the socket to the port so we are exitting the application
                exit(1);
            }

            log (LogSystem::severity::info, "Initializing Carbon");
            m_loop.onReadable(server.socket().id(), [this]() -> bool { log (LogSystem::severity::info, "Accepting new connection"); server.accept(); return true; } );
            m_loop.run();
        }

        CarbonApp() {}
        SocketServer server;
        React::MainLoop m_loop;
};

#endif
