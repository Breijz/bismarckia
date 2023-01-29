#ifdef factory_H
#define factory_H

#include <iostream>
#include <string>

using namespace std;

class Factory {
	public:
	Factory() {
		uLevel = 0;
		szBuilding = "NULL";
		bUpgrade = false;
	}

	public:
		uint uLevel;
		string szBuilding;
		bool bUpgrade;
};

#endif
