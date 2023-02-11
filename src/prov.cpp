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



vector<Province> populateProvinceWAttrib() {
	vector<string> szFolderList = listingOfFolder("game/history/provinces/", true);
}































