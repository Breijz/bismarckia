#include <iostream>
#include <thread>

#include "province.h"
#include "pop.h"

// These use the better system of having a header file include a source file
// The rest of the ones above ought to be converted at some point
// aswell as cleaned up         -Breizh
#include "ini.h"
#include "filelisting.h"
#include "factory.h"

// These HPP files are permenat
#include "market.hpp"



using namespace std;



int main(int argc, char* argv[]) {
	Market GM;
	cout << GM.listOfGoods.size() << endl;
	for(int i = 0; i < GM.listOfGoods.size(); i++) {
		cout << "GM.szName = " << GM.listOfGoods[i].szName << endl;
	}
	return 0;
	//cout << "This contains examples/displays of all the data we have collected through functions" << '\n';
	//cout << "Strike any key to continue ^-^" << '\n';
	//cin.get();
	vector<Province> Welt;
	Welt = populateProvinceWPops();

	cout << "Information read through populateProvinceWPops()\n";
	cout << "Strike any key to continue\n";
	cin.get();

	for(uint y = 0; y < Welt.size(); y++) {
		cout << Welt[y].uID << ":\n";
		for(uint x = 0; x < Welt[y].Populations.size(); x++) {
			//cout << "\t szType Size: " << Welt[y].Populations[x].szType.length() << "\n";
			cout << "\t szType: " << Welt[y].Populations[x].szType << "\n";
			cout << "\t szCulture: " << Welt[y].Populations[x].szCulture << "\n";
			cout << "\t szReligion: " << Welt[y].Populations[x].szReligion << "\n";
			cout << "\t uSize: " << Welt[y].Populations[x].uSize << "\n";
		}
	}
	


	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/africa/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/asia/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/australia/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/austria/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/balkan/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/canada/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/carribean/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/central asia/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/china/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/france/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/germany/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/india/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/indonesia/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/italy/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/japan/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/low countries/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/mexico/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/pacific island/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/portugal/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/scandinavia/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/south america/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/soviet/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/spain/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/united kingdom/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/usa/");


	cout << "\n\n\n";
	cout << "This is to display data collected through populateProvinceWAttrib\n";
	cout << "It is worth noting that, to my knowledge, most provinces do not define a terrain\n";
	cout << "Likewise by default strings are defined as NULL\n";
	cout << "Also when couting booleans, theyll appear as 1 for true and 0 for false\n";
	cout << "Strike any key to continue...\n";
	cin.get();

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

	
	//orgIntoState(Welt);
	
	
	for(int i = 0; i < Welt.size(); i++) {
		if(Welt[i].szGood.compare("Sand") == 0) {
			cout << Welt[i].uID << " : " << Welt[i].szGood << endl;
		}
	}

	return 0;
	/*

	
	for(int D = 0; D < (365 * (2000-1836)); D++) {
		for(int x = 0; x < Welt.size(); x++) {
			Welt[x].popGrowth();
		}
		cout << "Day: " << D << endl;
	}*/
	unsigned long int WorldPop = 0; 

       	for(int i = 0; i < Welt.size(); i++) {
		for(int y = 0; y < Welt[i].Populations.size(); y++) {
			WorldPop = WorldPop + Welt[i].Populations[y].uSize;
		}
	}
	cout << "World Population: " << WorldPop << endl;
        






        
        return EXIT_SUCCESS;
}
