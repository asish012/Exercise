/*
 * LogPolicy.h
 *
 * Updated on: December 6, 2016
 *     Author:
 */

#ifndef LOGPOLICY_H_
#define LOGPOLICY_H_

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>


#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif


class LogPolicy
{
public:
    LogPolicy(const std::string type, const std::string &fileName, const int lineNumber, const std::string &functionName)
    {
        addHeader(type, fileName, lineNumber, functionName);
    }

    virtual ~LogPolicy() {}

protected:
    std::string logTime()
    {
        std::stringstream ss;

        time_t now = std::time(nullptr);
        ss << std::put_time(std::localtime(&now), "%F %T");

        return ss.str();
    }

    void addHeader(const std::string type, const std::string &fileName, const int lineNumber, const std::string &functionName) {
        _buffer << '|' << type << "\t|" << logTime() << '|' << fileName << ':' << lineNumber << ':' << functionName << ':';
    }

    std::stringstream _buffer;

public:
    template <typename T>
    LogPolicy& operator<<(const T &t) {
        _buffer << ' ' << t;
        return *this;
    }
};

#endif /* LOGPOLICY_H_ */
