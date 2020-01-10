cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 11)

set(Boost_INCLUDE_DIR C:/boost/)   #here i had installed the boost files
set(Boost_LIBRARY_DIR C:/boost/stage/lib)
include_directories (include)
include_directories (src)
add_executable(Boost_Echo_Client src/unsubscribeFrame.cpp src/subscribeFrame.cpp src/stompEncoderDecoder.cpp src/sendFrame.cpp src/receiptFrame.cpp src/messageFrame.cpp src/disconnectFrame.cpp src/connectFrame.cpp src/connectedFrame.cpp include/unsubscribeFrame.h include/subscribeFrame.h include/stompEncoderDecoder.h include/sendFrame.h include/receiptFrame.h include/messageFrame.h include/frame.h include/disconnectFrame.h include/connectedFrame.h include/connectedFrame.h src/echoClient.cpp src/connectionHandler.cpp include/connectionHandler.h src/frame.cpp)

target_link_libraries(Boost_Echo_Client wsock32 ws2_32)
find_package(Boost REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    target_link_libraries(Boost_Echo_Client
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
            )
endif()