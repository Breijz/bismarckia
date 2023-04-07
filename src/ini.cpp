#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "ini.h"

using namespace std;



/*string alphaNurString(string &szLine) {
	string szCleaned;
	for(uint i = 0; i < szLine.size(); i++) {
		if(isalpha(szLine[i]) == true) {
			szCleaned.push_back(szLine[i]);
		}
	}
	return szCleaned;
}*/

vector<string> vecSeperateAtChar(string &szLine, char cDelim) {
	vector<string> sepLines;
	string finLine;
	size_t pos;

	while((pos = szLine.find(cDelim)) != string::npos) {
		sepLines.push_back(szLine.substr(0, pos));
		szLine.erase(0, (pos+1));
	}
	sepLines.push_back(szLine);

	return sepLines;
}

string cleanString(string &szLine) {
	bool bCapsule = false;
	string szCleaned;
	//check if were dealing with a capsule
	if(regex_search(szLine, regex("(?:[{].*[}])")) == true) {
		bCapsule = true;	
	}
	for(uint i = 0; i < szLine.size(); i++) {
		if(szLine[i] != ' ' && szLine[i] != '#' && szLine[i] != '\t') {
			if(bCapsule == true && szLine[i] == '{') { 
				for(; i < szLine.size(); i++) {
					szCleaned.push_back(szLine[i]);
				}
				break; 
			}
			if(szLine[i] == '\r' && szLine[i+1] != '\n') {
				szCleaned.push_back('\n');
				i=i+2;
			} else if(szLine[i] == '\r' && szLine[i+1] == '\n') {
				szCleaned.push_back('\n');
				i=i+3;
			} else if(szLine[i] == '\r' && szLine[i+1] == '\r') {
				szCleaned.push_back('\n');
				i=i+3;
			} 
			/*if(szLine[i] == '\r') {
				szCleaned.push_back('\n');
			}*/ else {
				szCleaned.push_back(szLine[i]);
			}
		} else if(szLine[i] == '#') { break; }
	}
	return szCleaned;
}

vector<Token> tokeniseIniFile(string szFile) {
	vector<Token> TokMap;
	vector<string> szFileLines;
	ifstream Readfile;
	string szLine;
	Readfile.open(szFile);

	while(getline(Readfile,szLine)) {
		szLine = cleanString(szLine);
		if(szLine.find_first_of('\n') != szLine.length()) {
			vector<string> Temp = vecSeperateAtChar(szLine, '\n');
			for(uint i = 0; i < Temp.size(); i++) {
				//cout << "Seperated " << i << " : " << Temp[i] << endl;
				//if(Temp[i][Temp[i].size()] == '\n' && Temp[i][Temp[i].size() -1] == '\n') { cout << "test\n"; }
				//szFileLines.push_back(alphaNurString(Temp[i]));
				szFileLines.push_back(Temp[i]);
			}
		} else {
			szFileLines.push_back(szLine);
		}
	}
	Readfile.close();

	for(uint uPos = 0; uPos < szFileLines.size(); uPos++) {
		if(szFileLines[uPos].empty() == false) {
			cout << szFileLines[uPos] << endl;
			uint uDelimPos = szFileLines[uPos].find_first_of('=');
			struct Token TokSetup;
			
			//Section / Group
			if(regex_search(szFileLines[uPos], regex("^(?:.*[=][{][\n])")) == true) { 
				TokSetup.itKeyNameType = INI_SECTION;
				TokSetup.szKeyName = szFileLines[uPos].substr(0,uDelimPos);
				if(string(szFileLines[uPos].substr((uDelimPos + 1), szFileLines[uPos].size())).empty() == false) {
					TokSetup.itKeyValueType = INI_OPENBRACKET;
					TokSetup.szKeyValue = szFileLines[uPos].substr((uDelimPos + 1), szFileLines[uPos].size());
				} else {
					TokMap[uPos].itKeyValueType = INI_EMPTY;
				}
				TokMap.push_back(TokSetup);
			} 
			//Capsule 
			else if(regex_search(szFileLines[uPos], regex("^(?:.*[=][{].*[}])")) == true) {
				TokSetup.itKeyNameType = INI_KEYNAME;
				TokSetup.itKeyValueType = INI_CAPSULE;
				TokSetup.szKeyName = szFileLines[uPos].substr(0,uDelimPos);
				TokSetup.szKeyValue = szFileLines[uPos].substr((uDelimPos + 1), szFileLines[uPos].size());
				TokMap.push_back(TokSetup);
			}
			//Key / Value&Association
			else if(regex_search(szFileLines[uPos], regex("^(?:.*[=].*[^}])")) == true) {
				TokSetup.itKeyNameType = INI_KEYNAME;
				TokSetup.itKeyValueType = INI_KEYVALUE;
				TokSetup.szKeyName = szFileLines[uPos].substr(0,uDelimPos);
				TokSetup.szKeyValue = szFileLines[uPos].substr((uDelimPos + 1), szFileLines[uPos].size());
				TokMap.push_back(TokSetup);
			}
			//Open Bracket / Left Bracket
			else if(regex_search(szFileLines[uPos], regex("^(?:[{])$")) == true) {
				if(TokMap[uPos--].itKeyNameType == INI_SECTION) {
					TokMap[uPos].itKeyValueType == INI_OPENBRACKET;
					TokSetup.szKeyName = szFileLines[uPos].substr(0,uDelimPos);
				} else {
					TokSetup.itKeyNameType = INI_OPENBRACKET;
					TokSetup.itKeyValueType = INI_EMPTY;
					TokSetup.szKeyName = szFileLines[uPos].substr(0,uDelimPos);
				}
				TokMap.push_back(TokSetup);
			}
			//End Bracket / Right Bracket
			else if(regex_search(szFileLines[uPos], regex("^(?:[}]$)")) == true) {
				TokSetup.itKeyNameType = INI_ENDBRACKET;
				TokSetup.itKeyValueType = INI_EMPTY;
				TokSetup.szKeyName = szFileLines[uPos].substr(0,uDelimPos);
				TokMap.push_back(TokSetup);
			}
		}
	}


	return TokMap;
}
