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
    void write(picojson::object obj); 
    void close();

    std::string gettime();

    static LogSystem& get()
    {
        static LogSystem lfile;
        return lfile;
    }
    
private:

    std::string getSeverity(enum severity _severity);
    void write(std::string type, std::string line);
    LogSystem();
    std::ofstream file;
};

inline error (std::string message)
{
    LogSystem::get().write(LogSystem::severity::error, message);
}

inline void error (std::string message, std::unordered_map<std::string, std::string> other_entries)
{
    other_entries["message"] = message;
    LogSystem::get().write(LogSystem::severity::error, other_entries);
}

inline void log (std::string message)
{
    LogSystem::get().write(LogSystem::severity::info, message);
}

inline void log (std::string message, std::unordered_map<std::string, std::string> other_entries)
{
    other_entries["message"] = message;
    LogSystem::get().write(type_entry, other_entries);
}
#endif	/* _LOGSYSTEM_H */

