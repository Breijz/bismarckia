#ifndef prov_H
#define prov_H

#include <iostream>
#include <vector>
#include <string>

#include "pop.h"
#include "province.h"
#include "ini.h"
#include "filelisting.h"

using namespace std;

vector<Province> populateProvinceWPops();

vector<Province> populateProvinceWAttrib(vector<Province> ProvWPop, char* File);

vector<Province> orgProvIntoContinents(vector<Province> Welt);

#endif
