#ifndef province_H
#define province_H

#include <iostream>
#include <string>
#include <vector>

#include "pop.h"

using namespace std;



class Province {

        public:
        Province() {
                uID = 0;
                szOwner = "Unowned";
                szController = "Unowned";
                szGood = "Sand";
                uLiferating = 35;
                uNavelBase = 0;
                //NOTE: Unused, for now :3      -Breizh
                //szProvince = "NULL";
                //szRegion = "NULL"; see line 77
                //szTerrain = "Snow";
                //iContient = 6;
        }

        public:
                uint uID;
                string szOwner;
                string szController;
                vector<string> Cores;
                string szGood;
                uint uLiferating;
                uint uNavelBase;
                vector<Pop> Populations;
                //string szProvince;
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
                //string szTerrain;
                /*
                 * Europe = 0
                 * North America = 1
                 * South America = 2
                 * Africa = 3
                 * Asia = 4
                 * Oceania = 5
                 */
                //uint iContient;
                //vector<string> Cores;
};

#endif