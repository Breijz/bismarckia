#include "ini.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;



/*enum IniTypes {
	INI_KEYNAME,
	INI_KEYVALUE,
	INI_ENDBRACKET,
	INI_OPENBRACKET,
	INI_CAPSULE		// This is for when keyname = { 0 0 0 }, like for RGB values or for the map/region.txt file -breizh
};*/



/*string szStripTabs(string &szLine) {
	return szLine.substr((1 + szLine.find_last_of("\t")), szLine.length());
}*/



// TODO: this needs to be improved upon.
string szStripTabs(string szLine) {
    string Ans;
	for(int i = 0; i < szLine.size(); i++) {
	    if(szLine[i] != '\t' && szLine[i] != ' ' && szLine[i] != '\r') {
	        Ans.push_back(szLine[i]);
	    } else if(szLine[i] == ' ') {
		    if(isdigit(szLine[i-1]) == true && isdigit(szLine[i+1]) == true) {
			    Ans.push_back(',');
		    }
	    }
	}
    
    return Ans;
}



string szStripComments(string &szLine) {
	uint uPos = szLine.find_first_of("#");
	if(uPos != string::npos) {
		return szLine.substr(0, (uPos - 1));
	} else {
		return szLine;
	}
}



string szStripSpace(string &szLine) {
	string Ans;
	for(uint uPos = 0; uPos < szLine.length(); uPos++) {
		if(szLine[uPos] != ' ' && szLine[uPos] != '\t') {
			Ans.push_back(szLine[uPos]);
		}
	}
	return Ans;
}



multimap<string, IniTypes> mapReadIniFile(string szFile) {
	multimap<string, IniTypes> mapToken;
	vector<string> szFileLines;
	string szLine;
	ifstream Readfile;

	Readfile.open(szFile);

	while(getline(Readfile, szLine)) {
		szLine = szStripSpace(szLine);
		szLine = szStripTabs(szLine);
		if(szLine[0] != '#' && szLine.empty() == false) {
			szLine = szStripComments(szLine);
			szFileLines.push_back(szLine);
		}
	}
	Readfile.close();
	
	for(uint uVecPos = 0; uVecPos < szFileLines.size(); uVecPos++) {
		uint uDelimPos = szFileLines[uVecPos].find("=");	
		//cout << "File: " << szFileLines[uVecPos] << endl;
		string szKeyName = szFileLines[uVecPos].substr(0, uDelimPos);
		string szKeyValue = szFileLines[uVecPos].substr((uDelimPos + 1), szFileLines[uVecPos].length());
		cout << "szKeyName: "<< szKeyName << endl;
		cout << "szKeyValue: " << szKeyValue << endl;


		/*
		if(uDelimPos == string::npos || uDelimPos > szFileLines[uVecPos].length()) {
			if(szFileLines[uVecPos][0] == '{') {
				mapToken.insert(pair<IniTypes, string>(INI_OPENBRACKET, "{"));
				cout << "test\n";
			} else if(szFileLines[uVecPos][0] == '}') {
				mapToken.insert(pair<IniTypes, string>(INI_ENDBRACKET, "}"));
			} else {
				//cout << "Debug: |" << szFileLines[uVecPos] << endl;
			}
		} else if(uDelimPos != string::npos) {
			mapToken.insert(pair<IniTypes, string>(INI_KEYNAME, szFileLines[uVecPos].substr(0, uDelimPos)));
			if(szFileLines[uVecPos].find("{", (uDelimPos + 1)) != string::npos && szFileLines[uVecPos].find("}", (uDelimPos + 1)) == string::npos) {
				mapToken.insert(pair<IniTypes, string>(INI_OPENBRACKET, "{"));
			} else if(szFileLines[uVecPos].find("{", (uDelimPos + 1)) != string::npos && szFileLines[uVecPos].find("}", (uDelimPos + 1)) != string::npos) {
				mapToken.insert(pair<IniTypes, string>(INI_CAPSULE, szFileLines[uVecPos].substr((szFileLines[uVecPos].find(" ", uDelimPos) + 1), szFileLines[uVecPos].length())));
			} else if(szFileLines[uVecPos].find("{", (uDelimPos + 1)) == string::npos && szFileLines[uVecPos].find("}", (uDelimPos + 1)) == string::npos) {
				mapToken.insert(pair<IniTypes, string>(INI_KEYVALUE, szFileLines[uVecPos].substr((szFileLines[uVecPos].find(" ", uDelimPos) + 1), szFileLines[uVecPos].length())));
			}
		}*/

		// szKeyName is never a { or } so we dont need to worry about it ^-^ 
		if(szKeyName.empty() == false && szKeyName.find("}") == string::npos) {
			//TokenSetup.Type = "INI_KEYNAME";
			//TokenSetup.Value = Key.szKeyName;
			//Token_Map.push_back(TokenSetup);
			//mapToken.insert(pair<IniTypes, string>(INI_KEYNAME, szKeyName));
			//mapToken.emplace(INI_KEYNAME, szKeyName);
			mapToken.emplace(szKeyName, INI_KEYNAME);
		} 

		
		if(szKeyValue.empty() == false && szKeyValue[0] != '{' && szKeyValue[0] != '}' ) {
			//TokenSetup.Type = "INI_KEYVALUE";
			//TokenSetup.Value = Key.szKeyValue;
			//Token_Map.push_back(TokenSetup);
			//mapToken.insert(pair<IniTypes, string>(INI_KEYVALUE, szKeyValue));
			mapToken.emplace(szKeyValue, INI_KEYVALUE);
		} /*else if(szKeyValue.empty() == false && szKeyValue[0] == '{' ) {
			//TokenSetup.Type = "INI_KEYVALUE";
			//TokenSetup.Value = Key.szKeyValue;
			//Token_Map.push_back(TokenSetup);
			mapToken.insert(pair<IniTypes, string>(INI_CAPSULE, szKeyValue));
		}*/

		// szKeyValue is sometimes { or } so we must handle them first before szKeyValue 
		if(szKeyValue.compare("}") == 0) {
			//TokenSetup.Type = "INI_ENDBRACKET";
			//TokenSetup.Value = Key.szKeyValue;
			//Token_Map.push_back(TokenSetup);
			//mapToken.insert(pair<IniTypes, string>(INI_ENDBRACKET, "}"));
			mapToken.emplace("}", INI_ENDBRACKET);
		}
		if(szKeyValue.compare("{") == 0) {
			//TokenSetup.Type = "INI_OPENBRACKET";
			//TokenSetup.Value = Key.szKeyValue;
			//Token_Map.push_back(TokenSetup);
			//mapToken.insert(pair<IniTypes, string>(INI_OPENBRACKET, "{"));
			mapToken.emplace("{", INI_OPENBRACKET);
		} 


		szKeyName.erase(0, string::npos);
		szKeyValue.erase(0, string::npos);
	}

	return mapToken;
}





















