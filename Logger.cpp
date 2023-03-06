#include "Logger.hpp"
#include <thread>
#include <queue>
#include <iostream>
#include <sstream>
#include <mutex>
#include <fstream>

enum class LogLevel : uint8_t
{
    Error,
    Warning,
    Info,
    Debug
};

class LogLineInfo
{
public:
    LogLineInfo(LogLevel level, const std::string& filename, uint32_t lineno);

private:
    LogLevel m_log_level;
    std::string m_file_name;
    uint32_t m_line_no;
};

class LogSink
{
public:
    virtual void print(const std::string& data) = 0;
};

class FileSink : public LogSink
{
public:
    FileSink(const std::string& file_path);

    void print(const std::string& data) override;

private:
    std::ofstream m_out_stream;
};

FileSink::FileSink(const std::string& file_path)
{
    m_out_stream.open(file_path);
    if(!m_out_stream.is_open()) {
        throw std::runtime_error("Failed to open file " + file_path);
    }
}

void FileSink::print(const std::string& data)
{
    m_out_stream << data << std::endl;
}

class ConsoleSink : public LogSink
{
public:
    void print(const std::string& data) override;
};

void ConsoleSink::print(const std::string& data)
{
    std::cout << data << std::endl;
}

class LoggerImpl
{
public:
    static LoggerImpl& instance();

    enum class LogLevel : uint8_t {
        error,
        warn,
        info,
        debug
    };

private:
    LoggerImpl();
    ~LoggerImpl() {}

    void log(LogLevel level);
    void run();
    void sink_output(const std::string& output_data);

    std::thread m_thread;

    std::queue<std::string> m_log_list;
    std::mutex m_mutex;
};

LoggerImpl& LoggerImpl::instance()
{
    static LoggerImpl loggerImpl;
    return loggerImpl;
}

LoggerImpl::LoggerImpl()
{
    m_thread = std::thread(&LoggerImpl::run, this);
}

void LoggerImpl::log(LogLevel level)
{
    std::stringstream stream;

    std::lock_guard<std::mutex> lock(m_mutex);
    m_log_list.push(stream.str());
}

void LoggerImpl::run()
{
    while(true) {
        if(!m_log_list.empty()) {
            
            std::string outptstring;
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                outptstring = m_log_list.front();
                m_log_list.pop();
            }
            sink_output(outptstring);
        }
    }
}

void LoggerImpl::sink_output(const std::string& output_data)
{

}

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::Logger() : m_logger_pImpl(LoggerImpl::instance())
{

}

Logger::~Logger()
{

}

void Logger::add_sink()
{

}

std::stringstream& Logger::log_error()
{
    return Logger::instance().;
}

std::stringstream& Logger::log_warn()
{
    return Logger::instance();
}

std::stringstream& Logger::log_info()
{
    return Logger::instance();
}

std::stringstream& Logger::log_debug()
{
    return Logger::instance();
}

Logger& Logger::operator<<(const std::string& data)
{    
    return *this;
}
