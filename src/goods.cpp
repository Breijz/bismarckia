#include <iostream>
#include <string>
#include <vector>

#include "market.hpp"
#include "ini.h"
#include "prov.h"

#include "goods.h"

using namespace std;



vector<Good> SetupGoods() {
	vector<Good> Laden;
	vector<Token> TokMap = mapReadIniFile("game/common/goods.txt");
	vector<SectionRange> szSectionList = spListGrandSections(TokMap);
	
	for(uint i = 0; i < szSectionList.size(); i++) {
		struct SectionRange srRange = srGiveSectionRange(TokMap, szSectionList[i].szSection);
		//cout << "Reading " << szSectionList[i].szSection << endl;
		for(uint uTokPos = (srRange.uStart + 1); uTokPos != srRange.uEnd; uTokPos++) {
			if(TokMap[uTokPos].itKeyNameType == INI_SECTION) {
				Good GoodSetup;
				GoodSetup.szCategory = szSectionList[i].szSection;
				GoodSetup.szName = TokMap[uTokPos].szKeyName;
				for(; uTokPos != srRange.uEnd; uTokPos++) {
					if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { break; }

					if(TokMap[uTokPos].itKeyNameType == INI_KEYNAME) {
						if(TokMap[uTokPos].szKeyName.compare("cost") == 0) {
							GoodSetup.fCost = stof(TokMap[uTokPos].szKeyValue);
						} else
						if(TokMap[uTokPos].szKeyName.compare("color") == 0) {
							GoodSetup.Colour.R = stoi(TokMap[uTokPos].szKeyValue.substr(1, (TokMap[uTokPos].szKeyValue.find_first_of(",") - 1)));
							//cout << "|" << TokMap[uTokPos].szKeyValue << "|" << endl;
						} else
						if(TokMap[uTokPos].szKeyName.compare("available_from_start") == 0) {
							if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
								GoodSetup.bAvailStart = true;
							} else {
								GoodSetup.bAvailStart = false;
							}
						} else
						if(TokMap[uTokPos].szKeyName.compare("tradeable") == 0) {
							if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
								GoodSetup.bTradeable = true;
							} else {
								GoodSetup.bTradeable = false;
							}
						} else
						if(TokMap[uTokPos].szKeyName.compare("money") == 0) {
							if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
								GoodSetup.bMoney = true;
							} else {
								GoodSetup.bMoney = false;
							}
						} else
						if(TokMap[uTokPos].szKeyName.compare("overseas_penalty") == 0) {
							if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
								GoodSetup.bOverseasPenalty = true;
							} else {
								GoodSetup.bOverseasPenalty = false;
							}
						}
					}
				}
				Laden.push_back(GoodSetup);
			}
		}
	}

	return Laden;
}
