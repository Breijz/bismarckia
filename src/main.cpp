#include <iostream>

#include "ini.h"
#include "province.h"
#include "prov.h"
#include "pop.h"
#include "filelisting.h"
#include "factory.h"

using namespace std;

int main() {
	vector<Token> vecToken = mapReadIniFile("game/common/goods.txt");

	vector<Province> Welt = populateProvinceWPops();
	
	for(uint i = 0; i < vecToken.size(); i++) {
		if(vecToken[i].itKeyNameType == 2) {
			cout << vecToken[i].szKeyName << "| = |" << vecToken[i].szKeyValue << endl;
		}
	}


	return 0;
}
