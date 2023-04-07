#include <iostream>
#include <string>

#include "army.h"
#include "ini.h"
#include "prov.h"

using namespace std;

vector<Army> giveArmies(string &szFile) {
	vector<Army> Armies;
	vector<Token> TokMap = tokeniseIniFile(szFile);

	for(uint uTokPos = 0; uTokPos < TokMap.size(); uTokPos++) {
		if(/*TokMap[uTokPos].itKeyNameType == INI_SECTION &&*/ TokMap[uTokPos].szKeyName.compare("army") == 0) {
			cout << TokMap[uTokPos].itKeyNameType << endl;
		}
	}
	

	return Armies;
}
