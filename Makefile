
all:
	g++ server.cpp -I/usr/include/mariadb -lmariadb -lpthread -lcpprest -lssl -lcrypto -o server
#	g++ server2.cpp -I/usr/include/mariadb -lmariadb -lpthread -lcpprest -lssl -lcrypto -o server2