#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

#include "rgo.h"

using namespace std;



class Pop { 

        public:
        Pop() {
                POPID = 0;
                iSize = 0;
                szType = "Farmer";
                szNationality = "Frisian";
                szReligion = "Catholic";
                fMilitancy = 0.00;
                fConsciousness = 0.00;
                //Implement Idealogy
                // Format is NationalistL25.6, LiberalL45.8, etc...
                // L is the delminator between the Idealogy's name and its amount
                vector<string> Idealogy;
                //Implement Political wants (pro military, residency etc
                // Similar to Idealogy
                // JingoismL88.8, Pro-CitizenshipL12.3, etc...
                vector<string> Causes;
                fBasicneeds = 0.00;
                fEverydayneeds = 0.00;
                fLuxuryneeds = 0.00;
        }

        public:
                uint POPID;
                uint iSize;
                string szType;
                string szNationality;
                string szReligion;
                float fMilitancy;
                float fConsciousness;
                //Implement Idealogy
                // Format is NationalistL25.6, LiberalL45.8, etc...
                // L is the delminator between the Idealogy's name and its amount
                vector<string> Idealogy;
                //Implement Political wants (pro military, residency etc
                // Similar to Idealogy
                // JingoismL88.8, Pro-CitizenshipL12.3, etc...
                vector<string> Causes;
                float fBasicneeds;
                float fEverydayneeds;
                float fLuxuryneeds;
                float fLiteracy;

};

class Province {

        public:
        Province() {
                iID = 0;
                szOwner = "Unowned";
                szProvince = "NULL";
                //szRegion = "NULL"; see line 77
                szTerrain = "Snow";
                szGood = "Sand";
                iLiferating = 0;
                //iContient = 6;
        }

        public:
                uint iID;
                string szOwner;
                string szProvince;
                //string szRegion; moved to State Class
                /*
                        szTerrain can be

                        Arctic
                        Coastal Desert
                        Desert
                        Farmlands
                        Forest
                        Hills
                        Jungle
                        Marsh
                        Mountains
                        Plains
                        Steppe
                        Woods
                 */
                string szTerrain;
                string szGood;
                uint iLiferating;
                /*
                 * Europe = 0
                 * North America = 1
                 * South America = 2
                 * Africa = 3
                 * Asia = 4
                 * Oceania = 5
                 */
                //uint iContient;
                vector<Pop> Populations;
                //vector<string> Cores;
};


class State {
        public:
        State() {
                string szRegion = "NULL";
                iContient = 0;
        }

        public:
                vector<Province> ProvincesOfState;
                vector<string> Cores;
                string szRegion;
                uint iContient;
};










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
