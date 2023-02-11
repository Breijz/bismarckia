#include <iostream>

#include "ini.h"
#include "province.h"
#include "prov.h"
#include "pop.h"
#include "filelisting.h"
#include "factory.h"

using namespace std;

int main() {
	//vector<Token> vecToken = mapReadIniFile("game/common/goods.txt");
	
	vector<string> PopTypes = szGiveListOfPops();


	vector<Province> Welt = populateProvinceWPops(PopTypes);

	for(uint x = 0; x < Welt.size(); x++) {
		if(Welt[x].uID > 2702) {
			cout << Welt[x].uID << endl;
		}
	}

	return 0;
}
