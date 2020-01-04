cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

add_executable(Boost_Echo_Client src/connectionHandler.cpp include/connectionHandler.h src/echoClient.cpp)