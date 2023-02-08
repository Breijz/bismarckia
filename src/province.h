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
                uID = 0;			// Province ID, there is no province 0 so we use this as a default
		szName = "NULL";		// Null values for strings since we cant predict what they ought to be
                szOwner = "NULL";
                szController = "NULL";
                szGood = "NULL";

                uLiferating = 0;		// Liferating of the province, this is never negative or a decimal, (base game its 15-50)
                uNavalBase = 0;			// Level of Navalbase, 0 = No Base
		uFort = 0;			// ^^^
		uRailroad = 0;			// ^^^
		bColonial = false;		// Is the Province integrated or not? for us to change this to true we need for bColony to be true prior	
		bColony = false;		// Is the Province *just* colonised
		bIsSlave = false;		// Is the province a slave state? in these states slaves can exist
		szTerrain = "NULL";		// Only used for ~3 provinces, all of which are Islands.

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

};

#endif
