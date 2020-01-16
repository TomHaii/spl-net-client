CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

	# All Targets
all: StompClient

# Tool invocations
StompClient: bin/StompClient.o bin/connectionHandler.o bin/stompEncoderDecoder.o bin/StompProtocol.o bin/ServerListener.o bin/KeyboardListener.o bin/Client.o bin/Book.o bin/UnsubscribeFrame.o bin/SubscribeFrame.o bin/SendFrame.o bin/ReceiptFrame.o bin/MessageFrame.o bin/Frame.o bin/ErrorFrame.o bin/DisconnectFrame.o bin/ConnectedFrame.o bin/ConnectFrame.o
	@echo 'Building target: Stomp Client'
	@echo 'Invoking: C++ Linker'
	g++ -pthread -o bin/StompBookClubClient bin/StompClient.o bin/connectionHandler.o bin/stompEncoderDecoder.o bin/StompProtocol.o bin/ServerListener.o bin/KeyboardListener.o bin/Client.o bin/Book.o bin/UnsubscribeFrame.o bin/SubscribeFrame.o bin/SendFrame.o bin/ReceiptFrame.o bin/MessageFrame.o bin/Frame.o bin/ErrorFrame.o bin/DisconnectFrame.o bin/ConnectedFrame.o bin/ConnectFrame.o $(LDFLAGS)
	@echo 'Finished building target: StompClient'
	@echo ' '

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/StompClient.o: src/StompClient.cpp
	g++ $(CFLAGS) -o bin/StompClient.o src/StompClient.cpp

bin/stompEncoderDecoder.o: src/stompEncoderDecoder.cpp
	g++ $(CFLAGS) -o bin/stompEncoderDecoder.o src/stompEncoderDecoder.cpp

bin/StompProtocol.o: src/StompProtocol.cpp
	g++ $(CFLAGS) -o bin/StompProtocol.o src/StompProtocol.cpp

bin/ServerListener.o: src/ServerListener.cpp
	g++ $(CFLAGS) -o bin/ServerListener.o src/ServerListener.cpp

bin/KeyboardListener.o: src/KeyboardListener.cpp
	g++ $(CFLAGS) -o bin/KeyboardListener.o src/KeyboardListener.cpp

bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

bin/Book.o: src/Book.cpp
	g++ $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/Frame.o: src/frames/Frame.cpp
	g++ $(CFLAGS) -o bin/Frame.o src/frames/Frame.cpp

bin/UnsubscribeFrame.o: src/frames/UnsubscribeFrame.cpp
	g++ $(CFLAGS) -o bin/UnsubscribeFrame.o src/frames/UnsubscribeFrame.cpp

bin/SubscribeFrame.o: src/frames/SubscribeFrame.cpp
	g++ $(CFLAGS) -o bin/SubscribeFrame.o src/frames/SubscribeFrame.cpp

bin/SendFrame.o: src/frames/SendFrame.cpp
	g++ $(CFLAGS) -o bin/SendFrame.o src/frames/SendFrame.cpp

bin/ReceiptFrame.o: src/frames/ReceiptFrame.cpp
	g++ $(CFLAGS) -o bin/ReceiptFrame.o src/frames/ReceiptFrame.cpp

bin/MessageFrame.o: src/frames/MessageFrame.cpp
	g++ $(CFLAGS) -o bin/MessageFrame.o src/frames/MessageFrame.cpp

bin/ErrorFrame.o: src/frames/ErrorFrame.cpp
	g++ $(CFLAGS) -o bin/ErrorFrame.o src/frames/ErrorFrame.cpp

bin/DisconnectFrame.o: src/frames/DisconnectFrame.cpp
	g++ $(CFLAGS) -o bin/DisconnectFrame.o src/frames/DisconnectFrame.cpp

bin/ConnectFrame.o: src/frames/ConnectFrame.cpp
	g++ $(CFLAGS) -o bin/ConnectFrame.o src/frames/ConnectFrame.cpp

bin/ConnectedFrame.o: src/frames/ConnectedFrame.cpp
	g++ $(CFLAGS) -o bin/ConnectedFrame.o src/frames/ConnectedFrame.cpp


.PHONY: clean
clean:
	rm -f bin/*
