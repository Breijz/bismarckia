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



SectionRange srGiveSectionRange(vector<Token> const& TokMap, std::string_view szLine) {
	struct SectionRange RanSetup;
	RanSetup.szSection = szLine;
	
	// Begin reading through the vector
	for(uint uPos = 0; uPos < TokMap.size(); uPos++) {
		if(TokMap[uPos].szKeyName.compare(szLine) == 0 && TokMap[uPos].itKeyNameType == INI_SECTION) {
			RanSetup.uStart = uPos;
			//Begin reading through the Section
			uint uEndBracket = 0;
			uint uOpenBracket = 0;
			for(; uPos < TokMap.size(); uPos++) {
				if(TokMap[uPos].itKeyNameType == INI_OPENBRACKET || TokMap[uPos].itKeyValueType == INI_OPENBRACKET) { uOpenBracket++; }
				if(TokMap[uPos].itKeyNameType == INI_ENDBRACKET || TokMap[uPos].itKeyValueType == INI_ENDBRACKET) { uEndBracket++; }
				
				if(uEndBracket == uOpenBracket) {
					//cout << uEndBracket << " == " << uOpenBracket << endl;
					RanSetup.uEnd = uPos;
					return RanSetup;
				}
			}
		}
	}

	// We shouldnt get here
	RanSetup.uEnd = 0;
	RanSetup.uStart = 0;
	return RanSetup;
}



vector<SectionRange> spListGrandSections(vector<Token> const& TokMap) {
	vector<SectionRange> Locations;

	for(uint uTokPos = 0; uTokPos < TokMap.size(); uTokPos++) {
		if(TokMap[uTokPos].itKeyNameType == INI_SECTION) {
			uint uOpenBracket = 0;
			//if(TokMap[uTokPos].itKeyValueType == INI_OPENBRACKET) { uOpenBracket++; }
			uint uEndBracket = 0;
			struct SectionRange SectSetup;
			SectSetup.szSection = TokMap[uTokPos].szKeyName;
			SectSetup.uStart = uTokPos;
			for(; uTokPos < TokMap.size(); uTokPos++) {
				if(TokMap[uTokPos].itKeyNameType == INI_OPENBRACKET || TokMap[uTokPos].itKeyValueType == INI_OPENBRACKET ) { uOpenBracket++; }
				if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET ) { uEndBracket++; }

				if(uEndBracket == uOpenBracket) {
					cout << "spListGrandSections breaking...\n";
					SectSetup.uEnd = uTokPos;
					Locations.push_back(SectSetup);
					break;
				}
			}

		}
	}


	return Locations;
}



bool bCheckIfNumber(std::string_view szLine) {
	for(uint i = 0; i < szLine.length(); i++) {
		if(isdigit(szLine[i]) == true) {
			return true;
		}
	}
	return false;
}



vector<string> szGiveListOfPops() {
	vector<string> vecFileList = listingOfFolder("game/poptypes/", false);

	for(uint i = 0; i < vecFileList.size(); i++) {
		vecFileList[i] = vecFileList[i].substr(0, vecFileList[i].find_first_of("."));
	}

	return vecFileList;
}



bool bIsStrPop(std::string_view szLine, vector<string> &PopTypes) {
	for(uint uPos = 0; uPos < PopTypes.size(); uPos++) {
		if(PopTypes[uPos].compare(szLine) == 0) {
			return true;
		}
	}
	return false;
}



vector<Province> populateProvinceWPops(vector<string> &PopTypes) {
	vector<Province> Welt;
	vector<string> vecFolderList = listingOfFolder("game/history/pops/1836.1.1/", true);
	vector<Token> TokMap;

	// Start reading one of the files
	for(uint uFLPos = 0; uFLPos < vecFolderList.size(); uFLPos++) {
		TokMap = mapReadIniFile(vecFolderList[uFLPos]);
		// Start reading the current files tokmap
		for(uint uPos = 0; uPos < TokMap.size(); uPos++) {
			// Check if weve reached a section 
			if(TokMap[uPos].itKeyNameType == INI_SECTION) {
				struct SectionRange RanSetup = srGiveSectionRange(TokMap, TokMap[uPos].szKeyName);
				Province ProvSetup;
				ProvSetup.uID = stoi(RanSetup.szSection);
				// start reading through section
				for(uPos++; uPos < RanSetup.uEnd; uPos++) {
					if(bIsStrPop(TokMap[uPos].szKeyName, PopTypes) == true) {
						Pop PopSetup;
						PopSetup.szType = TokMap[uPos].szKeyName;
						// Start reading through Pop
						for(; uPos < RanSetup.uEnd; uPos++) {
							if(TokMap[uPos].itKeyNameType == INI_ENDBRACKET || TokMap[uPos].itKeyValueType == INI_ENDBRACKET) {
								//cout << "Huzzah!\n";
								break;
							}

							if(TokMap[uPos].itKeyNameType == INI_KEYNAME) {
								if(TokMap[uPos].szKeyName.compare("culture") == 0) {
									PopSetup.szCulture = TokMap[uPos].szKeyValue;				// TODO: Change this to a position marker in a vector of cultures, storing a string each time is awful
								} else
								if(TokMap[uPos].szKeyName.compare("religion") == 0) {
									PopSetup.szReligion = TokMap[uPos].szKeyValue;				// TODO: Change this to a position marker in a vector of Religions, storing a string each time is awful
								} else
								if(TokMap[uPos].szKeyName.compare("size") == 0) {
									PopSetup.uSize = stoi(TokMap[uPos].szKeyValue);
								} else
								if(TokMap[uPos].szKeyName.compare("militancy") == 0) {
									PopSetup.fMilitancy = stof(TokMap[uPos].szKeyValue);
								} else
								if(TokMap[uPos].szKeyName.compare("rebel_type") == 0) {
									PopSetup.szRebelType = TokMap[uPos].szKeyValue;
								}
								else {
									cout << "Unknown Variable in " << RanSetup.szSection << " : " << TokMap[uPos].szKeyName << endl;
								}
							}
						}
						ProvSetup.Populations.push_back(PopSetup);
					} else {
						if(bCheckIfNumber(TokMap[uPos].szKeyName) == true) {
							//cout << "breaking...\n";
							break;
						} else {
							cout << TokMap[uPos].szKeyName << " is not PopType!\n";
						}
					}
				}
				Welt.push_back(ProvSetup);
			}
		}
	}

	return Welt;
}



vector<Province> populateProvinceWAttrib(vector<Province> &Welt) {
	vector<string> szFolderList = listingOfFolder("game/history/provinces/", true);

	for(uint uFLV = 0; uFLV < szFolderList.size(); uFLV++) {
		vector<string> szFileList = listingOfFolder(szFolderList[uFLV], true);
		for(uint uFLPos = 0; uFLPos < szFileList.size(); uFLPos++) {
			string szFileName = szFileList[uFLPos].substr((szFileList[uFLPos].find_last_of("/") + 1), (1 - szFileList[uFLPos].find_last_of(".")));
			uint uProvID = stoi(szFileName.substr(0, (szFileName.find_last_of("-") - 1)));
			string szProvName = szFileName.substr(szFileName.find_first_of("-") + 2, szFileName.length());		// TODO: For some reason having szFileName.find_first/last_of(".") here doesnt work?
			szProvName = szProvName.substr(0, szProvName.find_first_of("."));					// So we must do this for... reasons... -breizh
			
			uint uProvPos = 0;
			bool bFoundProv = false;
			for(uint i = 0; i < Welt.size(); i++) {
				if(uProvID == Welt[i].uID) {
					uProvPos = i;
					bFoundProv = true;
				}
			}
			if(bFoundProv == false) {
				cout << uProvID << " Not Found!\n";
			}

			vector<Token> TokMap = mapReadIniFile(szFileList[uFLPos]);
			for(uint uTokPos = 0; uTokPos < TokMap.size(); uTokPos++) {
				if(TokMap[uTokPos].itKeyNameType == INI_KEYNAME) {

					if(TokMap[uTokPos].szKeyName.compare("trade_goods") == 0) {
						Welt[uProvPos].szGood = TokMap[uTokPos].szKeyValue;
					} else
					if(TokMap[uTokPos].szKeyName.compare("life_rating") == 0) {
						Welt[uProvPos].uLiferating = stoi(TokMap[uTokPos].szKeyValue);
					} else
					if(TokMap[uTokPos].szKeyName.compare("owner") == 0) {
						Welt[uProvPos].szOwner = TokMap[uTokPos].szKeyValue;
					} else
					if(TokMap[uTokPos].szKeyName.compare("add_core") == 0) {
						Welt[uProvPos].Cores.push_back(TokMap[uTokPos].szKeyValue);
					} else
					if(TokMap[uTokPos].szKeyName.compare("controller") == 0) {
						Welt[uProvPos].szController = TokMap[uTokPos].szKeyValue;
					} else
					if(TokMap[uTokPos].szKeyName.compare("colony") == 0) {
						if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
							Welt[uProvPos].bColony = true;
						} else {
							Welt[uProvPos].bColony = false;
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("is_slave") == 0) {
						if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
							Welt[uProvPos].bIsSlave = true;
						} else {
							Welt[uProvPos].bIsSlave = false;
						}
						
					} else
					if(TokMap[uTokPos].szKeyName.compare("fort") == 0) {
						Welt[uProvPos].uFort = stoi(TokMap[uTokPos].szKeyValue);
					} else
					if(TokMap[uTokPos].szKeyName.compare("railroad") == 0) {
						Welt[uProvPos].uRailroad = stoi(TokMap[uTokPos].szKeyValue);
					} else
					if(TokMap[uTokPos].szKeyName.compare("naval_base") == 0) {
						Welt[uProvPos].uNavalBase = stoi(TokMap[uTokPos].szKeyValue);
					} else
					if(TokMap[uTokPos].szKeyName.compare("colonial") == 0) {
						if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
							Welt[uProvPos].bColonial = true;
						} else {
							Welt[uProvPos].bColonial = false;
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("terrain") == 0) {
						Welt[uProvPos].szTerrain = TokMap[uTokPos].szKeyValue;
					}
					else {
						cout << "Error in " << Welt[uProvPos].uID << " : " << TokMap[uTokPos].szKeyName << " : " << TokMap[uTokPos].szKeyValue << endl;
					}

				} else if(TokMap[uTokPos].itKeyNameType == INI_SECTION) {
					if(TokMap[uTokPos].szKeyName.compare("state_building") == 0) {
						for(; uTokPos < TokMap.size(); uTokPos++) {													// TODO : Implement
							if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { break; }
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("revolt") == 0) {
						for(; uTokPos < TokMap.size(); uTokPos++) {													// TODO : Implement
							if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { break; }
						}
					}
				}
			}
			
		}
	}

	return Welt;
}































