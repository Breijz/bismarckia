#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "pop.h"
#include "province.h"
#include "ini.h"
#include "filelisting.h"



std::vector<Province> populateProvinceWPops();

std::vector<Province> populateProvinceWAttrib(std::vector<Province> ProvWPop, char* File);

std::vector<Province> orgProvIntoContinents(std::vector<Province> Welt);

