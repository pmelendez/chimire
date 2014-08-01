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
#include <json.h> 

class LogSystem {
public:
    
    virtual ~LogSystem();

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
    std::ofstream file;
};

//static const char* endl="\n";

#define _Log LogSystem::get() 

#endif	/* _LOGSYSTEM_H */

