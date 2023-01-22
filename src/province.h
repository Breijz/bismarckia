#ifndef province_H
#define province_H

#include <iostream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;



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

#endif