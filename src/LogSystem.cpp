/* 
 * File:   LogSystem.cpp
 * Author: pedro
 * 
 * Created on November 11, 2010, 9:56 AM
 */

#include "LogSystem.h"
#include <chrono>
#include <sstream>
#include <json.h>

LogSystem::LogSystem() {
    file.open("./logserver.log" ,std::fstream::app | std::fstream::ate/*,std::fstream::out*/);
}

LogSystem::~LogSystem() {
    file.close();
}

std::string LogSystem::gettime()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    int fraction = (millis - seconds*1000);    
    std::stringstream ss;

    ss << seconds << "." << fraction;
    return ss.str();
}

void LogSystem::write(enum severity _severity, std::string line)
{
    std::string type=getSeverity(_severity);
    write(type, line);
}

std::string LogSystem::getSeverity(enum severity _severity)
{
    std::string type= "INFO";
    
    if (_severity == severity::debug)
    {   
        type = "DEBUG";
    }

    if (_severity == severity::warning)
    {   
        type = "WARNING";
    }

    if (_severity == severity::error)
    {   
        type = "ERROR";
    }

    return type;
}

void LogSystem::write(enum severity type, std::unordered_map<std::string, std::string> _vars)
{
    std::string str_vars;
    picojson::object obj;

    for(auto _item: _vars)
    {
        obj[_item.first] = picojson::value(_item.second);
    }

    obj["type"] = picojson::value(getSeverity(type));
    str_vars = picojson::value(obj).serialize();

    write(obj);
}

void LogSystem::write(std::string type,std::string line)
{
    picojson::object obj;
    picojson::value entry(line);

    obj["message"] = entry;
    obj["type"] = picojson::value(type);
    
    write(obj);
}

void LogSystem::write(picojson::object obj)
{
    if(obj.find("message") == obj.end())
    {
        obj["message"] = picojson::value("");
    }

    obj["t"] = picojson::value(gettime());

    std::string json = picojson::value(obj).serialize();
    file << json << std::endl;
}

void LogSystem::close()
{
    file.close();
}
