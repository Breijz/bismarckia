#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unistd.h>
#include <cstring>

#include "pop.h"
#include "province.h"
#include "factory.h"
#include "ini.h"
#include "filelisting.h"
#include "state.hpp"

#include "prov.h"

using namespace std;



void sanitiseString(string &szLine) {
	for(uint i = 0; i < szLine.size(); i++) {
		if(szLine[i] == '\n' || szLine[i] == '\r') {
			szLine.erase(i,1);
		}
	}
}

SectionRange srGiveSectionRange(vector<Token> const& TokMap, std::string_view szLine, uint uPos) {
	struct SectionRange RanSetup;
	RanSetup.szSection = szLine;
	
	// Begin reading through the vector
	for(; uPos < TokMap.size(); uPos++) {
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
					//cout << "spListGrandSections breaking...\n";
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



void populateProvinceWPops(vector<string> &PopTypes, vector<Province> &Welt) {
	vector<string> vecFolderList = listingOfFolder("game/history/pops/1836.1.1/", true);
	vector<Token> TokMap;

	// Start reading one of the files
	for(uint uFLPos = 0; uFLPos < vecFolderList.size(); uFLPos++) {
		TokMap = tokeniseIniFile(vecFolderList[uFLPos]);
		// Start reading the current files tokmap
		for(uint uPos = 0; uPos < TokMap.size(); uPos++) {
			// Check if weve reached a section 
			if(TokMap[uPos].itKeyNameType == INI_SECTION && bCheckIfNumber(TokMap[uPos].szKeyName) != false) {
				struct SectionRange RanSetup = srGiveSectionRange(TokMap, TokMap[uPos].szKeyName, 0);
				//cout << RanSetup.szSection << endl;
				uint uProvID = stoi(RanSetup.szSection);
				uint uProvPos = 0;
				bool bFoundID = false;
				for(uint i = 0; i < Welt.size(); i++) {
					if(uProvID == Welt[i].uID) {
						uProvPos = i;
						bFoundID = true;
						break;
					}
				}
				if(bFoundID == false) {
					cout << "populateProvinceWPops() - Didnt find ID! " << uProvID << endl;
				}
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
						Welt[uProvPos].Populations.push_back(PopSetup);
						//ProvSetup.Populations.push_back(PopSetup);
					} else {
						if(bCheckIfNumber(TokMap[uPos].szKeyName) == true) {
							//cout << "breaking...\n";
							break;
						} else {
							cout << TokMap[uPos].szKeyName << " is not PopType!\n";
						}
					}
				}
				//Welt.push_back(ProvSetup);
			}
		}
	}
}


// Inspired from a similar routine in Project Alice ^-^
string removeFSJunk(string &szLine) {
	string szReturn;
	const char* pcLine = szLine.c_str();

	const char* uDirDelim = strrchr(pcLine, '/');
	const char* uFileExtDelim = strrchr(pcLine, '.');
	uint uStrLength = strlen(pcLine);

	for(; uDirDelim < uFileExtDelim; uDirDelim++) {
		szReturn.push_back(*uDirDelim);
	}

	szReturn.erase(0,1);
	return szReturn;
}


void populateProvinceWAttrib(vector<Province>& Welt) {
	vector<string> szFolderList = listingOfFolder("game/history/provinces/", true);

	for(uint uFLV = 0; uFLV < szFolderList.size(); uFLV++) {
		vector<string> szFileList = listingOfFolder(szFolderList[uFLV], true);
		for(uint uFLPos = 0; uFLPos < szFileList.size(); uFLPos++) {
			string szFileName = removeFSJunk(szFileList[uFLPos]);
			uint uProvID = stoi(szFileName.substr(0, szFileName.find_first_of(' ')));
			string szProvName = szFileName.substr((szFileName.find_last_of('-') + 2), szFileName.length());

			Province ProvSetup;	
			ProvSetup.uID = uProvID;
			ProvSetup.szName = szProvName;

			//cout << ProvSetup.szName << endl;


			vector<Token> TokMap = tokeniseIniFile(szFileList[uFLPos]);
			for(uint uTokPos = 0; uTokPos < (TokMap.size() - 0); uTokPos++) {
				if(TokMap[uTokPos].itKeyNameType == INI_KEYNAME) {
					sanitiseString(TokMap[uTokPos].szKeyValue);

					if(TokMap[uTokPos].szKeyName.compare("trade_goods") == 0) {
						ProvSetup.szGood = TokMap[uTokPos].szKeyValue;
						//Welt[Welt.size()].szGood = TokMap[uTokPos].szKeyValue;
					} else
					if(TokMap[uTokPos].szKeyName.compare("life_rating") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							ProvSetup.uLiferating = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("owner") == 0) {
						//cout << "prov.cpp - szOwner: " << TokMap[uTokPos].szKeyValue << endl;
						ProvSetup.szOwner = TokMap[uTokPos].szKeyValue;
						//memcpy(Welt[Welt.size()].szOwner, TokMap[uTokPos].szKeyValue.data(), TokMap[uTokPos].szKeyValue.length());
					} else
					if(TokMap[uTokPos].szKeyName.compare("add_core") == 0) {
						ProvSetup.Cores.push_back(TokMap[uTokPos].szKeyValue);
					} else
					if(TokMap[uTokPos].szKeyName.compare("controller") == 0) {
						ProvSetup.szController = TokMap[uTokPos].szKeyValue;
					} else
					if(TokMap[uTokPos].szKeyName.compare("colony") == 0) {
						if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
							ProvSetup.bColony = true;
						} else {
							ProvSetup.bColony = false;
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("is_slave") == 0) {
						if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
							ProvSetup.bIsSlave = true;
						} else {
							ProvSetup.bIsSlave = false;
						}
						
					} else
					if(TokMap[uTokPos].szKeyName.compare("fort") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							ProvSetup.uFort = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("railroad") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							ProvSetup.uRailroad = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("naval_base") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							ProvSetup.uNavalBase = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("colonial") == 0) {
						if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
							ProvSetup.bColonial = true;
						} else {
							ProvSetup.bColonial = false;
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("terrain") == 0) {
						ProvSetup.szTerrain = TokMap[uTokPos].szKeyValue;
					}
					else {
						if(TokMap[uTokPos].szKeyName.compare("state_building") == 0) {
							cout << "State Building Found in main sequence\n";
						}
						//cout << "Error in " << Welt[uProvPos].uID << " : " << TokMap[uTokPos].szKeyName << " : " << TokMap[uTokPos].szKeyValue << endl;
						//cout << "Types : " << TokMap[uTokPos].itKeyNameType << " : " << TokMap[uTokPos].itKeyValueType << endl;
					}

				} else if(TokMap[uTokPos].itKeyNameType == INI_SECTION) {
					sanitiseString(TokMap[uTokPos].szKeyValue);
					if(regex_match(TokMap[uTokPos].szKeyName, regex("^(?:[0-9]{4}[.][0-9]{1,2}[.][0-9]{1,2}[=][{]$)")) == true) {
						// TODO: Implement historical bookmarks
						for(; uTokPos < TokMap.size(); uTokPos++) {
							uint uOB = 0;
							uint uEB = 0;
							if(TokMap[uTokPos].itKeyNameType == INI_OPENBRACKET || TokMap[uTokPos].itKeyValueType == INI_OPENBRACKET) {
								uOB++;
							}
							if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) {
								uEB++;
							}
							if(uOB == uEB) {
								break;
							}
						}
					} else {
						if(TokMap[uTokPos].szKeyName.compare("state_building") == 0) {
							struct Factory FactSetup;
							for(; uTokPos < TokMap.size(); uTokPos++) {
									if(TokMap[uTokPos].szKeyName.compare("level") == 0) {
										FactSetup.uLevel = stoi(TokMap[uTokPos].szKeyValue);
									}else
									if(TokMap[uTokPos].szKeyName.compare("building") == 0) {
										FactSetup.szBuilding = TokMap[uTokPos].szKeyValue;
									} else
									if(TokMap[uTokPos].szKeyName.compare("upgrade") == 0) {
										if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
											FactSetup.bUpgrade = true;
										} else {
											FactSetup.bUpgrade = false;
										}
									}
								if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { 
									ProvSetup.Factories.push_back(FactSetup);
									break; 
								}
							}
						} else
						if(TokMap[uTokPos].szKeyName.compare("revolt") == 0) {
							struct Revolt RevSetup;
							for(; uTokPos < TokMap.size(); uTokPos++) {
								if(TokMap[uTokPos].szKeyName.compare("type") == 0) {
									RevSetup.szType = TokMap[uTokPos].szKeyValue;
								} else
								if(TokMap[uTokPos].szKeyName.compare("controller") == 0) {
									if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
										RevSetup.bController = true;
									} else {
										RevSetup.bController = false;
									}
								} else {
									cout << "Unknown Variable! " << TokMap[uTokPos].szKeyName << endl;
								}
								if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { 
									ProvSetup.Rebellions.push_back(RevSetup);
									break; 
								}
							}
						}
					}
				}
			}
		Welt.push_back(ProvSetup);
		}
	}
}



/*vector<Province> populateProvinceWAttrib(vector<Province> &Welt) {
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

			vector<Token> TokMap = tokeniseIniFile(szFileList[uFLPos]);
			for(uint uTokPos = 0; uTokPos < TokMap.size(); uTokPos++) {
				if(TokMap[uTokPos].itKeyNameType == INI_KEYNAME) {
					sanitiseString(TokMap[uTokPos].szKeyValue);

					if(TokMap[uTokPos].szKeyName.compare("trade_goods") == 0) {
						Welt[uProvPos].szGood = TokMap[uTokPos].szKeyValue;
					} else
					if(TokMap[uTokPos].szKeyName.compare("life_rating") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							Welt[uProvPos].uLiferating = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("owner") == 0) {
						cout << "prov.cpp - szOwner: " << TokMap[uTokPos].szKeyValue << endl;
						//Welt[uProvPos].szOwner = TokMap[uTokPos].szKeyValue;
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
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							Welt[uProvPos].uFort = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("railroad") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							Welt[uProvPos].uRailroad = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
					} else
					if(TokMap[uTokPos].szKeyName.compare("naval_base") == 0) {
						if(bCheckIfNumber(TokMap[uTokPos].szKeyValue) == true) {
							Welt[uProvPos].uNavalBase = stoi(TokMap[uTokPos].szKeyValue);
						} else {
							cout << "stoi() Error: " << TokMap[uTokPos].szKeyValue << endl;
							sleep(5);
						}
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
						if(TokMap[uTokPos].szKeyName.compare("state_building") == 0) {
							cout << "State Building Found in main sequence\n";
						}
						//cout << "Error in " << Welt[uProvPos].uID << " : " << TokMap[uTokPos].szKeyName << " : " << TokMap[uTokPos].szKeyValue << endl;
						//cout << "Types : " << TokMap[uTokPos].itKeyNameType << " : " << TokMap[uTokPos].itKeyValueType << endl;
					}

				} else if(TokMap[uTokPos].itKeyNameType == INI_SECTION) {
					sanitiseString(TokMap[uTokPos].szKeyValue);
					if(regex_match(TokMap[uTokPos].szKeyName, regex("^(?:[0-9]{4}[.][0-9]{1,2}[.][0-9]{1,2}[=][{]$)")) == true) {
						// TODO: Implement historical bookmarks
						for(; uTokPos < TokMap.size(); uTokPos++) {
							uint uOB = 0;
							uint uEB = 0;
							if(TokMap[uTokPos].itKeyNameType == INI_OPENBRACKET || TokMap[uTokPos].itKeyValueType == INI_OPENBRACKET) {
								uOB++;
							}
							if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) {
								uEB++;
							}
							if(uOB == uEB) {
								break;
							}
						}
					} else {
						if(TokMap[uTokPos].szKeyName.compare("state_building") == 0) {
							struct Factory FactSetup;
							for(; uTokPos < TokMap.size(); uTokPos++) {
									if(TokMap[uTokPos].szKeyName.compare("level") == 0) {
										FactSetup.uLevel = stoi(TokMap[uTokPos].szKeyValue);
									}else
									if(TokMap[uTokPos].szKeyName.compare("building") == 0) {
										FactSetup.szBuilding = TokMap[uTokPos].szKeyValue;
									} else
									if(TokMap[uTokPos].szKeyName.compare("upgrade") == 0) {
										if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
											FactSetup.bUpgrade = true;
										} else {
											FactSetup.bUpgrade = false;
										}
									}
								if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { 
									Welt[uProvPos].Factories.push_back(FactSetup);
									break; 
								}
							}
						} else
						if(TokMap[uTokPos].szKeyName.compare("revolt") == 0) {
							struct Revolt RevSetup;
							for(; uTokPos < TokMap.size(); uTokPos++) {
								if(TokMap[uTokPos].szKeyName.compare("type") == 0) {
									RevSetup.szType = TokMap[uTokPos].szKeyValue;
								} else
								if(TokMap[uTokPos].szKeyName.compare("controller") == 0) {
									if(TokMap[uTokPos].szKeyValue.compare("yes") == 0) {
										RevSetup.bController = true;
									} else {
										RevSetup.bController = false;
									}
								} else {
									cout << "Unknown Variable! " << TokMap[uTokPos].szKeyName << endl;
								}
								if(TokMap[uTokPos].itKeyNameType == INI_ENDBRACKET || TokMap[uTokPos].itKeyValueType == INI_ENDBRACKET) { 
									Welt[uProvPos].Rebellions.push_back(RevSetup);
									break; 
								}
							}
						}
					}
				}
			}
			
		}
	}

	return Welt;
}
*/


bool bIsStrNumber(string szLine) {
	for(uint i = 0; i < szLine.length(); i++) {
		if(isdigit(szLine[i]) == false) {
			return false;
		}
	}
	return true;
}

vector<State> orgIntoState(vector<Province> const& Welt) {
	vector<Token> TokMap = tokeniseIniFile("game/map/region.txt");
	vector<State> Staten;

	for(uint uTokPos = 0; uTokPos < TokMap.size(); uTokPos++) {
		if(TokMap[uTokPos].itKeyNameType == INI_KEYNAME && TokMap[uTokPos].itKeyValueType == INI_CAPSULE) {
			State Staat;
			string szCapsule = TokMap[uTokPos].szKeyValue.substr((TokMap[uTokPos].szKeyValue.find_first_of('{') + 2), (TokMap[uTokPos].szKeyValue.find_first_of('}') - 2));
			vector<string> Temp = vecSeperateAtChar(szCapsule, ' ');
			vector<uint> uStateProvIDs;
			for(uint i = 0; i < Temp.size(); i++) {
				if(Temp[i].empty() == false) {
					uStateProvIDs.push_back(stoi(Temp[i]));
				}
			}
			string szStateID = TokMap[uTokPos].szKeyName.substr((TokMap[uTokPos].szKeyName.find_first_of('_') + 1), TokMap[uTokPos].szKeyName.length());
			if(bIsStrNumber(szStateID) == true) {
				//cout << "\'" << szStateID << "\'" << " is a number!\n";
				Staat.uStateID = stoi(szStateID);

				struct i_StateProvPos sppBundle;

				//cout << "uStateProvIDs Size: " << uStateProvIDs.size() << endl;
				for(uint x = 0; x < uStateProvIDs.size(); x++) {
					//cout << "Line 420: " << uStateProvIDs[x] << endl;
					//sppBundle.uProvID = uStateProvIDs[x];
					//cout << "Welt Size: " << Welt.size() << endl;
					uint uProvPos = 0;
					bool bFoundID = false;
					for(uint i = 0; i < Welt.size(); i++) {
						if(uStateProvIDs[x] == Welt[i].uID) {
							sppBundle.uProvID = Welt[uProvPos].uID;
							uProvPos = i;
							bFoundID = true;
							break;
						} else {
							//cout << Welt[i].uID << " =/= " << uStateProvIDs[x] << endl;
						}
					}
					sppBundle.uProvPos = uProvPos;
					Staat.Provinces.push_back(sppBundle);
					if(bFoundID == false) {
						cout << "Didnt Find ID!\n";
					}
					/*
					for(uint y = 0; y < Welt.size(); y++) {
						if(Welt[y].uID == uStateProvIDs[x]) {
							cout << "Found ID!\n";
							bFoundID = true;
							sppBundle.uProvPos = y;
							Staat.Provinces.push_back(sppBundle);
						} else {
							cout << Welt[y].uID << " =/= " << uStateProvIDs[x] << endl;
						}

					}
					*/
				}
				Staten.push_back(Staat);
			} else {
				cout << "\'" << szStateID << "\'" << " is not a number!\n";
			}
		}
	}
	
	return Staten;
}

