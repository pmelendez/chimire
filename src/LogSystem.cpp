/* 
 * File:   LogSystem.cpp
 * Author: pedro
 * 
 * Created on November 11, 2010, 9:56 AM
 */

#include "LogSystem.h"
#include <chrono>
#include <sstream>

LogSystem::LogSystem() {
    file.open("./logserver.log" ,std::fstream::app | std::fstream::ate/*,std::fstream::out*/);
}

LogSystem::~LogSystem() {
    file.close();
}

void LogSystem::writetime()
{
    write("[" + gettime() + "] ");
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

//PM : this need more work to be less verbose.

void LogSystem::writeline(std::string line)
{
    file << "*:" << line << std::endl;
    //LogSystem::Instance().write(line);
}

void LogSystem::write(std::string line)
{
}

void LogSystem::close()
{
    file.close();
}
