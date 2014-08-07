#include <LogSystem.h>
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
    //CarbonApp::start();
   INFO("This is an info ");
   WARNING("This is a warning");
   DEBUG("This is a debug");
   ERROR("This is an error");

   std::unordered_map<std::string, std::string> t;
   t["nombre"] = "pedro";
   t["apellido"] = "melendez";
   t["mensaje"] = "jaja";

   ERROR(t);

   return 0;
}


