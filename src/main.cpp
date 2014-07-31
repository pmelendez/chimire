#include <json.h>
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
    picojson::object o;
    picojson::value v(5.5);

    o["hello"] = v;
    o["world"] = picojson::value("!!");
    
    std::string json = picojson::value(o).serialize();

    std::cout << json << std::endl;
    
    return 0;
}


