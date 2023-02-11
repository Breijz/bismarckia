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
	INI_EMPTY,	//	0
	INI_SECTION,	//	1
	INI_KEYNAME,	//	2
	INI_KEYVALUE,	//	3
	INI_ENDBRACKET,	//	4
	INI_OPENBRACKET,//	5
	INI_CAPSULE	//	6
};

struct Token {
	IniTypes itKeyNameType;
	IniTypes itKeyValueType;
	std::string szKeyName;
	std::string szKeyValue;
};

struct SectionRange {
	std::string szSection;
	uint uStart;
	uint uEnd;
};

//void szStripTabs(std::string_view szLine);

//void szStripComments(std::string_view szLine);

std::vector<std::string> vecSeperateAtCR(std::string &szLine);

std::string szCleanString(std::string &szLine);

std::vector<Token> mapReadIniFile(std::string szFile);
