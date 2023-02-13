#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ini.h"

using namespace std;

struct Farbe {
	unsigned char R;
	unsigned char G;
	unsigned char B;
	// NOTE: uchar is 8 bits whereas uint is 16, differance is that uchar needs to be casted into (uint) to be displayed correctly.
	// Vic2s files only use values from 0-255, so uchar is better, as it only supports values from 0-256, hence uint would be overkill
	// as itd allow for values from 0-65536, which is never seen in the files, or expected to be supported afaik. -Breizh
	//uint R;
	//uint G;
	//uint B;
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
