#pragma once

#include <string>
#include <sstream>

class LoggerImpl;

class Logger
{
public:
    static Logger& instance();

    static std::stringstream& log_error();
    static std::stringstream& log_warn();
    static std::stringstream& log_info();
    static std::stringstream& log_debug();

    Logger& operator<<(const std::string& data);
    void add_sink();
private:
    Logger();
    ~Logger();

    LoggerImpl& m_logger_pImpl;
};
