project(FeatureProject)

cmake_minimum_required(VERSION 2.8)

# for colored output
if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold  "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
endif()


# iterator over subdirectories
macro(SubDirList result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()



if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
# message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("${Green}Build in Debug mode.${ColourReset}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("${Green}Build in Release mode.${ColourReset}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

message("${Green}CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}${ColourReset}")


set(target log2req.bin)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_DIR}/bin)
set(SRC_DIR ${PROJECT_DIR}/src)
# set(SRC ${SRC_DIR}/*.cpp ${SRC_DIR}/MTSearch_thrift/gen-cpp/*.cpp)

set(INCLUDE ${SRC_DIR}/MTSearch_thrift/gen-cpp)
include_directories(${INCLUDE})

# file(GLOB SRC ${SRC_DIR}/main.cpp 
            # ${SRC_DIR}/LogReq.cpp
            # ${SRC_DIR}/LogParser.cpp
            # ${SRC_DIR}/MTSearch_thrift/gen-cpp/*.cpp)

file(GLOB SRC ${SRC_DIR}/*.cpp ${SRC_DIR}/MTSearch_thrift/gen-cpp/*.cpp)

set(LIBS glog jsoncpp thrift boost_program_options)

add_executable(${target} ${SRC})
target_link_libraries(${target} ${LIBS})

