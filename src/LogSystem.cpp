/* 
 * File:   LogSystem.cpp
 * Author: pedro
 * 
 * Created on November 11, 2010, 9:56 AM
 */

#include "LogSystem.h"
#include <ctime>

LogSystem::LogSystem() {
    m_prefix="";
    file.open("./logserver.log" ,std::fstream::app | std::fstream::ate/*,std::fstream::out*/);
}

LogSystem::LogSystem(std::string prefix) {
    m_prefix=prefix;
    file.open("./logserver.log",std::fstream::app | std::fstream::ate/*,std::fstream::out*/);
}

// Check whether the file stream is open, if not it would opened.

void LogSystem::check_if_open()
{
    if(!file.is_open())
    {
        file.open("./logserver.log",std::fstream::app | std::fstream::ate);
    }
}

LogSystem::LogSystem(const LogSystem& orig) {
}

LogSystem::~LogSystem() {
    file.close();
}

LogSystem& LogSystem::operator <<(std::string line)
{

    //writeline(line);
    write(line);
    return *this;
}

LogSystem& LogSystem::operator ~()
{
    //write("[" + gettime() + "] ");
    writetime();
    return *this;
}

void LogSystem::writetime()
{
    write("[" + gettime() + "] ");
}

LogSystem& LogSystem::operator <<(const char* line)
{
    std::string chr = line;
    //writeline(line);
    write(chr);
    return *this;
}

LogSystem& LogSystem::operator <<(int value)
{
    std::string str;
    std::stringstream ss;

    ss << value;
    writeline(ss.str());
    return *this;
}

LogSystem& LogSystem::operator <(std::string line)
{

    write(line);
    return *this;
}

LogSystem& LogSystem::operator <(int value)
{
    std::string str;
    std::stringstream ss;

    ss << value;
    write(ss.str());
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
    check_if_open();
    file << "*:" << line << std::endl;
    //m_prefix.c_str() <<
    //LogSystem::Instance().write(line);
}

void LogSystem::write(std::string line)
{
    check_if_open();
    file <<  m_prefix.c_str() << line;
}

void LogSystem::close()
{
    file.close();
}
