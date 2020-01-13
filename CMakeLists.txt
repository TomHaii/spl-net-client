cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client)


set(CMAKE_CXX_STANDARD 11)

add_compile_options("-lboost_system")
link_libraries("-lboost_system -lpthread")
include_directories (include)
include_directories (src)
add_executable(Boost_Echo_Client src/stompEncoderDecoder.cpp include/stompEncoderDecoder.h src/echoClient.cpp src/connectionHandler.cpp include/connectionHandler.h src/frames/Frame.cpp include/frames/Frame.h src/StompProtocol.cpp include/StompProtocol.h src/frames/ConnectFrame.cpp include/frames/ConnectFrame.h src/frames/SubscribeFrame.cpp include/frames/SubscribeFrame.h src/frames/SendFrame.cpp include/frames/SendFrame.h src/Book.cpp include/Book.h src/frames/DisconnectFrame.cpp include/frames/DisconnectFrame.h src/frames/MessageFrame.cpp include/frames/MessageFrame.h src/frames/ConnectedFrame.cpp include/frames/ConnectedFrame.h src/frames/UnsubscribeFrame.cpp include/frames/UnsubscribeFrame.h src/frames/ReceiptFrame.cpp include/frames/ReceiptFrame.h src/Client.cpp include/Client.h include/StompProtocol.h src/KeyboardListener.cpp include/KeyboardListener.h src/ServerListener.cpp include/ServerListener.h src/frames/ErrorFrame.cpp include/frames/ErrorFrame.h)

