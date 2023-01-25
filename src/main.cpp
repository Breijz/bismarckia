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
        vector<Province> ProvincesOfWelt;
        string d_POPS_FILE = "/mnt/breizh/NewSteamLibary/steamapps/common/Victoria\ 2/history/pops/1836.1.1/";

        
        vector<string> Listing;
        Listing = listingOfFolder("/mnt/breizh/NewSteamLibary/steamapps/common/Victoria\ 2/history/pops/1836.1.1/");
        for(int i = 0; i < Listing.size(); i++) {
                Listing[i].insert(0, d_POPS_FILE);                                
        }
        
        vector<Province> temp;
        for(int i = 0; i < Listing.size(); i++) {
                //cout << Listing[i] << endl;
                temp = giveProvincePops(Listing[i]);
                for(int z = 0; i < temp.size(); z++) {
                        ProvincesOfWelt.push_back(temp[z]);
                }
        }
        






        
        return EXIT_SUCCESS;
}
