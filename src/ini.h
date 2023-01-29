#ifndef ini_H
#define ini_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "factory.h"
#include "pop.h"
#include "province.h"

using namespace std;

typedef struct {
    string szKeyName;
    string szKeyValue;
} KeyResult;

typedef struct {
        string Type;
        string Value;
} Token;

string stripTabs(string szLine);

KeyResult seperateKey(string Key, char Delim);

bool isKeyNamePop(string szLine);

bool isNumber(string szLine);

vector<Token> readIniFile(string File);

vector<Province> populateProvinceWPops();

vector<Province> populateProvinceWAttrib(vector<Province> ProvFS, char* Folder);

#endif
