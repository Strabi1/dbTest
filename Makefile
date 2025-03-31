
all:
	g++ server.cpp -I/usr/include/mariadb -lmariadb -lpthread -lcpprest -lssl -lcrypto -o server