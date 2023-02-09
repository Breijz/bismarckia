#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "factory.h"
#include "pop.h"
#include "province.h"



enum IniTypes {
	INI_KEYNAME,
	INI_KEYVALUE,
	INI_ENDBRACKET,
	INI_OPENBRACKET,
	INI_CAPSULE
};

struct Key {
	IniTypes itType;
	string szKeyName;
	string szKeyValue;
};

void szStripTabs(std::string_view szLine);

void szStripComments(std::string_view szLine);

std::multimap<std::string, IniTypes> mapReadIniFile(std::string szFile);
