#!/bin/sh

version=1.1

echo 
echo ===============================================
echo Remove old containers
echo ===============================================
echo 
docker rm db_container
# docker rmi db_docker

echo 
echo ===============================================
echo Build Database container
echo ===============================================
echo 
docker build -f db.Dockerfile -t db_docker:${version} .

echo 
echo ===============================================
echo Start Database container
echo ===============================================
echo 
docker run --name=db_container -it -v .:/media/database db_docker:${version}
