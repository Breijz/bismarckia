#ifndef ini_H
#define ini_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "pop.h"
#include "province.h"

using namespace std;

typedef struct {
    string szKeyName;
    string szKeyValue;
} KeyResult;

string stripTabs(string szLine);

KeyResult seperateKey(string Key);

bool isKeyNamePop(string szLine);

bool isNumber(string szLine);

vector<Province> giveProvincePops(string File);

#endif