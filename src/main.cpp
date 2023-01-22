#include <iostream>
#include <thread>

#include "state.h"
#include "province.h"
#include "pop.h"
#include "rgo.h"
#include "common_market.h"
#include "global_market.h"
#include "goods.h"

using namespace std;



int main(int argc, char* argv[]) {
        cout << "Starting Progams" << endl << endl;;
        
        State Minnesota;
        Minnesota.iContient = 1;

        Province test;

        test.iID = 155;
        test.szOwner = "Minnesota";
        test.szProvince = "Minneapolis";
        test.szTerrain = "Forest";
        test.iLiferating = 35;
        test.szGood = "Timber";

        Minnesota.ProvincesOfState.push_back(test);
        
        test.iID = 156;
        test.szProvince = "Granite Falls";
        test.szGood = "Coal";

        Minnesota.ProvincesOfState.push_back(test);

        test.iID = 157;
        test.szProvince = "Moorhead";
        test.szGood = "Timber";

        Minnesota.ProvincesOfState.push_back(test);
        
        test.iID = 158;
        test.szProvince = "Duluth";
        test.szGood = "Iron";

        Minnesota.ProvincesOfState.push_back(test);
        
        
        for(int i = 0; i < Minnesota.ProvincesOfState.size(); i++) {
                cout << Minnesota.ProvincesOfState[i].iID << endl;
        }
        




        
        
        /*Pop poptest;
        poptest.iSize = 90000;

        test.Populations.push_back(poptest);
        
        poptest.iSize = 3000;
        poptest.szType = "Aristocrat";
        
        test.Populations.push_back(poptest);
        
        
        for(int i = 0; i < test.Populations.size(); i++) {
                cout << test.Populations[i].iSize << endl;
        }*/




        

        return EXIT_SUCCESS;
}
