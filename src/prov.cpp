#include <iostream>
#include <string>
#include <vector>

#include "pop.h"
#include "province.h"
#include "factory.h"
#include "ini.h"
#include "filelisting.h"

#include "prov.h"

using namespace std;



/*
uint findProvID(vector<Province> &Welt, uint ProvID) {
	for(uint Pos = 0; Pos < Welt.size(); Pos++) {
		if(Welt[Pos].uID == ProvID) {
			return Pos;
		}
	}
	return 0;
}

// This code is being written at 0331, it probably has errors, hopefully less errors than above code.
vector<Province> populateProvinceWPops() {
	vector<Province> ProvWPop;
	vector<string> Listing = listingOfFolder("game/history/pops/1836.1.1/", true);

	for(uint ListPos = 0; ListPos < Listing.size(); ListPos++) {
		uint uEndBracket = 0;
		uint uOpenBracket = 0;
		vector<Token> Token_Map = mapReadIniFile(Listing[ListPos]);
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



// This function takes in a vector of Provinces and adds the attributes defined in /history/province/???/ 
// to them, to use it populateProvWPops must be used first.
vector<Province> populateProvinceWAttrib(vector<Province> ProvWPop, char* File) {
	vector<Province> ProvFS = ProvWPop;
        KeyResult Key;
        vector<Token> Token_Map;
        vector<string> Listing = listingOfFolder(File, false);
        string szFile;

         // This code isnt expandable and will only work with the files shipped in the original Vic2, (w/o dlc) 


        for(uint i = 0; i < Listing.size(); i++) {
                szFile = File + Listing[i];
                //Key = seperateKey(Listing[i], '-', false);
		string szKeyname = Listing[i].substr(0, Listing[i].find_first_of("-"));
		string szKeyValue = Listing[i].substr(Listing[i].find_first_of("-"), Listing[i].length());

		string t_szProv = szKeyName.substr((szKeyName.find_last_of("/") + 1), szKeyName.length());

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



		Token_Map = mapReadIniFile(szFile);


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
					struct Revolt RevSetup;
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



vector<Province> orgProvIntoContinent(vector<Province> Welt) {
	vector<Province> ProvFS = Welt;

	vector<Token> Token_Map = mapReadIniFile("game/map/continent.txt");

	// Begin reading through Token_Map
	for(uint TokPos = 0; TokPos < Token_Map.size(); TokPos++) {
		// Check if were reading a continent
		if(Token_Map[TokPos].Type.compare("INI_KEYNAME") == 0) {
			string szFileContinent = Token_Map[TokPos].Value;
			uint uEndBracket = 0;
			uint uOpenBracket = 0;
			//Begin reading through the continent
			for(TokPos = TokPos + 1; TokPos < Token_Map.size(); TokPos++) {
				if(Token_Map[TokPos].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
				if(Token_Map[TokPos].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; }

				// Check if weve hit the Provinces stuff
				if(Token_Map[TokPos].Value.compare("provinces") == 0) {
					for(uint TokPos = 0; TokPos < Token_Map.size(); TokPos++) {
						if(Token_Map[TokPos].Type.compare("INI_OPENBRACKET") == 0) { uOpenBracket++; }
						// Since we dont have any subsections in provinces we can just escape through the endbracket
						if(Token_Map[TokPos].Type.compare("INI_ENDBRACKET") == 0) { uEndBracket++; break; }

						//everything should be a number here now? but we'll check just in case
						if(isNumber(Token_Map[TokPos].Value) == false) { 
							cout << Token_Map[TokPos].Value << " is not a number!\n";
						} else {
							uint ProvPos = findProvID(Welt, stoi(Token_Map[TokPos].Value));
							ProvFS[ProvPos].szContinent = szFileContinent;
						}
					}
				} else {
					cout << "Unknown: " << Token_Map[TokPos].Value << endl;
				}

				if(uEndBracket == uOpenBracket) {
					break;
				}
			}
		}
	}


	return ProvFS;
}
*/



























