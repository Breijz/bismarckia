CPP=g++
OPTFlags=-o
Input=src/main.cpp
Output=bmserver

compile:
	${CPP} ${Input} ${OPTFlags} ${Output}
