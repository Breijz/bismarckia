#include "ini.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "pop.h"
#include "province.h"


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
        if(szLine[i] != '\t' && szLine[i] != ' ') {
            Ans.push_back(szLine[i]);
        }
    }
    
    return Ans;
}




//Inherit from servicd/getKeyValue.cpp
KeyResult seperateKey(string Key) {
    KeyResult SepKey;
    bool Side = false;
    for(int i = 0; i < Key.size(); i++) {
        if(Key[i] == '=') {
            Side = true;
        } else if(Side == false && Key[i] != ' ') {
            SepKey.szKeyName.push_back(Key[i]);
        } else if(Side == true && Key[i] != ' ') {
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



map<string, string> readIniFile(string File) {
        Province ProvSetup;
        Pop PopSetup;
        vector<Province> ProvinceWPops;
        fstream Readfile;
        string szLine;
        KeyResult Key;
        map<string, string> Token_Map;
        Readfile.open(File);

        while(getline(Readfile, szLine)) {
                szLine = stripTabs(szLine);
                if(szLine[0] != '#') {
                        Key = seperateKey(szLine);
                        if(Key.szKeyName[0] == '}') {
                                Token_Map.insert({"INI_ENDBRACKET","}"});
                        } else {
                                if(Key.szKeyName.empty() != true) {
                                        Token_Map.insert({"INI_KEYNAME", Key.szKeyName});
                                }
                                if(Key.szKeyValue.empty() != true) {
                                        if(Key.szKeyValue[0] == '{') {
                                                Token_Map.insert({"INI_OPENBRACKET", "{" });
                                        } else {
                                                Token_Map.insert({"INI_KEYVALUE", Key.szKeyValue});
                                        }
                                }
                        }



                }
        }




        return Token_Map;
}


/*
    TODO: This is awful, it wont work for any files that _DONT_ follow the exact same fucking format as the files in
    'history/pops/1836.1.1/'
    So this _MUST_ be replaced in the future with a tokeniser i do believe. -Breizh
*/

/*vector<Province> giveProvincePops(string File) {
//int main(int argc, char* argv[]) {
    vector<Province> ProvinceWPops;
    vector<Pop> PopList;
    fstream Readfile;
    Province ProvSetup;
    Pop PopSetup;
    KeyResult Key;
    uint LeftBracket = 0;
    uint RightBracket = 0;
    string szLine;
    Readfile.open(File);
    Key = seperateKey("}");
    /*
        if theres no keyvalue (for example if szLine = } ), then szKeyName will hold the contents
    */
    

/*
    //Begin Reading entire file
    while(getline(Readfile, szLine)) {
        szLine = stripTabs(szLine);
        //Check if we're reading a comment/dead space, if we arent then continue, otherwise read a new line
        if(szLine[0] != '#' && szLine[0] != ' ' && szLine[0] != '\r') {
            //cout << szLine << endl;
            Key = seperateKey(szLine);
            //check if the KeyName of the line is a province number, if so continue, otherwise if its a } then add one to the counter.
            //cout << Key.szKeyName << endl;
            //cout << "?!?:" << Key.szKeyValue << endl;
            if(isNumber(Key.szKeyName) == true && Key.szKeyValue[0] == '{') {
                LeftBracket++;
                //Begin loop within province
                //cout << "Reading Province (" << Key.szKeyName << ")\n";
                ProvSetup.uID = stoi(Key.szKeyName);
                while(getline(Readfile, szLine)) {
                    szLine = stripTabs(szLine);
                    if(szLine[0] != '#' && szLine[0] != ' ' && szLine[0] != '\r') {
                        Key = seperateKey(szLine);
                        if(Key.szKeyName[0] == '}') {
                            //cout << Key.szKeyName << Key.szKeyValue << endl;
                            RightBracket++;
                        }
                        if(Key.szKeyValue[0] == '{') {
                            //cout << Key.szKeyName << Key.szKeyValue << endl;
                            LeftBracket++;
                        }
                        //cout << "LeftBracket: " << LeftBracket << endl;
                        //cout << "RightBracket: " << RightBracket << endl;
                        if(RightBracket == LeftBracket) { 
                            //cout << "End of Province (" << ProvSetup.iID << ")! Breaking..." << endl;
                            ProvSetup.Populations = PopList;
                            PopList.erase(PopList.begin(), PopList.end());
                            ProvinceWPops.push_back(ProvSetup);
                            break;
                        }
                        
                        if(isKeyNamePop(Key.szKeyName) != false || Key.szKeyValue.compare("}") == 0) {
                            //cout << "Reading Pop: " << Key.szKeyName << endl;
                            PopSetup.szType = Key.szKeyName;
                            while(getline(Readfile, szLine)){
                                szLine = stripTabs(szLine);
                                Key = seperateKey(szLine);
                                if(Key.szKeyName.compare("culture") == 0) {
                                    PopSetup.szCulture = Key.szKeyValue;
                                } else if(Key.szKeyName.compare("religion") == 0) {
                                    PopSetup.szReligion = Key.szKeyValue;
                                } else if(Key.szKeyName.compare("size") == 0) {
                                    PopSetup.uSize = stoi(Key.szKeyValue);
                                } else if(Key.szKeyName.compare("militancy") == 0) {
                                    PopSetup.uMilitancy = stoi(Key.szKeyValue);
                                } else if(Key.szKeyName.compare("rebel_type") == 0) {
                                    PopSetup.szRebel_Type = Key.szKeyValue;
                                } else if(Key.szKeyName[0] == '}'){
                                    RightBracket++;
                                    PopList.push_back(PopSetup);
                                    break;
                                } else {
                                    cout << "(EE) Unknown Variable! : " << Key.szKeyName << " in " << File << endl;
                                }
                            }
                        }
                    }

                }


            } else if(Key.szKeyValue[0] == '}') { RightBracket++; }


        } 
    }

    

    Readfile.close();
    return ProvinceWPops;
}*/ 
