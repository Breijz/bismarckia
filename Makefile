CPP=g++
OPTFlags=-o
Input=src/main.cpp\
      src/ini.cpp\
      src/filelisting.cpp

Output=bmserver

compile:
	${CPP} ${Input} ${OPTFlags} ${Output}
