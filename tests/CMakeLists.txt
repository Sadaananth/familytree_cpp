cmake_minimum_required(VERSION 3.16)

project(LoggerTest)

set(INC ${PROJECT_SOURCE_DIR}/../)

set(SOURCES
${PROJECT_SOURCE_DIR}/LoggerTest.cpp
${PROJECT_SOURCE_DIR}/../Logger.cpp)

add_executable(loggertest ${SOURCES})
set_property(TARGET loggertest PROPERTY CXX_STANDARD 17)
target_include_directories(loggertest PUBLIC ${PROJECT_SOURCE_DIR}/../)
target_link_libraries(loggertest -lpthread)