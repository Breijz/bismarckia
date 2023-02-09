#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "pop.h"
#include "factory.h"



struct Revolt {
	std::string szType;
	bool bController;
};


class Province {
        public:
                uint uID = 0; 			// Province ID, there is no province 0 so we use this as a default
		std::string szName;
                std::string szOwner;
                std::string szController;
                std::vector<std::string> Cores;
                std::string szGood;
                uint uLiferating = 0;		// Liferating of the province, this is never negative or a decimal, (base game its 15-50)
                uint uNavalBase = 0;		// Level of Navalbase, 0 = No Base
		uint uFort = 0;			// ^^^
		uint uRailroad = 0;		// ^^^
		bool bColonial = false;		// Is the Province integrated or not? for us to change this to true we need for bColony to be true prior	
		bool bColony = false;		// Is the Province *just* colonised
		bool bIsSlave = false;		// Is the province a slave state? in these states slaves can exist
		std::string szTerrain;		// Only used ~3 Provinces, all of which are islands afaik
		std::string szClimate;
		//string szContinent;	
                std::vector<Pop> Populations;
		std::vector<Revolt> Rebellions;
		std::vector<Factory> Factories;

};
