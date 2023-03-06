cmake_minimum_required(VERSION 3.16)

project(FamilyTree)

set(INC ${PROJECT_SOURCE_DIR}/inc/)

set(SOURCES
${PROJECT_SOURCE_DIR}/main.cpp
${PROJECT_SOURCE_DIR}/Person.cpp
${PROJECT_SOURCE_DIR}/Family.cpp
${PROJECT_SOURCE_DIR}/FamilyTree.cpp)
# ${PROJECT_SOURCE_DIR}/Logger.cpp)

add_custom_target(
    prebuild
    COMMAND wget -nc -P ${PROJECT_SOURCE_DIR}/inc/ https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
)

add_executable(familytree ${SOURCES})
set_property(TARGET familytree PROPERTY CXX_STANDARD 17)
add_dependencies(familytree prebuild)
target_include_directories(familytree PUBLIC ${PROJECT_SOURCE_DIR}/inc)

#add_subdirectory(tests)
