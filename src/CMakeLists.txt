cmake_minimum_required(VERSION 3.16)

project(FamilyTreeGen)

set(SOURCES
${PROJECT_SOURCE_DIR}/main.cpp
${PROJECT_SOURCE_DIR}/core/Person.cpp
${PROJECT_SOURCE_DIR}/core/Family.cpp
${PROJECT_SOURCE_DIR}/core/FamilyTree.cpp)

include(FetchContent)
FetchContent_Declare(
    SadaLogger
    # URL https://github.com/Ananthsada/SadaLogger/archive/refs/tags/v0.0.1.zip
    URL https://github.com/Ananthsada/SadaLogger/archive/refs/heads/include_header_in_cmake.zip
)

FetchContent_MakeAvailable(SadaLogger)

add_custom_target(
    prebuild
    COMMAND wget -nc -P ${PROJECT_SOURCE_DIR}/../external/json/ https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
)

add_executable(familytreegen ${SOURCES})
set_property(TARGET familytreegen PROPERTY CXX_STANDARD 17)
add_dependencies(familytreegen prebuild)
target_include_directories(familytreegen PUBLIC ${PROJECT_SOURCE_DIR}/../external/json/ ${PROJECT_SOURCE_DIR}/)
target_link_libraries(familytreegen SadaLogger)

# install(TARGETS familytreegen DESTINATION ${CMAKE_BINARY_DIR}/bin/)
