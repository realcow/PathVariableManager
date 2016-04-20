cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(PathVariableManager)

add_executable(PathVariableManager main.cpp Readme.md)
if(MSVC)
  # make it use static runtime
  #foreach(config_name  ""  DEBUG  RELEASE  MINSIZEREL  RELWITHDEBINFO)
  #  set(var_name "CMAKE_CXX_FLAGS")
  #  if(NOT "${config_name}" STREQUAL "")
  #    set(var_name "${var_name}_${config_name}")
  #  endif()
  #  string(REPLACE "/MD" "/MT" ${var_name} "${${var_name}}")
  #endforeach()
endif()

# boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.48.0 COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(PathVariableManager ${Boost_LIBRARIES})

# yaml-cpp
include(ExternalProject)
ExternalProject_Add(yamlcpp
    PREFIX ${CMAKE_BINARY_DIR}/thirdparty
    GIT_REPOSITORY "D:/git/yaml-cpp-source/.git"
    GIT_TAG release-0.5.3
    CMAKE_ARGS -DMSVC_SHARED_RT=on -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/yamlcpp
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/yamlcpp
    INSTALL_COMMAND cmake --build . --target install --config Release)
add_dependencies(PathVariableManager yamlcpp)
ExternalProject_Get_Property(yamlcpp source_dir install_dir)
include_directories(PathVariableManager ${source_dir}/include)
add_library(yaml-cpp STATIC IMPORTED)
set_property(TARGET yaml-cpp PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libyaml-cppmd.lib) #TODO: library filename is changed depending on toolset
link_directories(PathVariableManager ${binary_dir})
target_link_libraries(PathVariableManager yaml-cpp)