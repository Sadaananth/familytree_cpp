#pragma once

#include <string>

class LoggerImpl;

class Logger
{
public:
    static Logger& create();

    void log_error();
    void log_warn();
    void log_info();
    void log_debug();

    void add_sink();
private:
    Logger();
    ~Logger();

    LoggerImpl& m_logger_pImpl;
};
