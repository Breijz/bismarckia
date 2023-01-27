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
        vector<Province> Welt;
        vector<Province> Temp;
        vector<string> Listing = listingOfFolder("game/history/pops/1836.1.1/");
        cout << Listing[0] << endl;
        for(int i = 0; i < Listing.size(); i++) {
                Listing[i] = "game/history/pops/1836.1.1/" + Listing[i];
        }

        for(int i = 0; i < Listing.size(); i++) {
                Temp = populateProvinceWPops(Listing[i]);
                cout << Temp.size() << " " << Listing[i] << endl;
                for(int y = 0; y < Temp.size(); y++) {
                        Welt.push_back(Temp[y]);
                }
        }
       
        






        
        return EXIT_SUCCESS;
}
