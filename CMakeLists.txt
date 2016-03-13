cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(PathVariableManager)

add_executable(PathVariableManager main.cpp Readme.md)

# boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.48.0 COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(PathVariableManager ${Boost_LIBRARIES})

# yaml-cpp
include(ExternalProject)
ExternalProject_Add(yamlcpp
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty
    GIT_REPOSITORY "https://github.com/jbeder/yaml-cpp.git"
    GIT_TAG release-0.5.3)
add_dependencies(PathVariableManager "yamlcpp static md") #TODO: hardcoded target name. it varies with build option.
ExternalProject_Get_Property(yamlcpp source_dir)
include_directories(PathVariableManager ${source_dir}/include)