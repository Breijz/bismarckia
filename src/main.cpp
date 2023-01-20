#include <iostream>
#include <thread>
#include <vector>

using namespace std;



class Pop { 

        Pop() {
                iSize = 0;
                szType = "Farmer";
                szNationality = "Frisian";
                szReligion = "Catholic";
                fMilitancy = 0.00;
                fConsciousness = 0.00;
                //Implement Idealogy
                //Implement Political wants (pro military, residency etc
                fBasicneeds = 0.00;
                fEverydayneeds = 0.00;
                fLuxuryneeds = 0.00;
        }

        public:
                uint iSize;
                string szType;
                string szNationality;
                string szReligion;
                float fMilitancy;
                float fConsciousness;
                //Implement Idealogy
                //Implement Political wants (pro military, residency etc
                float fBasicneeds;
                float fEverydayneeds;
                float fLuxuryneeds;
                float fLiteracy;

};

class Province {

        Province() {
                iID = 0;
                szOwner = "Unowned";
                szProvince = "NULL";
                szRegion = "NULL";
                szTerrain = "Snow";
                szGood = "Sand";
                iLiferating = 0;
                iContient = 6;
        }

        public:
                uint iID;
                string szOwner;
                string szProvince;
                string szRegion;
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
                uint iContient;
                vector<Pop> Populations;
                vector<string> Cores;
};



int main(int argc, char* argv[]) {

        cout << "Fucking Hell" << endl;

        return EXIT_SUCCESS;
}
