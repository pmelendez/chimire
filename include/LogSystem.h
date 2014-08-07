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
#include <unordered_map>

class LogSystem {
public:
    
    enum severity { debug, info, warning, error  };
    virtual ~LogSystem();

    void write(enum severity type ,std::string line);
    void write(enum severity type, std::unordered_map<std::string, std::string> _vars);
    void close();

    std::string gettime();

    static LogSystem& get()
    {
        static LogSystem lfile;
        return lfile;
    }
    
private:

    void write(std::string type, std::string line);
    LogSystem();
    std::ofstream file;
};

//static const char* endl="\n";

#define _Log LogSystem::get() 
#define INFO(X) (LogSystem::get().write(LogSystem::severity::info, X))
#define DEBUG(X) (LogSystem::get().write(LogSystem::severity::debug, X))
#define WARNING(X) (LogSystem::get().write(LogSystem::severity::warning, X))
#define ERROR(X) (LogSystem::get().write(LogSystem::severity::error, X))
#endif	/* _LOGSYSTEM_H */

