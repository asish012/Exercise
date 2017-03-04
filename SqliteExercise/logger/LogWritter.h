/*
 * ConsoleLogger.h
 *
 * Updated on: December 6, 2016
 *     Author:
 */

#pragma once

#include "LogPolicy.h"

#include <fstream>
#include <mutex>
#include <unistd.h>

/*
 * ConsoleLogger
 *
 * @brief Writes log to console(std::cerr)
 */
class ConsoleLogger : public LogPolicy
{
public:
    ConsoleLogger(const std::string type, const std::string &fileName, const int lineNumber, const std::string &functionName)
        : LogPolicy(type, fileName, lineNumber, functionName)
    {}

    virtual ~ConsoleLogger()
    {
        std::lock_guard<std::mutex> lockguard(_mutex);
        _buffer << '\n';
        std::string log = _buffer.str();
        UNUSED size_t success = write(STDOUT_FILENO, log.c_str(), log.size());
    }

private:
    std::mutex _mutex;
};


/*
 * FileLogger
 *
 * @brief Writes log to log/Log.txt
 */
class FileLogger : public LogPolicy
{
public:
    FileLogger(const std::string type, const std::string &fileName, const int lineNumber, const std::string &functionName)
        : LogPolicy(type, fileName, lineNumber, functionName)
    {}

    ~FileLogger()
    {
#ifdef DIR_LOG
        _fileName = std::string(DIR_LOG) + '/' + _fileName;
#endif
        std::ofstream output(_fileName.c_str(), std::ios_base::app);
        if (output) {
            _buffer << '\n';
            output << _buffer.str();
        }
        else {
            _buffer << "Couldn't open the LogFile\n";
            std::cerr << _buffer.str();
        }
    }

private:
    std::string _fileName{"Log.txt"};
};
