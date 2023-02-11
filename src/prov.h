#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "pop.h"
#include "province.h"
#include "ini.h"
#include "filelisting.h"



std::vector<std::string> szGiveListOfPops();

bool bIsStrPop(std::string_view szLine, std::vector<std::string> &PopTypes);

std::vector<Province> populateProvinceWPops(std::vector<std::string> &PopTypes);
