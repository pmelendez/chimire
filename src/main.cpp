#include <CarbonApp.h>
using namespace std;

/*
 * TODO:
 *
 * - Create an abstraction to handle the signals
 * - Create a thread to handle incoming connections
 * - Create an extensible system to handle the different types of request.
 *
 * */

int main()
{
    CarbonApp::start();
    return 0;
}


