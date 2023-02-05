CPP=g++


compile:
	${CPP} src/main.cpp\
		src/ini.cpp\
		src/filelisting.cpp -o bmserver

