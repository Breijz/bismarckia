#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Regiment {
	std::string szName;
	std::string szType;	//TODO: replace with index to the type of unit
	uint uHomeProvID;
};

struct Army {
	std::string szName;
	uint uLocation;
	std::vector<Regiment> Regiments;
};

std::vector<Army> giveArmies(std::string &szFile);
