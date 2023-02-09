#include "ini.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "factory.h"
#include "pop.h"
#include "province.h"
#include "filelisting.h"


using namespace std;



string stripTabs(string szLine) {
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



string stripComments(string szLine) {
	string szAns;

	for(int i = 0; i < szLine.size(); i++) {
		if(szLine[i] == '#') {
			break;	
		} else {
			szAns.push_back(szLine[i]);
		}
	}

	return szAns;
}



//Inherit from servicd/getKeyValue.cpp
KeyResult seperateKey(string Key, char Delim, bool bKeepSpace) {
    KeyResult SepKey;
    bool Side = false;
    if(bKeepSpace == false) {
   	 for(int i = 0; i < Key.size(); i++) {
   	     if(Key[i] == Delim) {
   	         Side = true;
   	     } else if(Side == false && Key[i] != ' ' /*&& Key[i] != '\r'*/) {
   	         SepKey.szKeyName.push_back(Key[i]);
   	     } else if(Side == true && Key[i] != ' ' /*&& Key[i] != '\r'*/) {
   	         SepKey.szKeyValue.push_back(Key[i]);
   	     }
   	 }
    } else {
	for(int i = 0; i < Key.size(); i++) {
   	     if(Key[i] == Delim) {
   	         Side = true;
   	     } else if(Side == false /*&& Key[i] != '\r'*/) {
   	         SepKey.szKeyName.push_back(Key[i]);
   	     } else if(Side == true /*&& Key[i] != '\r'*/) {
   	         SepKey.szKeyValue.push_back(Key[i]);
   	     }
   	 }
    }
    return SepKey;
}



// This should probably be modified so it can allow for more pops.
bool isKeyNamePop(string szLine) {
    if(szLine.compare("craftsmen") == 0) {
        return true;
    }
    if(szLine.compare("farmers") == 0) {
        return true;
    }
    if(szLine.compare("laborers") == 0) {
        return true;
    }
    if(szLine.compare("slaves") == 0) {
        return true;
    }
    if(szLine.compare("soldiers") == 0) {
        return true;
    }
    if(szLine.compare("artisans") == 0) {
        return true;
    }
    if(szLine.compare("bureaucrats") == 0) {
        return true;
    }
    if(szLine.compare("clergymen") == 0) {
        return true;
    }
    if(szLine.compare("clerks") == 0) {
        return true;
    }
    if(szLine.compare("officers") == 0) {
        return true;
    }
    if(szLine.compare("aristocrats") == 0) {
        return true;
    }
    if(szLine.compare("capitalists") == 0) {
        return true;
    }

    return false;
}



bool isNumber(string szLine) {
    for(int i = 0; i < szLine.length(); i++) {
        if(isdigit(szLine[i]) == 0) { return false; }
    }
    return true;
}



vector<string> seperateAtCR(string szLine, string szDelim) {
	vector<string> sepLines;
	string finLine;
	KeyResult Key;
	size_t pos;

		while((pos = szLine.find(szDelim)) != string::npos) {
			sepLines.push_back(szLine.substr(0, pos));
			szLine.erase(0, (pos + 1));
		}
		sepLines.push_back(szLine);



	return sepLines;
}



// This code is *alot* more generic, its nothing more than a tokeniser
// for the INI style files that Vic2 uses, and it should work for any
// format of the file, this function ought not to be used on its own but
// instead as part of another function...       -Breizh

vector<Token> readIniFile(string File, bool bCheckKeyValue) {
	ifstream Readfile;
	vector<Token> Token_Map;
	vector<string> FileLines;
	vector<string> t_Temp;

	Readfile.open(File);
	string szLine;
	Token TokenSetup;
	KeyResult Key;
	size_t pos;
	
	while(getline(Readfile,szLine)) {
		if(szLine[0] != ' ' && szLine[0] != '#') {
			szLine = stripComments(szLine);
			t_Temp = seperateAtCR(szLine, "\r");
			for(uint i = 0; i < t_Temp.size(); i++) {
				FileLines.push_back(t_Temp[i]);
			}
		}
	}
	Readfile.close();
	
	for(uint uFR = 0; uFR < FileLines.size(); uFR++) {
		szLine = FileLines[uFR];
		szLine = stripTabs(szLine);
		if(szLine.empty() == false && szLine[0] != '#') {
			//From https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
			while((pos = szLine.find("=")) != string::npos) {
				Key.szKeyName = szLine.substr(0, pos);
				szLine.erase(0, (pos + 1));
			}
			Key.szKeyValue = szLine;

			
			
			

			// szKeyName is never a { or } so we dont need to worry about it ^-^ 
			if(Key.szKeyName.empty() == false) {
				TokenSetup.Type = "INI_KEYNAME";
				TokenSetup.Value = Key.szKeyName;
				Token_Map.push_back(TokenSetup);
			} 

			
			if(Key.szKeyValue.empty() == false && Key.szKeyValue[0] != '{' && Key.szKeyValue[0] != '}' && bCheckKeyValue == true) {
				TokenSetup.Type = "INI_KEYVALUE";
				TokenSetup.Value = Key.szKeyValue;
				Token_Map.push_back(TokenSetup);
			} else if(Key.szKeyValue.empty() == false && Key.szKeyValue[0] != '}' && bCheckKeyValue == false) {
				TokenSetup.Type = "INI_KEYVALUE";
				TokenSetup.Value = Key.szKeyValue;
				Token_Map.push_back(TokenSetup);
			}

			// szKeyValue is sometimes { or } so we must handle them first before szKeyValue 
			if(Key.szKeyValue.compare("}") == 0) {
				TokenSetup.Type = "INI_ENDBRACKET";
				TokenSetup.Value = Key.szKeyValue;
				Token_Map.push_back(TokenSetup);
			}
			if(Key.szKeyValue.compare("{") == 0) {
				TokenSetup.Type = "INI_OPENBRACKET";
				TokenSetup.Value = Key.szKeyValue;
				Token_Map.push_back(TokenSetup);
			} 


			Key.szKeyName.erase(0, string::npos);
			Key.szKeyValue.erase(0, string::npos);
		} 
	}
	return Token_Map;
}
