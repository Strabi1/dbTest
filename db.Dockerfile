FROM ubuntu:20.04

ENV LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 \
    DEBIAN_FRONTEND=noninteractive

RUN apt update && \
    apt install -y --no-install-recommends \
        ca-certificates unzip sudo htop \
        build-essential g++ gcc make cmake \
        git \
        mariadb-server mariadb-client libmariadb-dev \
        python3 python3-pip \
        # libboost-all-dev \
        libcpprest-dev \
        libssl-dev 
RUN apt clean && rm -rf /var/lib/apt/lists/*

# MariaDB indítása és inicializálása
RUN service mysql start && \
    mysql -e "CREATE DATABASE food_db;" && \
    mysql -e "CREATE USER 'user'@'%' IDENTIFIED BY 'password';" && \
    mysql -e "GRANT ALL PRIVILEGES ON food_db.* TO 'user'@'%';" && \
    mysql -e "FLUSH PRIVILEGES;"

WORKDIR /media/database
