#include <iostream>
#include <thread>

#include "state.h"
#include "province.h"
#include "pop.h"
#include "rgo.h"
#include "common_market.h"
#include "global_market.h"
#include "goods.h"
#include "country.h"

// These use the better system of having a header file include a source file
// The rest of the ones above ought to be converted at some point
// aswell as cleaned up         -Breizh
#include "ini.h"
#include "filelisting.h"
#include "factory.h"



using namespace std;



int main(int argc, char* argv[]) {
	vector<Province> Welt = populateProvinceWPops();

	
	cout << "   "<< Welt.size() << endl;
	for(int x = 0; x < Welt.size(); x++) {
		for(int y = 0; y < Welt[x].Populations.size(); y++) {
			cout << Welt[x].uID << " : " << Welt[x].Populations[y].uSize << endl;
		}
	}
	


	return 0;

	/*
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
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/soviet/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/spain/");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/united kingdom");
	Welt = populateProvinceWAttrib(Welt, "game/history/provinces/usa/");

	//orgIntoState(Welt);
	
	for(int i = 0; i < Welt.size(); i++) {
		if(Welt[i].szGood.compare("Sand") == 0) {
			cout << Welt[i].uID << " : " << Welt[i].szGood << endl;
		}
	}

	
	for(int D = 0; D < (365 * (2000-1836)); D++) {
		for(int x = 0; x < Welt.size(); x++) {
			Welt[x].popGrowth();
		}
		cout << "Day: " << D << endl;
	}
	unsigned long int WorldPop = 0; 

       	for(int i = 0; i < Welt.size(); i++) {
		for(int y = 0; y < Welt[i].Populations.size(); y++) {
			WorldPop = WorldPop + Welt[i].Populations[y].uSize;
		}
	}
	cout << "World Population: " << WorldPop << endl;
	*/
        






        
        return EXIT_SUCCESS;
}
