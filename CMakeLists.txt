cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)
set(BOOST_NO_SYSTEM_PATHS ON)
set(BOOST_USE_MULTITHREADED  ON)
set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK OFF)

set(BOOST_ROOT "C:/boost")
set(BOOST_INCLUDE_DIRS ${BOOST_ROOT})
set(BOOST_LIBRARY_DIRS ${BOOST_ROOT}/stage/lib/)
include_directories (include)
include_directories (src)
include_directories(${BOOST_INCLUDE_DIRS})
LINK_DIRECTORIES(${BOOST_LIBRARY_DIRS})

add_executable(Boost_Echo_Client src/stompEncoderDecoder.cpp include/stompEncoderDecoder.h src/echoClient.cpp src/connectionHandler.cpp include/connectionHandler.h)

target_link_libraries(Boost_Echo_Client wsock32 ws2_32)
find_package(Boost REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(Boost_Echo_Client
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
            )
endif()