CPP=g++


compile:
	${CPP} src/main.cpp\
		src/ini.cpp\
		src/filelisting.cpp\
		src/prov.cpp -o bmserver

