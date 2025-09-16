
all:
# ================================================
# Server - dockerben kell fordítani
# ================================================
	g++ server.cpp -I/usr/include/mariadb -lmariadb -lpthread -lcpprest -lssl -lcrypto -o server

# ================================================
# Test - bárhol lehet fordítani
# ================================================
	g++ measure.cpp -I/usr/include/mariadb -lcurl -o measure
