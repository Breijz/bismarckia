#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ini.h"

using namespace std;

struct Farbe {
	char R;
	char G;
	char B;
};

struct Good {
	string szCategory;
	string szName;
	float fCost;
	bool bAvailStart = true;
	bool bTradeable = true;		// These are only used for precious_metal so in theory we could merge them
	bool bMoney = false;		// but we wont for the sake of accuracy
	bool bOverseasPenalty = false;
	Farbe Colour;
};


class Market {
	public:
	Market() {
	}

	public:
		vector<Good> listOfGoods;

};
