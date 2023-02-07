#ifndef province_H
#define province_H

#include <iostream>
#include <string>
#include <vector>

#include "pop.h"
#include "factory.h"

using namespace std;



typedef struct {
	string szType;
	bool bController;
} Revolt;


class Province {

        public:
        Province() {
                uID = 0;
		szName = "NULL";
                szOwner = "NULL";
                szController = "NULL";
                szGood = "NULL";
                uLiferating = 0;
                uNavalBase = 0;
		uFort = 0;
		uRailroad = 0;
		bColonial = false;	// I dont believe these are interchangable, but i may be wrong
		bColony = false;		// if they are interchangable, then populateProvinceWAttrib needs to be changed
		bIsSlave = false;
		szTerrain = "NULL";
		szClimate = "NULL";
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
		uint uRailroad;
		bool bColonial;
		bool bColony;
		bool bIsSlave;
		string szTerrain;
		string szClimate;
                vector<Pop> Populations;
		vector<Revolt> Rebellions;
		vector<Factory> Factories;
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
