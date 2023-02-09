#include "ini.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;



enum IniTypes {
	INI_KEYNAME,
	INI_KEYVALUE,
	INI_ENDBRACKET,
	INI_OPENBRACKET,
	INI_CAPSULE		// This is for when keyname = { 0 0 0 }, like for RGB values or for the map/region.txt file -breizh
};



string szStripTabs(string szLine) {
	string szAns;
	for(uint uPos = 0; uPos < szLine.length(); uPos++) {
		if(szLine[uPos] != '\t' && szLine[i] != '\r' && szLine[i] != ' ') {
			szAns.push_back(szLine[uPos]);
		}
	}
	return szAns;
}



string szStripComments(string szLine) {
	uint uPos = szLine.find_first_of("#");
	if(uPos != string::npos) {
		return szLine.substr(0, (uPos - 1));
	}
	return szLine;
}



map<IniTypes, string> map_readIniFile(string szFile) {
	map<IniTypes, string> mapToken;
	vector<string> szFileLines;
	string szLine;
	ifstream Readfile;

	while(getline(Readfile, szLine)) {
		szLine = szStripComments(szStripTabs(szLine));
		szFileLines.push_back(szLine);
	}
	Readfile.close();
	
	for(uint uVecPos = 0; uVecPos < szFileLines.size(); uVecPos++) {
		
	}

	return mapToken;
}
