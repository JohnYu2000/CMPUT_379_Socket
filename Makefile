CLIENT_EXECUTABLE := client
SERVER_EXECUTABLE := server

CLIENT_MAN_TARGET := client.pdf
SERVER_MAN_TARGET := server.pdf
COMPRESS_TARGET := junye-socket.tar

CLIENT_FILES := client.cpp client.h client_socket_handler.cpp client_socket_handler.h command.cpp command.h client_logger.cpp client_logger.h
MAN_FILES := client.man server.man
SERVER_FILES := server.cpp server.h server_socket_handler.cpp server_socket_handler.h consumer.cpp consumer.h server_logger.cpp server_logger.h
COMMON_FILES := mutex.cpp mutex.h tands.cpp tands.h util.cpp util.h

######################################## CLIENT ########################################
client: client.o client_socket_handler.o command.o client_logger.o tands.o util.o
	g++ -o $(CLIENT_EXECUTABLE) client.o client_socket_handler.o command.o client_logger.o tands.o util.o -pthread

client.o: client.cpp client.h
	g++ -c client.cpp

client_socket_handler.o: client_socket_handler.cpp client_socket_handler.h
	g++ -c client_socket_handler.cpp

command.o: command.cpp command.h
	g++ -c command.cpp

client_logger.o: client_logger.cpp client_logger.h
	g++ -c client_logger.cpp

######################################## SERVER ########################################
server: server.o server_socket_handler.o consumer.o server_logger.o mutex.o tands.o util.o
	g++ -o $(SERVER_EXECUTABLE) server.o server_socket_handler.o consumer.o server_logger.o mutex.o tands.o util.o -pthread

server.o: server.cpp server.h
	g++ -c server.cpp

server_socket_handler.o: server_socket_handler.cpp server_socket_handler.h
	g++ -c server_socket_handler.cpp

consumer.o: consumer.cpp consumer.h
	g++ -c consumer.cpp

server_logger.o: server_logger.cpp server_logger.h
	g++ -c server_logger.cpp

######################################## COMMON ########################################
mutex.o: mutex.cpp mutex.h
	g++ -c mutex.cpp

tands.o: tands.cpp tands.h
	g++ -c tands.cpp

util.o: util.cpp util.h
	g++ -c util.cpp

######################################## MAN ########################################
man: $(CLIENT_MAN_TARGET) $(SERVER_MAN_TARGET)

$(CLIENT_MAN_TARGET):
	groff -Tpdf -man client.man > $(CLIENT_MAN_TARGET)

$(SERVER_MAN_TARGET):
	groff -Tpdf -man server.man > $(SERVER_MAN_TARGET)

######################################## OTHER ########################################
compress:
	tar -cvf $(COMPRESS_TARGET) Makefile README.md $(CLIENT_FILES) $(MAN_FILES) $(SERVER_FILES) $(COMMON_FILES)

clean:
	rm -f $(COMPRESS_TARGET) $(CLIENT_EXECUTABLE) $(SERVER_EXECUTABLE) *.o $(CLIENT_MAN_TARGET) $(SERVER_MAN_TARGET) *.log