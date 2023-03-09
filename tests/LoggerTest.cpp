#include <utils/Logger.hpp>
#include <thread>
#include <chrono>

int main()
{
    auto& test = Logger::log_debug();

    test << "Main" << std::endl;

    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
