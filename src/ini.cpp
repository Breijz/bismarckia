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
string szStripTabs(string &szLine) {
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
	if(uPos != string::npos || uPos > szLine.length()) {
		return szLine.substr(0, uPos);
	} else {
		return szLine;
	}
}



string szStripSpace(string &szLine) {
	string Ans;
	for(uint uPos = 0; uPos < szLine.length(); uPos++) {
		if(szLine[uPos] == '{') {
			for(; uPos < szLine.length(); uPos++) {
				Ans.push_back(szLine[uPos]);
				if(szLine[uPos] == '}') {
					uPos++;
					break;
				}
			}
		}
		if(szLine[uPos] != ' ' && szLine[uPos] != '\t') {
			Ans.push_back(szLine[uPos]);
		}
	}
	return Ans;
}




vector<string> vecSeperateAtCR(string &szLine) {
	vector<string> sepLines;
	string finLine;
	size_t pos;

	while((pos = szLine.find("\r")) != string::npos) {
		sepLines.push_back(szLine.substr(0, pos));
		szLine.erase(0, (pos+1));
	}
	sepLines.push_back(szLine);

	return sepLines;
}



vector<Token> mapReadIniFile(string szFile) {
	vector<Token> vecToken;
	vector<string> szFileLines;
	string szLine;
	ifstream Readfile;

	Readfile.open(szFile);

	while(getline(Readfile, szLine)) {
		if(szLine[0] != ' ' && szLine[0] != '#') {
			szLine = szStripTabs(szLine);
			szLine = szStripComments(szLine);
			vector<string> Temp = vecSeperateAtCR(szLine);
			for(uint i = 0; i < Temp.size(); i++) {
				szFileLines.push_back(Temp[i]);
			}
		}
	}
	Readfile.close();
	
	for(uint uVecPos = 0; uVecPos < szFileLines.size(); uVecPos++) {
		uint uDelimPos = szFileLines[uVecPos].find("=");	
		//cout << "File: " << szFileLines[uVecPos] << endl;


		/*
		 * Will trigger for these lines
		 * {
		 * ...
		 * }
		 */
		if(uDelimPos == string::npos || uDelimPos > szFileLines[uVecPos].size()) {
			if(szFileLines[uVecPos].find("{") != string::npos) {
				struct Token TokSetup;
				TokSetup.itKeyNameType = INI_OPENBRACKET;
				TokSetup.itKeyValueType = INI_EMPTY;
				TokSetup.szKeyName = "{";
				vecToken.push_back(TokSetup);
			} else if(szFileLines[uVecPos].find("}") != string::npos) {
				struct Token TokSetup;
				TokSetup.itKeyNameType = INI_ENDBRACKET;
				TokSetup.itKeyValueType = INI_EMPTY;
				TokSetup.szKeyName = "}";
				vecToken.push_back(TokSetup);
			} else {
				//cout << "Debug: " << szFileLines[uVecPos] << endl;
			}

		} 
		/* Will trigger for these lines...
		 * Key = {
		 * 	cost = ...
		 * 	bool = yes
		 */
		else {
			string szKeyName = szFileLines[uVecPos].substr(0, uDelimPos);
			string szKeyValue = szFileLines[uVecPos].substr((uDelimPos + 1), szFileLines[uVecPos].length());

			struct Token TokSetup;

			if(szKeyValue.compare("{") == 0) {
				TokSetup.itKeyNameType = INI_SECTION;
				TokSetup.itKeyValueType = INI_OPENBRACKET;
				TokSetup.szKeyName = szKeyName;
				TokSetup.szKeyValue = szKeyValue;
				vecToken.push_back(TokSetup);
			} else {
				TokSetup.itKeyNameType = INI_KEYNAME;
				TokSetup.szKeyName = szKeyName;
				if(szKeyValue.find("{") != string::npos && szKeyValue.find("}") != string::npos) {
					TokSetup.itKeyValueType = INI_CAPSULE;
					TokSetup.szKeyValue = szKeyValue;
				} else {
					TokSetup.itKeyValueType = INI_KEYVALUE;
					TokSetup.szKeyValue = szKeyValue;
				}

				vecToken.push_back(TokSetup);
			}

		}
	}

	return vecToken;
}





















