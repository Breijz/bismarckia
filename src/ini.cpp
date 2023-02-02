#include "ini.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "factory.h"
#include "pop.h"
#include "province.h"
#include "state.h"
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
        if(szLine[i] != '\t' && szLine[i] != ' ' && szLine[i] != '\r') {
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
			if(szLine[i] != '\r' && szLine[i] != '\n') {
				szFix.push_back(szLine[i]);
			} else if(szLine[i] == '\r' && szLine[i+1] == '\n') {
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

/*vector<Token> readIniFile(string File) {
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
                        if(Key.szKeyName[0] == '{' || Key.szKeyValue[0] == '{') {
                                //Token_Map.insert({"INI_OPENBRACKET", "{"});
                                //cout << "INI_OPENBRACKET: " << Key.szKeyName << endl;
                                t_Setup.Type = "INI_OPENBRACKET";
                                t_Setup.Value = "{";
                                Token_Map.push_back(t_Setup);
                        } else
                        if(Key.szKeyValue.empty() != true) {
                        	t_Setup.Type = "INI_KEYVALUE";
                        	t_Setup.Value = Key.szKeyValue;
                                Token_Map.push_back(t_Setup);
                       } else
                        if(Key.szKeyName[0] == '}') {
                                //Token_Map.insert({"INI_ENDBRACKET","}"});
                                //cout << "INI_END_BRACKET: " << Key.szKeyName << endl;
                                t_Setup.Type = "INI_ENDBRACKET";
                                t_Setup.Value = "}";
                                Token_Map.push_back(t_Setup);
                        } 
                        if(Key.szKeyName.empty() != true && Key.szKeyValue[0] != '}') {
                                //Token_Map.insert({"INI_KEYNAME", Key.szKeyName});
                                //cout << "INI_KEYNAME: " << Key.szKeyName << endl;
                                t_Setup.Type = "INI_KEYNAME";
                                t_Setup.Value = Key.szKeyName;
                                Token_Map.push_back(t_Setup);
                        }



                }
        }




        return Token_Map;
}*/

vector<Token> readIniFile(string File) {
	ifstream Readfile;
	vector<Token> Token_Map;

	Readfile.open(File);
	string szLine;
	Token TokenSetup;
	KeyResult Key;
	size_t pos;
	
	while(getline(Readfile, szLine)) {
		szLine = stripTabs(szLine);
		if(szLine.empty() == false && szLine[0] != '#') {
			//From https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
			while((pos = szLine.find("=")) != string::npos) {
				Key.szKeyName = szLine.substr(0, pos);
				szLine.erase(0, (pos + 1));
			}
			Key.szKeyValue = szLine;

			//cout << Key.szKeyName << " : " << Key.szKeyValue << endl;
			
			
			

			// szKeyName is never a { or } so we dont need to worry about it ^-^ 
			if(Key.szKeyName.empty() == false) {
				TokenSetup.Type = "INI_KEYNAME";
				TokenSetup.Value = Key.szKeyName;
				Token_Map.push_back(TokenSetup);
			} /*else {
				cout << "[Error] src/ini.cpp: szKeyName Empty! " << Key.szKeyName << " : " << Key.szKeyValue << " aus " << File << endl;
			}*/

			
			if(Key.szKeyValue.empty() == false && Key.szKeyValue[0] != '{' && Key.szKeyValue[0] != '}') {
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
	Readfile.close();
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
		cout << Listing[uFLInt] << endl;
		uint uEndBracket = 0;
		uint uOpenBracket = 0;
		vector<Token> Token_Map = readIniFile(Listing[uFLInt]);
		vector<int> ProvPositions;
		// Begin Looping through TokenMap 
		for(int i = 0; i < Token_Map.size(); i++) {
			if(Token_Map[i].Type.compare("INI_KEYNAME") == 0 && isNumber(Token_Map[i].Value) == true) {
				//cout << "I is : " << i << endl;
				//Province ProvSetup;
				//ProvSetup.uID = stoi(Token_Map[i].Value);
				//cout << ProvSetup.uID << endl;
				ProvPositions.push_back(i);
			} 
		}
		
		/*
		cout << "size: " << ProvPositions.size() << endl;
		for(int i = 0 ; i < Token_Map.size(); i++) {
			cout << Token_Map[i].Type << " : " << Token_Map[i].Value << endl;
		}*/

		for(int i = 0; i < ProvPositions.size(); i++) {
			// ProvPositions incl. the location of each location of the provinces.
			Province ProvSetup;
			Pop PopSetup;
	
			//cout << "FFSFS Prov is... " << ProvPositions[i] << endl;
			uint uZ = ProvPositions[i];
			//cout << "uZ is ... " << uZ << endl;
			ProvSetup.uID = stoi(Token_Map[uZ].Value);
			cout << "Province ID: " << ProvSetup.uID << endl;


			// Start reading the pops of the Province 
			for(int z = (1 + uZ);z < Token_Map.size(); z++) {
				if(Token_Map[z].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
				if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
				
				if(isKeyNamePop(Token_Map[z].Value) == true) {
					PopSetup.szType = Token_Map[z].Value;
					//cout << PopSetup.szType << endl;
					// Start reading one of the Pops
					for(z++;;z++) {
						if(Token_Map[z].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
						if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) { 
							uEndBracket++; 
							//cout << "Pushing POP...\n";
							ProvSetup.Populations.push_back(PopSetup);
							break; 
						}
						//cout << Token_Map[z].Value << endl;

						if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
							if(Token_Map[z].Value.compare("culture") == 0) {
								z++;
								PopSetup.szCulture = Token_Map[z].Value;
								//cout << PopSetup.szCulture << endl;
							}
							if(Token_Map[z].Value.compare("religion") == 0) {
								z++;
								PopSetup.szReligion = Token_Map[z].Value;
								//cout << PopSetup.szReligion << endl;
							}
							if(Token_Map[z].Value.compare("size") == 0) {
								z++;
								PopSetup.uSize = stoi(Token_Map[z].Value);
								//cout << PopSetup.uSize << endl;
							}
						}
					}
					if(Token_Map[z+1].Type.compare("INI_ENDBRACKET") == 0) {
						cout << "Pushing Province...\n";
						//ProvWPop.push_back(ProvSetup);
						//uEndBracket = 0;
						//uOpenBracket = 0;
						break;
					} else {
						//cout << "Debug: " << uEndBracket << " : " << uOpenBracket << endl;
						//cout << "Debug: " << Token_Map[z].Value << endl;
						//cout << Token_Map[z+1].Type << " : " << Token_Map[z+1].Value << endl;
					}
				}
			}
			// This is stupid, but required as otherwise Provinces 77 and 265 dont get pushed into ProvWPop
			// Why these? not sure, and it shall remain a mystery i suppose
			ProvWPop.push_back(ProvSetup);
			uEndBracket = 0;
			uOpenBracket = 0;


		}
		
	}
	return ProvWPop;
}



/*vector<Province> populateProvinceWAttrib(vector<Province> ProvFS, char* File) {
	vector<Province> ProvWAtt = ProvFS;
	

	for(int i = 0; i < ProvWAtt.size(); i++) {
		for(int x = 0; x < ProvWAtt[i].Populations.size(); x++) {
			cout << ProvWAtt[i].Populations[x].uSize << endl;
		}
	}


	return ProvWAtt;
}*/


// Some province files (136, 1107, 232, 123, 211, 219, 200, and 116) do not work due to '\r' line terminators...
// Keeping '\r' in the token map causes a seg. fault, Im not quite sure how to fix this at the moment, so I wont
// handle it for now, but it needs to be handled.

vector<Province> populateProvinceWAttrib(vector<Province> ProvWPop, char* File) {
	vector<Province> ProvFS = ProvWPop;
        KeyResult Key;
        vector<Token> Token_Map;
        vector<string> Listing = listingOfFolder(File, false);
        string szFile;

         /* This code isnt expandable and will only work with the files shipped in the original Vic2, (w/o dlc) */


        for(int i = 0; i < Listing.size(); i++) {
                szFile = File + Listing[i];
                Key = seperateKey(Listing[i], '-');
                uint ProvID = stoi(Key.szKeyName);

		bool True = false;
		uint ProvPos = 0;
		for(; ProvPos < ProvFS.size(); ProvPos++) {
			if(ProvID == ProvFS[ProvPos].uID) {
				True = true;
				break;
			}
		}
		if(True == false) {
			cout << "ProvID: " << ProvID << " doesnt exist!\n";
			ProvPos = 0;
		}


		Token_Map = readIniFile(szFile);
		//cout << szFile << endl;
		//cout << "Done!\n";
		//cout << Token_Map.size() << endl;
		for(int z = 0; z < Token_Map.size(); z++) {
			if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
				
				
				if(Token_Map[z].Value.compare("owner") == 0) {
					z++;
					ProvFS[ProvPos].szOwner = Token_Map[z].Value;
				} else
				if(Token_Map[z].Value.compare("controller") == 0) {
					ProvFS[ProvPos].szController = Token_Map[z+1].Value;
				} else
				if(Token_Map[z].Value.compare("add_core") == 0) {
					ProvFS[ProvPos].Cores.push_back(Token_Map[z+1].Value);
				} else
				if(Token_Map[z].Value.compare("life_rating") == 0) {
					ProvFS[ProvPos].uLiferating = stoi(Token_Map[z+1].Value);
				} else
				if(Token_Map[z].Value.compare("colonial") == 0) {
					if(Token_Map[z+1].Value.compare("yes") == 0) {
						ProvFS[ProvPos].bColonial = true;
					} else {
						ProvFS[ProvPos].bColonial = false;
					}
				} else
				if(Token_Map[z].Value.compare("terrain") == 0) {
					ProvFS[ProvPos].szTerrain = Token_Map[z+1].Value;
				} else
				if(Token_Map[z].Value.compare("naval_base") == 0) {
					ProvFS[ProvPos].uNavalBase = stoi(Token_Map[z+1].Value);
				} else
				if(Token_Map[z].Value.compare("fort") == 0) {
					ProvFS[ProvPos].uFort = stoi(Token_Map[z+1].Value);
				} else
				if(Token_Map[z].Value.compare("railroad") == 0) {
					ProvFS[ProvPos].uRailroad = stoi(Token_Map[z+1].Value);
				} else
				if(Token_Map[z].Value.compare("state_building") == 0) {
					Factory FactSetup;
					for(z++; z < Token_Map.size(); z++) {
						if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) { break; }
						
						if(Token_Map[z].Value.compare("level") == 0) {
							FactSetup.uLevel = stoi(Token_Map[z+1].Value);
						}
						if(Token_Map[z].Value.compare("building") == 0) {
							FactSetup.szBuilding= Token_Map[z+1].Value;
						}
						if(Token_Map[z].Value.compare("upgrade") == 0) {
							if(Token_Map[z+1].Value.compare("yes") == 0) {
								FactSetup.bUpgrade = true;
							} else {
								FactSetup.bUpgrade = false;	
							}
						}

					}
					//ProvFS[ProvPos].Factories.push_back(FactSetup);

				} else
				if(Token_Map[z].Value.compare("colony") == 0) {
					if(Token_Map[z+1].Value.compare("yes") == 0) {
						ProvFS[ProvPos].bColony = true;
					} else {
						ProvFS[ProvPos].bColony = false;
					}
				} else
				if(Token_Map[z].Value.compare("is_slave") == 0) {
					if(Token_Map[z+1].Value.compare("yes") == 0) {
						ProvFS[ProvPos].bIsSlave = true;
					} else {
						ProvFS[ProvPos].bIsSlave = false;
					}
				} else
				if(Token_Map[z].Value.compare("revolt") == 0) {
					Revolt RevSetup;
					for(z++; z < Token_Map.size(); z++) {
						if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) { break; }
						
						if(Token_Map[z].Value.compare("type") == 0) {
							RevSetup.szType = Token_Map[z+1].Value;
						}
						if(Token_Map[z].Value.compare("controller") == 0) {
							if(Token_Map[z+1].Value.compare("yes") == 0) {
								RevSetup.bController = true;
							} else {
								RevSetup.bController = false;
							}
						}
					}
					ProvFS[ProvPos].Rebellions.push_back(RevSetup);

				} else
				if(Token_Map[z].Value.compare("trade_goods") == 0) {
					//ProvFS[ProvPos].szGood = "FUCKKCK";
					//cout << "FUCK\n";
					ProvFS[ProvPos].szGood = Token_Map[z+1].Value;
				} else {
					cout << ProvID << ": " <<  "|" << Token_Map[z].Value << " = " << Token_Map[z+1].Value << "|" << endl;
				}
			}
		}
	}

                
        return ProvFS;
}


vector<State> orgIntoState(vector<Province> Welt) {
	vector<Token> Token_Map = readIniFile("game/map/region.txt");
	vector<State> Staten;
	for(int i = 0 ; i < Token_Map.size(); i++) {
		cout << Token_Map[i].Type << " : " <<  Token_Map[i].Value << endl;
	}
	return Staten;
}







 
