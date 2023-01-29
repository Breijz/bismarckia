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



using namespace std;



int main(int argc, char* argv[]) {
        Global_Market GM;
        vector<Province> Welt = populateProvinceWPops();

	/*
	for(int i = 0; i < Welt.size(); i++) {
		for(int y = 0; y < Welt[i].Populations.size(); y++) {
			cout << ":" << Welt[i].Populations[y].uSize << endl;
		}
	}
	*/

	cout << Welt.size() << endl;


	/*for(int i = 0; i < Welt.size(); i++) {
		for(int y = 0; y < Welt[i].Populations.size(); y++) {
			cout << Welt[i].Populations[y].uSize << endl;
		}
	}*/
       
        






        
        return EXIT_SUCCESS;
}
