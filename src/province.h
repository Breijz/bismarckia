#ifndef province_H
#define province_H

#include <iostream>
#include <string>
#include <vector>

#include "pop.h"
#include "factory.h"

using namespace std;



class Province {

        public:
        Province() {
                uID = 0;
		szName = "Unknown";
                szOwner = "Unowned";
                szController = "Unowned";
                szGood = "Sand";
                uLiferating = 35;
                uNavalBase = 0;
		uFort = 0;
		bColonial = true;
		szTerrain = "Plains";
                //NOTE: Unused, for now :3      -Breizh
                //szProvince = "NULL";
                //szRegion = "NULL"; see line 77
                //szTerrain = "Snow";
                //iContient = 6;
        }

        public:
                uint uID;
		string szName;
                string szOwner;
                string szController;
                vector<string> Cores;
                string szGood;
                uint uLiferating;
                uint uNavalBase;
		uint uFort;
		bool bColonial;
		string szTerrain;
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

	public:
		void popGrowth() {
			if(uLiferating > 30) {
				int diff = uLiferating - 30;
				float Increase = diff * 0.01;
				Increase = 1 + Increase;
				if(Increase < 1.00) { cout << "fuck\n"; return; }
				for(int i = 0; i < Populations.size(); i++) {
					Populations[i].uSize = Populations[i].uSize * Increase;
				}
			}
		}
};

#endif
