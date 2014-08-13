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
#include <format.h>
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
#define INFO(...) (LogSystem::get().write(LogSystem::severity::info, fmt::format(__VA_ARGS__)))
#define DEBUG(...) (LogSystem::get().write(LogSystem::severity::debug, fmt::format(__VA_ARGS__)))
#define WARNING(...) (LogSystem::get().write(LogSystem::severity::warning, fmt::format(__VA_ARGS__)))
#define ERROR(...) (LogSystem::get().write(LogSystem::severity::error, fmt::format(__VA_ARGS__)))
#endif	/* _LOGSYSTEM_H */

