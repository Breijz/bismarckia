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


/*
 * This code is made for the files shipped with Vic2, since Vic2 was made for Windows Systems, and only Windows Systems, they use '\r\n'
 * Since we only use '\n' on *nix and OSX we check for '\r' to tell if its a newline
 * In the future we'll want to allow for both *nix/OSX ('\n') and Windows ('\r\n') types of files to work
 * as currently only the original vic2 files will work (which use the windows style)
 */





string stripTabs(string szLine) {
    string Ans;
    for(int i = 0; i < szLine.size(); i++) {
        if(szLine[i] != '\t' && szLine[i] != ' ' /*&& szLine[i] != '\r'*/) {
            Ans.push_back(szLine[i]);
        }
    }
    
    return Ans;
}




//Inherit from servicd/getKeyValue.cpp
KeyResult seperateKey(string Key, char Delim) {
    KeyResult SepKey;
    bool Side = false;
    for(int i = 0; i < Key.size(); i++) {
        if(Key[i] == Delim) {
            Side = true;
        } else if(Side == false && Key[i] != ' ' /*&& Key[i] != '\r'*/) {
            SepKey.szKeyName.push_back(Key[i]);
        } else if(Side == true && Key[i] != ' ' /*&& Key[i] != '\r'*/) {
            SepKey.szKeyValue.push_back(Key[i]);
        }
    }
    return SepKey;
}

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

vector<string> readWCR(string File) {
	vector<string> Result;
	string szLine;
	string szFix;
	fstream Readfile;
	Readfile.open(File);

	while(getline(Readfile, szLine)) {
		for(int i = 0; i < szLine.size(); i++) {
			if(szLine[i] != '\r' || szLine[i] != '\n') {
				szFix.push_back(szLine[i]);
			} else if(szLine[i] == '\r' || szLine[i] == '\n') {
				Result.push_back(szFix);
				szFix.erase(0, szFix.size());
				break;
			}
		}
		Result.push_back(szFix);
		szFix.erase(0, szFix.size());

	}
	
	

	return Result;
}


/*
 * This code is *alot* more generic, its nothing more than a tokeniser
 * for the INI style files that Vic2 uses, and it should work for any
 * format of the file, this function ought not to be used on its own but
 * instead as part of another function...       -Breizh
 */

vector<Token> readIniFile(string File) {
        ifstream Readfile;
        KeyResult Key;
        Token t_Setup;
        vector<Token> Token_Map;
	string szLine;

	vector<string> LinesOfFile = readWCR(File);


        //while(getline(Readfile, szLine)) {
	for(int i = 0; i < LinesOfFile.size(); i++) {
		szLine = LinesOfFile[i];
                t_Setup.Type.erase(t_Setup.Type.begin(), t_Setup.Type.end());
                t_Setup.Value.erase(t_Setup.Value.begin(), t_Setup.Value.end());
                Key.szKeyName.erase(Key.szKeyName.begin(), Key.szKeyName.end());
                Key.szKeyValue.erase(Key.szKeyValue.begin(), Key.szKeyValue.end());
                szLine = stripTabs(szLine);
                if(szLine[0] != '#') {
                        Key = seperateKey(szLine, '=');
                        if(Key.szKeyName.empty() != true) {
                                //Token_Map.insert({"INI_KEYNAME", Key.szKeyName});
                                //cout << "INI_KEYNAME: " << Key.szKeyName << endl;
                                t_Setup.Type = "INI_KEYNAME";
                                t_Setup.Value = Key.szKeyName;
                                Token_Map.push_back(t_Setup);
                        }
                        if(Key.szKeyName[0] == '{') {
                                //Token_Map.insert({"INI_OPENBRACKET", "{"});
                                //cout << "INI_OPENBRACKET: " << Key.szKeyName << endl;
                                t_Setup.Type = "INI_OPENBRACKET";
                                t_Setup.Value = "{";
                                Token_Map.push_back(t_Setup);
                        } 
                        if(Key.szKeyValue.empty() != true) {
                                if(Key.szKeyValue[0] == '{') {
                                        //Token_Map.insert({"INI_OPENBRACKET", "{" });
                                        //cout << "INI_OPENBRACKET: " << Key.szKeyValue << endl;
                                        t_Setup.Type = "INI_OPENBRACKET";
                                        t_Setup.Value = "{";
                                        Token_Map.push_back(t_Setup);
                                } else {
                                        //Token_Map.insert({"INI_KEYVALUE", Key.szKeyValue});
                                        //cout << "INI_KEYVALUE: " << Key.szKeyValue << endl;
                                        t_Setup.Type = "INI_KEYVALUE";
                                        t_Setup.Value = Key.szKeyValue;
                                        Token_Map.push_back(t_Setup);
                                }
                        }
                        if(Key.szKeyName[0] == '}') {
                                //Token_Map.insert({"INI_ENDBRACKET","}"});
                                //cout << "INI_END_BRACKET: " << Key.szKeyName << endl;
                                t_Setup.Type = "INI_ENDBRACKET";
                                t_Setup.Value = "}";
                                Token_Map.push_back(t_Setup);
                        } 



                }
        }




        return Token_Map;
}

/*
 * This function populates a given vector of provinces with their pops
 * from history/1836.1.1/pops
 */

vector<Province> populateProvinceWPops() {
	vector<string> Listing = listingOfFolder("game/history/pops/1836.1.1/", true);
	vector<Province> ProvWPop;


	for(uint uFLInt = 0; uFLInt < Listing.size(); uFLInt++) {
		uint uEndBracket = 0;
		uint uOpenBracket = 0;
		vector<Token> Token_Map = readIniFile(Listing[uFLInt]);
		/* Begin Looping through TokenMap  */
		for(int i = 0; i < Token_Map.size(); i++) {
			/* Check if were reading a province ID */
			if(Token_Map[i].Type.compare("INI_KEYNAME") == 0 && isNumber(Token_Map[i].Value) == true) {
				Province ProvSetup;
				ProvSetup.uID = stoi(Token_Map[i].Value);
				/* Begin Looping Within Province  */
				for(i++; i < Token_Map.size(); i++) {
					
					if(isKeyNamePop(Token_Map[i].Value) == true) {
						Pop PopSetup;
						PopSetup.szType = Token_Map[i].Value;
						/* Begin Looping Within Pop */
						for(i++; i < Token_Map.size(); i++) {
							if(Token_Map[i].Type.compare("INI_KEYVALUE") != 0 && Token_Map[i].Value.compare("culture") == 0) {
								PopSetup.szCulture = Token_Map[i+1].Value;
							}
							if(Token_Map[i].Type.compare("INI_KEYVALUE") != 0 && Token_Map[i].Value.compare("religion") == 0) {
								PopSetup.szReligion = Token_Map[i+1].Value;
							}
							if(Token_Map[i].Type.compare("INI_KEYVALUE") != 0 && Token_Map[i].Value.compare("size") == 0) {
								PopSetup.uSize = stoi(Token_Map[i+1].Value);
							}
							if(Token_Map[i].Type.compare("INI_KEYVALUE") != 0 && Token_Map[i].Value.compare("militancy") == 0) {
								PopSetup.fMilitancy = stof(Token_Map[i+1].Value);
							}
							if(Token_Map[i].Type.compare("INI_KEYVALUE") != 0 && Token_Map[i].Value.compare("rebel_type") == 0) {
								PopSetup.szRebelType = Token_Map[i+1].Value;
							}
							if(Token_Map[i].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
							if(Token_Map[i].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
							if(uOpenBracket == uEndBracket) { ProvSetup.Populations.push_back(PopSetup); /*cout << "PopBreaking...\n";*/  break; }
						}
					}
					if(Token_Map[i].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
					if(Token_Map[i].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
					if(uOpenBracket == uEndBracket) { ProvWPop.push_back(ProvSetup); /*cout << "ProvBreaking...\n";*/  break; }
				}
			} 
			//if(Token_Map[i].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
			//if(Token_Map[i].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
			//if(uOpenBracket == uEndBracket) { break; }
		}
		
	}
	return ProvWPop;
}



/*vector<Province> populateProvinceWAttrib(char* Folder) {
	vector<string> Listing = listingOfFolder(Folder);
	KeyResult Key;
	string szFile = Folder;
	vector<Province> List;



	for(uint uFLInt = 0; uFLInt < Listing.size(); uFLInt++) {
		uint uEndBracket = 0;
		uint uOpenBracket = 0;

		Province ProvSetup;

		vector<Token> Token_Map = readIniFile(Listing[uFLInt]);
		Key = seperateKey(Listing[uFLInt], '-');
		
		Key.szKeyName.erase(0, szFile.size());
		ProvSetup.uID = stoi(Key.szKeyName);
		Key = seperateKey(Key.szKeyValue, '.');
		ProvSetup.szName = Key.szKeyName;
		
		
		 Begin Looping through TokenMap  
		for(int i = 0; i < Token_Map.size(); i++) {
			if(Token_Map[i].Type.compare("INI_KEYNAME") == 0) {
				if(Token_Map[i].Value.compare("owner") == 0) {
					ProvSetup.szOwner = Token_Map[i+1].Value;
				}
				if(Token_Map[i].Value.compare("controller") == 0) {
					ProvSetup.szController = Token_Map[i+1].Value;
				}
				if(Token_Map[i].Value.compare("add_core") == 0) {
					ProvSetup.Cores.push_back(Token_Map[i+1].Value);
				}
				if(Token_Map[i].Value.compare("trade_goods") == 0) {
					ProvSetup.szGood = Token_Map[i+1].Value;
				}
				if(Token_Map[i].Value.compare("life_rating") == 0) {
					ProvSetup.uLiferating = stoi(Token_Map[i+1].Value);
				}
				if(Token_Map[i].Value.compare("state_building") == 0) {
					cout << "Found State Building! Breaking...\n";
					break;
				}
			}
			
			//if(Token_Map[i].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
			//if(Token_Map[i].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
			//if(uOpenBracket == uEndBracket) { break; }
		}
		List.push_back(ProvSetup);
		 We assign the varibles here since we dont want to have to read through the *entire* vector each time just to change a single variable...  
	}
	return List;
}*/




vector<Province> populateProvinceWAttrib(vector<Province> ProvFS, char* File) {
        ifstream Readfile;
        KeyResult Key;
        vector<Token> Token_Map;
        vector<string> Listing = listingOfFolder(File, false);
        string szFile;

        /*
         * This code isnt expandable and will only work with the files shipped in the original Vic2, (w/o dlc)
         */


        for(int i = 0; i < Listing.size(); i++) {
                szFile = File + Listing[i];
                Key = seperateKey(Listing[i], '-');
                uint ProvID = stoi(Key.szKeyName);

                for(int i = 0; i < ProvFS.size(); i++) {
                        if(ProvFS[i].uID == ProvID) {
                                Key = seperateKey(Key.szKeyValue, '.');
                                ProvFS[i].szName = Key.szKeyName;
                                Token_Map = readIniFile(szFile);
				//cout << szFile << endl;
                                for(int z = 0; z < Token_Map.size(); z++) {
                                        if(Token_Map[z].Type.compare("INI_KEYNAME") == 0);
                                                if(Token_Map[z].Value.compare("owner") == 0) {
							z++;
                                                        ProvFS[i].szOwner = Token_Map[z].Value;
                                                } 
                                                if(Token_Map[z].Value.compare("controller") == 0) {
							z++;
                                                        ProvFS[i].szController = Token_Map[z].Value;
                                                } 
                                                if(Token_Map[z].Value.compare("add_core") == 0) {
							z++;
                                                        ProvFS[i].Cores.push_back(Token_Map[z].Value);
                                                }
                                                if(Token_Map[z].Value.compare("trade_goods") == 0 || Token_Map[z].Value.compare("trade_goods\r") == 0) {
							z++;
                                                        ProvFS[i].szGood = Token_Map[z].Value;
                                                }
                                                if(Token_Map[z].Value.compare("life_rating") == 0) {
							z++;
                                                        ProvFS[i].uLiferating = stoi(Token_Map[z].Value);
                                                }
                                                if(Token_Map[z].Value.compare("state_building") == 0) {
						}
                                                        /*Factory FactSetup;
                                                        for(;z < Token_Map.size(); z++) {
                                                                if(Token_Map[z].Value[0] == '}') {
                                                                        break;
                                                                } else
                                                                if(Token_Map[z].Value.compare("level") == 0) {
									z++;
                                                                        FactSetup.uLevel = stoi(Token_Map[z].Value);
                                                                } else
                                                                if(Token_Map[z].Value.compare("building") == 0) {
									z++;
                                                                        FactSetup.szBuilding = Token_Map[z].Value;
                                                                } else
                                                                if(Token_Map[z].Value.compare("upgrade") == 0 && Token_Map[z+1].Value.compare("yes") == 0) {
                                                                        FactSetup.bUpgrade = true;
                                                                }
                                                                
                                                        }
                                                        ProvFS[i].Factories.push_back(FactSetup);*/
                                                //}

                                }
				//cout << "Done With: " << ProvID << endl;
                        }
                }
        }

        return ProvFS;
}








 
