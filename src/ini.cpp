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



/*
 * This code is *alot* more generic, its nothing more than a tokeniser
 * for the INI style files that Vic2 uses, and it should work for any
 * format of the file, this function ought not to be used on its own but
 * instead as part of another function...       -Breizh
 */

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



// This code is being written at 0331, it probably has errors, hopefully less errors than above code.
vector<Province> populateProvinceWPops() {
	vector<Province> ProvWPop;
	vector<string> Listing = listingOfFolder("game/history/pops/1836.1.1/", true);

	for(uint ListPos = 0; ListPos < Listing.size(); ListPos++) {
		uint uEndBracket = 0;
		uint uOpenBracket = 0;
		vector<Token> Token_Map = readIniFile(Listing[ListPos], true);
		//Start Reading through Token_Map
		for(uint TokPos = 0; TokPos < Token_Map.size(); TokPos++) {
			if(isNumber(Token_Map[TokPos].Value) == true) {
				Province ProvSetup;
				ProvSetup.uID = stoi(Token_Map[TokPos].Value);

				//Start Reading through a province
				TokPos = TokPos + 1;
				for(;TokPos < Token_Map.size(); TokPos++) {
					if(Token_Map[TokPos].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
					if(Token_Map[TokPos].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }

					if(isKeyNamePop(Token_Map[TokPos].Value) == true) {
						Pop PopSetup;
						PopSetup.szType = Token_Map[TokPos].Value;
						//Begin reading through Pop
						TokPos = TokPos + 1;
						for(;TokPos < Token_Map.size();TokPos++) {
							if(Token_Map[TokPos].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
							if(Token_Map[TokPos].Type.compare("INI_ENDBRACKET") == 0) { 
								//printf("Pushing Pop...\n"); 
								uEndBracket++; 
								break; 
							}

							if(Token_Map[TokPos].Type.compare("INI_KEYNAME") == 0) {
								if(Token_Map[TokPos].Value.compare("culture") == 0) {
									TokPos++;
									PopSetup.szCulture.swap(Token_Map[TokPos].Value);
								} else
								if(Token_Map[TokPos].Value.compare("religion") == 0) {
									TokPos++;
									PopSetup.szReligion.swap(Token_Map[TokPos].Value);
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
				ProvWPop.push_back(ProvSetup); 
				uEndBracket = 0;
				uOpenBracket = 0;
			}
		}
	}

	return ProvWPop;
}



/*
 * This function takes in a vector of Provinces and adds the attributes defined in /history/province/???/ 
 * to them, to use it populateProvWPops must be used first.
 */
vector<Province> populateProvinceWAttrib(vector<Province> ProvWPop, char* File) {
	vector<Province> ProvFS = ProvWPop;
        KeyResult Key;
        vector<Token> Token_Map;
        vector<string> Listing = listingOfFolder(File, false);
        string szFile;

         /* This code isnt expandable and will only work with the files shipped in the original Vic2, (w/o dlc) */


        for(uint i = 0; i < Listing.size(); i++) {
                szFile = File + Listing[i];
                Key = seperateKey(Listing[i], '-', false);
		string t_szProv = Key.szKeyName.substr((Key.szKeyName.find_last_of("/") + 1), Key.szKeyName.length());

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
			// TODO: We probably want to create the Province if it doesnt exist, as to let one use
			// the functions in whichever order they want
			ProvPos = 0;
		}



		Token_Map = readIniFile(szFile);


		for(uint z = 0; z < Token_Map.size(); z++) {
			if(Token_Map[z].Type.compare("INI_KEYNAME") == 0) {
				if(Token_Map[z].Value.compare("trade_goods") == 0) {
					z++;
					ProvFS[ProvPos].szGood = Token_Map[z].Value;
				} else
				if(Token_Map[z].Value.compare("life_rating") == 0) {
					z++;
					ProvFS[ProvPos].uLiferating = stoi(Token_Map[z].Value);
				} else
				if(Token_Map[z].Value.compare("owner") == 0) {
					z++;
					ProvFS[ProvPos].szOwner = Token_Map[z].Value;
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
