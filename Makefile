
all: server meas

server:
# ================================================
# Server - dockerben kell fordítani
# ================================================
	g++ server.cpp -I/usr/include/mariadb -lmariadb -lpthread -lcpprest -lssl -lcrypto -o server

meas:
# ================================================
# Test - bárhol lehet fordítani
# ================================================
	g++ measure.cpp -I/usr/include/mariadb -lcurl -o measure

clean:
	rm -rf server measure

.PHONY: server meas clean
