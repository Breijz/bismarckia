#include "ini.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

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


/*
 * This code is *alot* more generic, its nothing more than a tokeniser
 * for the INI style files that Vic2 uses, and it should work for any
 * format of the file, this function ought not to be used on its own but
 * instead as part of another function...       -Breizh
 */

vector<Token> readIniFile(string File) {
        ifstream Readfile;
        string szLine;
        KeyResult Key;
        Token t_Setup;
        vector<Token> Token_Map;
        Readfile.open(File);


        while(getline(Readfile, szLine)) {
                t_Setup.Type.erase(t_Setup.Type.begin(), t_Setup.Type.end());
                t_Setup.Value.erase(t_Setup.Value.begin(), t_Setup.Value.end());
                Key.szKeyName.erase(Key.szKeyName.begin(), Key.szKeyName.end());
                Key.szKeyValue.erase(Key.szKeyValue.begin(), Key.szKeyValue.end());
                szLine = stripTabs(szLine);
                if(szLine[0] != '#' && szLine[0] != '\r') {
                        Key = seperateKey(szLine);
                        if(Key.szKeyName.empty() != true && Key.szKeyName.compare("}\r") != 0) {
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




        Readfile.close();
        return Token_Map;
}

/*
 * This function populates a given vector of provinces with their pops
 * from history/1836.1.1/pops
 */

vector<Province> populateProvinceWPops() {
        vector<Token> Token_Map;
        //Token_Map = readIniFile(File);
        vector<Province> ProvWPop;
        vector<string> Listing;
        uint uOPENBRACKET = 0;
        uint uENDBRACKET = 0;

        Listing = listingOfFolder("game/history/pops/1836.1.1/");
        
        /*
         Fixing the File Listing 
        for(int i = 0; i < Listing.size(); i++) {
                Listing[i] = "game/history/pops/1836.1.1/" + Listing[i];
                cout << Listing[i] << endl;
        }*/


        for(uint uFLInt = 0; uFLInt < Listing.size(); uFLInt++) {
                Token_Map = readIniFile(Listing[uFLInt]);
                //cout << Listing[uFLInt] << endl;
                //cout << ProvWPop.size() << endl;
                cout << uFLInt << endl;
                uint uOPENBRACKET = 0;
                uint uENDBRACKET = 0;

                for(int i = 0; i < Token_Map.size(); i++) {
                        /* here we start reading Token_Map */
                        if(Token_Map[i].Type.compare("INI_KEYNAME") == 0 && isNumber(Token_Map[i].Value) == true) {
                                /* Here we begin reading within the province */
                                Province ProvSetup;
                                ProvSetup.uID = stoi(Token_Map[i].Value);
                                for(;i < Token_Map.size(); i++) {
                                        if(Token_Map[i].Type.compare("INI_OPENBRACKET") == 0) { uOPENBRACKET++; }
                                        if(Token_Map[i].Type.compare("INI_ENDBRACKET") == 0) { uENDBRACKET++; }
                                        //cout << uOPENBRACKET << " : " << uENDBRACKET << endl;
                                        if(uENDBRACKET == uOPENBRACKET) { uOPENBRACKET = 0; uENDBRACKET = 0; ProvWPop.push_back(ProvSetup); break; }   /* Here we would push the finished province */
                                        if(isKeyNamePop(Token_Map[i].Value) == true) {
                                                Pop PopSetup;
                                                PopSetup.szType = Token_Map[i].Value;
                                                for(i++ ;i < Token_Map.size(); i++) {
                                                        if(Token_Map[i].Type.compare("INI_OPENBRACKET") == 0) { /*cout << uOPENBRACKET << " : " << uENDBRACKET << endl;*/ uOPENBRACKET++; }
                                                        if(Token_Map[i].Type.compare("INI_ENDBRACKET") == 0) { uENDBRACKET++; }
                                                        if(uENDBRACKET == uOPENBRACKET) { uOPENBRACKET = 0; uENDBRACKET = 0; ProvSetup.Populations.push_back(PopSetup); break; }   /* Here we would push the finished pop */
        
        
                                                        if(Token_Map[i].Value.compare("culture") == 0) {
                                                                i++;
                                                                PopSetup.szCulture = Token_Map[i].Value;
                                                        }
                                                        if(Token_Map[i].Value.compare("religion") == 0) {
                                                                i++;
                                                                PopSetup.szReligion = Token_Map[i].Value;
                                                        }
                                                        if(Token_Map[i].Value.compare("size") == 0) {
                                                                i++;
                                                                PopSetup.uSize = stoi(Token_Map[i].Value);
                                                        }
                                                        if(Token_Map[i].Value.compare("militancy") == 0) {
                                                                i++;
                                                                PopSetup.uMilitancy = stoi(Token_Map[i].Value);
                                                        }
                                                        if(Token_Map[i].Value.compare("rebel_type") == 0) {
                                                                i++;
                                                                PopSetup.szRebel_Type = Token_Map[i].Value;
                                                        }
        
                                                }
                                        } else {
                                                //cout << "Invalid! " << Token_Map[i].Value << endl;
                                                //Commented out to prevent spam
                                        }
        
                                }
                        }
                }
        
        }
        


        //cout << ProvWPop.size() << endl;
        return ProvWPop;
}

















 
