CPP=g++

all: server client

server:
	${CPP} src/main.cpp\
		src/ini.cpp\
		src/filelisting.cpp -o bmserver

client:
	${CPP} sp/main.cpp -lGLEW -lGL -lglfw -o bmclient
