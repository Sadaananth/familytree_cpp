#pragma once

#include <string>

class Logger
{
public:
    Logger& create() 
    {
        static Logger logger;
        return logger;
    )

private:
    Logger() {}
    ~Logger() {}

    enum class LogLevel : uint8_t {
        error,
        warn,
        info,
        debug
    };
};

template<typename out_stream>
out_stream& operator<<(out_stream& stream, const Logger& logger)
{
    return out_stream;
}
