#include <iostream>
#include <unistd.h>

#include "ini.h"
#include "province.h"
#include "prov.h"
#include "pop.h"
#include "filelisting.h"
#include "factory.h"
#include "goods.h"

using namespace std;

int main() {

	/*
	string szFile = "game/common/religion.txt";
	vector<Token> TokMap = tokeniseIniFile(szFile);

	//cout << TokMap[0].szKeyName << " : " << TokMap[0].szKeyValue << endl;
	//return 0;

	for(uint i = 0; i < TokMap.size(); i++) {
		cout << TokMap[i].szKeyName << " : " << TokMap[i].szKeyValue << endl;
	}

	return 0;
	*/

	vector<string> PopTypes = szGiveListOfPops();

	vector<Province> Welt = populateProvinceWPops(PopTypes);


	cout << "Orging States...\n";
	sleep(5);
	vector<State> Staten = orgIntoState(Welt);


	
	cout << "Finished Orging States!\n";
	sleep(5);

	for(int i = 0; i < Staten.size(); i++) {
		cout << Staten[i].uStateID << endl;
		for(int x = 0; x < Staten[i].Provinces.size(); x++) {
			cout << "\t" << Staten[i].Provinces[x].uProvID << endl;
		}
	}

	return 0;



	populateProvinceWAttrib(Welt);
	

	for(int y = 0; y < Welt.size(); y++) {
		cout << Welt[y].uID << ":\n";
		cout << "\t" << "Trade Good: " << Welt[y].szGood << endl;
		cout << "\t" << "LifeRating: " << Welt[y].uLiferating << endl;
		cout << "\t" << "Owner: " << Welt[y].szOwner << endl;
		cout << "\t" << "Cores: ";
		for(uint x = 0; x < Welt[y].Cores.size(); x++) {
			cout << Welt[y].Cores[x] << ", ";
		}
		cout << "\n";
		cout << "\t" << "Controller: " << Welt[y].szController << endl;
		cout << "\t" << "Colony: " << Welt[y].bColony << endl;
		cout << "\t" << "Slave State: " << Welt[y].bIsSlave << endl;
		cout << "\t" << "Fort Level: " << Welt[y].uFort << endl;
		cout << "\t" << "Railroad Level: " << Welt[y].uRailroad << endl;
		cout << "\t" << "Naval Base Level: " << Welt[y].uNavalBase << endl;
		cout << "\t" << "Colonial: " << Welt[y].bColonial << endl;
		cout << "\t" << "Terrain: " << Welt[y].szTerrain << endl;
		if(Welt[y].Factories.size() > 0) {
			cout << "\t" << "Factories:\n";
			for(uint x = 0; x < Welt[y].Factories.size(); x++) {
				cout << "\t\t" << "Level: " << Welt[y].Factories[x].uLevel << "\n";
				cout << "\t\t" << "Building: " << Welt[y].Factories[x].szBuilding << "\n";
				cout << "\t\t" << "Upgrade: " << Welt[y].Factories[x].bUpgrade << "\n";
			}
		}
		if(Welt[y].Rebellions.size() > 0) {
			cout << "\t" << "Rebellions:\n";
			for(uint x = 0; x < Welt[y].Rebellions.size(); x++) {
				cout << "\t\t" << "Type: " << Welt[y].Rebellions[x].szType << "\n";
				cout << "\t\t" << "Controller: " << Welt[y].Rebellions[x].bController << "\n";
			}
		}
	}


	cout << '\a';
	return 0;
}
