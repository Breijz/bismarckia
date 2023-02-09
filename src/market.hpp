#ifndef market_HPP
#define market_HPP

#include <iostream>
#include <string>
#include <vector>

#include "ini.h"

using namespace std;

typedef struct {
	char R;
	char G;
	char B;
} Farbe;

typedef struct {
	string szCategory;
	string szName;
	float fPrice;
	bool bAvailStart = true;
	bool bTradeable = true;		// These are only used for precious_metal so in theory we could merge them
	bool bMoney = false;		// but we wont for the sake of accuracy
	bool bOverseasPenalty = false;
	Farbe Colour;
} Good;


class Market {
	public:
	Market() {
	}

	public:
		vector<Good> listOfGoods;

	private:
		void initalise() {
			vector<Token> Token_Map = readIniFile("game/common/goods.txt", true);

			for(uint TokPos = 0; TokPos < Token_Map.size(); TokPos++) {
				uint uEndBracket = 0;
				uint uOpenBracket = 0;

			}

		}
};

#endif