/* 
 * File:   LogSystem.h
 * Author: pedro
 *
 * Created on November 11, 2010, 9:56 AM
 */

#ifndef _LOGSYSTEM_H
#define	_LOGSYSTEM_H

#include <fstream>
#include <sstream>
#include <string>

class LogSystem {
public:
    
    virtual ~LogSystem();

    LogSystem& operator ~ ();
    LogSystem& operator << (std::string line);
    LogSystem& operator << (int values);
    LogSystem& operator << (const char* line);
    LogSystem& operator < (std::string line);
    LogSystem& operator < (int values);

    void writetime();
    void writeline(std::string line);
    void write(std::string line);
    void close();

    std::string gettime();

    static LogSystem& get()
    {
        static LogSystem lfile;
        return lfile;
    }
    
private:

    LogSystem();
    LogSystem(std::string prefix);
    LogSystem(const LogSystem& orig);

    std::ofstream file;

    void check_if_open();

    std::string m_prefix;
};

static const char* endl="\n";

#define _Log LogSystem::get() 

#endif	/* _LOGSYSTEM_H */

