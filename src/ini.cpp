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


vector<string> seperateAtCR(string szLine) {
	vector<string> sepLines;
	string finLine;
	KeyResult Key;
	size_t pos;

		while((pos = szLine.find("\r")) != string::npos) {
			sepLines.push_back(szLine.substr(0, pos));
			szLine.erase(0, (pos + 1));
		}
		sepLines.push_back(szLine);



	return sepLines;
}


/*
 * This code is *alot* more generic, its nothing more than a tokeniser
 * for the INI style files that Vic2 uses, and it should work for any
 * format of the file, this function ought not to be used on its own but
 * instead as part of another function...       -Breizh
 */

vector<Token> readIniFile(string File) {
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
			t_Temp = seperateAtCR(szLine);
			for(uint i = 0; i < t_Temp.size(); i++) {
				FileLines.push_back(t_Temp[i]);
			}

			/*
			Key = seperateKey(szLine, '\r');
			if(Key.szKeyValue[0] == '\n') {
				FileLines.push_back(szLine);
			} else if(Key.szKeyValue[0] != '\n' ) {
				if(Key.szKeyName.empty() != true) {
					//cout << "DEBUG szKeyName: " << Key.szKeyName << endl;
					FileLines.push_back(Key.szKeyName);
				}
				if(Key.szKeyValue.empty() != true) {
					//cout << "DEBUG szKeyValue: " << Key.szKeyValue << endl;
					FileLines.push_back(Key.szKeyValue);
				}
			}
			*/
		}
	}
	Readfile.close();
	
	//while(getline(Readfile, szLine)) {
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
	return Token_Map;
}

/*
 * This function populates a given vector of provinces with their pops
 * from history/1836.1.1/pops
 */



/*void populateProvinceWPops(vector<Province> *ProvWPop) {
	vector<string> Listing = listingOfFolder("game/history/pops/1836.1.1/", true);
	//vector<Province> ProvWPop;


	for(uint uFLInt = 0; uFLInt < Listing.size(); uFLInt++) {
		//cout << Listing[uFLInt] << endl;
		uint uEndBracket = 0;
		uint uOpenBracket = 0;
		vector<Token> Token_Map = readIniFile(Listing[uFLInt]);
		vector<int> ProvPositions;
		// Begin Looping through TokenMap 
		for(int i = 0; i < Token_Map.size(); i++) {
			if(Token_Map[i].Type.compare("INI_KEYNAME") == 0 && isNumber(Token_Map[i].Value) == true) {
				ProvPositions.push_back(i);
			} 
		}
		

		//Use the Province Positions inside of Token Map
		for(int i = 0; i < ProvPositions.size(); i++) {
			Province ProvSetup;
			// ProvPositions incl. the location of each location of the provinces in the Token Map
	
			uint uZ = ProvPositions[i];
			ProvSetup.uID = stoi(Token_Map[uZ].Value);
			cout << "ID: " << ProvSetup.uID << endl;


			// Start reading the pops of the Province 
			for(int z = (1 + uZ);z < Token_Map.size(); z++) {
				if(Token_Map[z].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
				if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
				
				if(isKeyNamePop(Token_Map[z].Value) == true) {
					Pop PopSetup;
					PopSetup.szType.resize(Token_Map[z].Value.size());
					PopSetup.szType = Token_Map[z].Value;
					//cout << "\t" << PopSetup.szType << endl;
					// Start reading one of the Pops
					for(z++;;z++) {
						if(Token_Map[z].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
						if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) { 
							uEndBracket++; 
							//cout << "Pushing POP...\n";
							//ProvSetup.Populations.push_back(PopSetup);
							break; 
						}
						//cout << Token_Map[z].Value << endl;

						if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
							if(Token_Map[z].Value.compare("culture") == 0) {
								z++;
								PopSetup.szCulture = Token_Map[z].Value;
								//cout << "Culture Token Map Size: " << Token_Map[z].Value.size() << endl;
							} else
							if(Token_Map[z].Value.compare("religion") == 0) {
								z++;
								PopSetup.szReligion = Token_Map[z].Value;
							} else
							if(Token_Map[z].Value.compare("size") == 0) {
								z++;
								PopSetup.uSize = stoi(Token_Map[z].Value);
							}
						}
					}
					ProvSetup.Populations.push_back(PopSetup);
					PopSetup.szCulture.erase(0, string::npos);
					PopSetup.szReligion.erase(0, string::npos);
					PopSetup.uSize = 0;
					if(Token_Map[z+1].Type.compare("INI_ENDBRACKET") == 0) {
						//cout << "Pushing Province...\n";
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
			ProvWPop->push_back(ProvSetup);
			uEndBracket = 0;
			uOpenBracket = 0;


		}
		
	}
	return;
}*/

// This code is being written at 0331, it probably has errors, hopefully less errors than above code.
void populateProvinceWPops(vector<Province> *ProvWPop) {
	vector<string> Listing = listingOfFolder("game/history/pops/1836.1.1/", true);

	for(uint ListPos = 0; ListPos < Listing.size(); ListPos++) {
		uint uEndBracket = 0;
		uint uOpenBracket = 0;
		vector<Token> Token_Map = readIniFile(Listing[ListPos]);
		//Start Reading through Token_Map
		for(uint TokPos = 0; TokPos < Token_Map.size(); TokPos++) {
			if(isNumber(Token_Map[TokPos].Value) == true) {
				Province ProvSetup;
				ProvSetup.uID = stoi(Token_Map[TokPos].Value);
				//cout << "ProvID: " << ProvSetup.uID << endl;
				//Start Reading through a province
				//cout << "Note: " << Token_Map[TokPos+1].Value << endl;
				TokPos = TokPos + 1;
				for(;TokPos < Token_Map.size(); TokPos++) {
					if(Token_Map[TokPos].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
					if(Token_Map[TokPos].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }
					//cout << uOpenBracket << " : " << uEndBracket << endl;

					if(isKeyNamePop(Token_Map[TokPos].Value) == true) {
						Pop PopSetup;
						PopSetup.szType = Token_Map[TokPos].Value;
						//Begin reading through Pop
						//cout << "Before: " << Token_Map[TokPos+1].Value << endl;
						TokPos = TokPos + 1;
						for(;TokPos < Token_Map.size();TokPos++) {
							if(Token_Map[TokPos].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
							if(Token_Map[TokPos].Type.compare("INI_ENDBRACKET") == 0) { 
								//printf("Pushing Pop...\n"); 
								uEndBracket++; 
								break; 
							}
							//cout << "INNER: " << uOpenBracket << " : " << uEndBracket << endl;

							if(Token_Map[TokPos].Type.compare("INI_KEYNAME") == 0) {
								if(Token_Map[TokPos].Value.compare("culture") == 0) {
									TokPos++;
									PopSetup.szCulture.swap(Token_Map[TokPos].Value);
									//PopSetup.szCulture = Token_Map[TokPos].Value;
								} else
								if(Token_Map[TokPos].Value.compare("religion") == 0) {
									TokPos++;
									PopSetup.szReligion.swap(Token_Map[TokPos].Value);
									//PopSetup.szReligion = Token_Map[TokPos].Value;
								} else
								if(Token_Map[TokPos].Value.compare("size") == 0) {
									TokPos++;
									PopSetup.uSize = stoi(Token_Map[TokPos].Value);
								} else
								if(Token_Map[TokPos].Value.compare("militancy") == 0) {
									TokPos++;
									PopSetup.fMilitancy = stof(Token_Map[TokPos].Value);
								} else
								if(Token_Map[TokPos].Value.compare("rebel_type") == 0) {
									TokPos++;
									PopSetup.szRebelType = Token_Map[TokPos].Value;
								}
								else {
									cout << "UNKNOWN! " << Token_Map[TokPos].Value << endl;
								}
							}
						}
						ProvSetup.Populations.push_back(PopSetup); 
					}
					if(uOpenBracket == uEndBracket) { 
						//printf("Pushing Prov...\n"); 
						break; 
					}
				}
				ProvWPop->push_back(ProvSetup); 
				uEndBracket = 0;
				uOpenBracket = 0;
			}
		}
	}

	return;
}



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


        for(uint i = 0; i < Listing.size(); i++) {
                szFile = File + Listing[i];
                Key = seperateKey(Listing[i], '-');
		string t_szProv = Key.szKeyName.substr((Key.szKeyName.find_last_of("/") + 1), Key.szKeyName.length());
		//cout << "Debug: " << t_szProv << endl;
                uint ProvID = stoi(t_szProv);

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


		//cout << "File: " << szFile << endl;
		Token_Map = readIniFile(szFile);
		//cout << szFile << endl;
		//cout << "Done!\n";
		//cout << Token_Map.size() << endl;
		for(uint z = 0; z < Token_Map.size(); z++) {
			if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
				if(Token_Map[z].Value.compare("trade_goods") == 0) {
					z++;
					ProvFS[ProvPos].szGood = Token_Map[z].Value;
					//cout << PopSetup.szCulture << endl;
				} else
				if(Token_Map[z].Value.compare("life_rating") == 0) {
					z++;
					ProvFS[ProvPos].uLiferating = stoi(Token_Map[z].Value);
					//cout << PopSetup.szReligion << endl;
				} else
				if(Token_Map[z].Value.compare("owner") == 0) {
					z++;
					ProvFS[ProvPos].szOwner = Token_Map[z].Value;
					//cout << PopSetup.uSize << endl;
				} else
				if(Token_Map[z].Value.compare("add_core") == 0) {
					z++;
					ProvFS[ProvPos].Cores.push_back(Token_Map[z].Value);
				} else
				if(Token_Map[z].Value.compare("controller") == 0) {
					z++;
					ProvFS[ProvPos].szController = Token_Map[z].Value;
				} else
				if(Token_Map[z].Value.compare("colony") == 0) {
					z++;
					if(Token_Map[z].Value.compare("yes") == 0) {
						ProvFS[ProvPos].bColony = true;
					} else {
						ProvFS[ProvPos].bColony = false;
					}
				} else
				if(Token_Map[z].Value.compare("is_slave") == 0) {
					z++;
					if(Token_Map[z].Value.compare("yes") == 0) {
						ProvFS[ProvPos].bIsSlave = true;
					} else {
						ProvFS[ProvPos].bIsSlave = false;
					}
					
				} else
				if(Token_Map[z].Value.compare("fort") == 0) {
					z++;
					ProvFS[ProvPos].uFort = stoi(Token_Map[z].Value);
				} else
				if(Token_Map[z].Value.compare("railroad") == 0) {
					z++;
					ProvFS[ProvPos].uRailroad = stoi(Token_Map[z].Value);
				} else
				if(Token_Map[z].Value.compare("naval_base") == 0) {
					z++;
					ProvFS[ProvPos].uNavalBase = stoi(Token_Map[z].Value);
				} else
				if(Token_Map[z].Value.compare("colonial") == 0) {
					z++;
					if(Token_Map[z].Value.compare("yes") == 0) {
						ProvFS[ProvPos].bColonial = true;
					} else {
						ProvFS[ProvPos].bColonial = false;
					}
				} else
				if(Token_Map[z].Value.compare("terrain") == 0) {
					z++;
					ProvFS[ProvPos].szTerrain = Token_Map[z].Value;
				} else
				if(Token_Map[z].Value.compare("state_building") == 0) {
					Factory FactSetup;
					for(;z < Token_Map.size(); z++) {
						if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) {
							break;
						} 
						if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
							if(Token_Map[z].Value.compare("level") == 0) {
								z++;
								FactSetup.uLevel = stoi(Token_Map[z].Value);
							} else
							if(Token_Map[z].Value.compare("building") == 0) {
								z++;
								FactSetup.szBuilding = Token_Map[z].Value;
							} else
							if(Token_Map[z].Value.compare("upgrade") == 0) {
								z++;
								if(Token_Map[z].Value.compare("yes") == 0) {
									FactSetup.bUpgrade = true;
								} else {
									FactSetup.bUpgrade = false;
								}
							}
							else {
								// TODO: This code (may) not be fully functional, here
								// when cout debug is on itll report "state_building"
								//cout << "Error! " << Token_Map[z].Value << " : " << Token_Map[z+1].Value << endl;
							}
						}
					}
					ProvFS[ProvPos].Factories.push_back(FactSetup);
				} else
				if(Token_Map[z].Value.compare("revolt") == 0) {
					Revolt RevSetup;
					for(;z < Token_Map.size(); z++) {
						if(Token_Map[z].Type.compare("INI_ENDBRACKET") == 0) {
							break;
						}
						if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
							if(Token_Map[z].Value.compare("type") == 0) {
								z++;
								RevSetup.szType = Token_Map[z].Value;
							} else
							if(Token_Map[z].Value.compare("controller") == 0) {
								z++;
								if(Token_Map[z].Value.compare("yes") == 0) {
									RevSetup.bController = true;
								} else {
									RevSetup.bController = false;
								}
							}
						} else {
							// TODO: This has the same issue as state_building
							//cout << "Error! " << Token_Map[z].Value << " : " << Token_Map[z+1].Value << endl;
						}
					}
					ProvFS[ProvPos].Rebellions.push_back(RevSetup);
				}
				else {
					cout << "Error in " << ProvFS[ProvPos].uID << " : " << Token_Map[z].Value << " : " << Token_Map[z+1].Value << endl;
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







 
