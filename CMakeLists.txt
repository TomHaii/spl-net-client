cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

set(Boost_INCLUDE_DIR C:/boost/)   #here i had installed the boost files
set(Boost_LIBRARY_DIR C:/boost/stage/lib)
include_directories (include)
include_directories (src)
add_executable(Boost_Echo_Client src/echoClient.cpp src/connectionHandler.cpp include/connectionHandler.h include/frame.h src/connectedFrame.cpp include/connectedFrame.h src/connectFrame.cpp include/connectFrame.h src/disconnectFrame.cpp include/disconnectFrame.h src/messageFrame.cpp include/messageFrame.h src/receiptFrame.cpp include/receiptFrame.h src/sendFrame.cpp include/sendFrame.h src/subscribeFrame.cpp include/subscribeFrame.h src/unsubscribeFrame.cpp include/unsubscribeFrame.h)

target_link_libraries(Boost_Echo_Client wsock32 ws2_32)
find_package(Boost REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(Boost_Echo_Client
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
            )
endif()