/* 
 * File:   LogSystem.cpp
 * Author: pedro
 * 
 * Created on November 11, 2010, 9:56 AM
 */

#include "LogSystem.h"
#include <ctime>

LogSystem::LogSystem() {
    file.open("./logserver.log" ,std::fstream::app | std::fstream::ate/*,std::fstream::out*/);
}

LogSystem::~LogSystem() {
    file.close();
}

LogSystem& LogSystem::operator <<(std::string line)
{

    return *this;
}

LogSystem& LogSystem::operator ~()
{
    return *this;
}

void LogSystem::writetime()
{
    write("[" + gettime() + "] ");
}

LogSystem& LogSystem::operator <<(const char* line)
{
    return *this;
}

LogSystem& LogSystem::operator <<(int value)
{
    return *this;
}

LogSystem& LogSystem::operator <(std::string line)
{
    return *this;
}

LogSystem& LogSystem::operator <(int value)
{
   return *this;
}

std::string LogSystem::gettime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];
    std::string str;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime(buffer, 80 , "%x %I:%M:%S %p", timeinfo);
    str = buffer;     

    //return asctime (timeinfo);
    //return ctime(&rawtime);
    return str;
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
