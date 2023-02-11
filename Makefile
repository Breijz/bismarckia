CPP=g++


#compile:
#	${CPP} src/main.cpp\
#		src/ini.cpp\
#		src/filelisting.cpp\
#		src/prov.cpp -o bmserver

compile:
	${CPP} src/main.cpp\
		src/ini.cpp\
		src/prov.cpp\
		src/filelisting.cpp\
		-std=c++17 -o bmserver -g

