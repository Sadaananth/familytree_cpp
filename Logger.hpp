#pragma once

#include <string>

class LoggerImpl;

class Logger
{
public:
    static Logger& instance();

    static Logger& log_error();
    static Logger& log_warn();
    static Logger& log_info();
    static Logger& log_debug();

    Logger& operator<<(const std::string& data);
    void add_sink();
private:
    Logger();
    ~Logger();

    LoggerImpl& m_logger_pImpl;
};
