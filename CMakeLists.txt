cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(PathVariableManager)

add_executable(PathVariableManager main.cpp Readme.md)

# boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.58.0 COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(PathVariableManager ${Boost_LIBRARIES})