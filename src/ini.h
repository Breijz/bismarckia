#ifndef ini_H
#define ini_H

#include <iostream>
#include <fstream>
#include <string>

#include "global_market.h"
#include "goods.h"

using namespace std;



class INI {
    
    public:
        string szKeyName;
        string szKeyValue;
        string szSectionName;
        

        void ReadGoodsFile() {
            ifstream Readfile;
            Good intl_Setup;
            string Line;
            bool ReadingGood = false;
            Readfile.open("neu/00-goods.ini");
            while(getline(Readfile, Line)) {
                if(Line[0] == '[' || Line[0] == ' ' && ReadingGood == true) {
                    GM.vGloMarktGoods.push_back(intl_Setup);
                    ReadingGood = false;
                }
                if(Line[0] == '[') {
                    ReadingGood = true;
                    GetSectionName(Line);
                    intl_Setup.szName = szSectionName;
                }
                if(ReadingGood == true) {
                    SeperateKey(Line);
                    //Here we check for keys
                    if(szKeyName == "fOutputAmount") {
                        cout << "ini.h : szKeyValue = " << szKeyValue << endl;
                        intl_Setup.fOutputAmount = stof(szKeyValue);
                    } else
                    if(szKeyName == "fBasePrice") {
                        cout << "ini.h : szKeyValue = " << szKeyValue << endl;
                        intl_Setup.fOutputAmount = stof(szKeyValue);
                    }

                }
                
            }

        }
        
        void SeperateKey(string szKey) {
            bool Delim = false;
            for(int i = 0; i < szKey.length(); i++) {
                if(szKey[i] == '=') { Delim = true; }
                if(Delim == false && szKey[i] != ' ' || szKey[i] != '\n') { szKeyName.push_back(szKey[i]);}
                if(Delim == true && szKey[i] != ' ' || szKey[i] != '\n') { szKeyValue.push_back(szKey[i]);}
            }
        }
        
        void GetSectionName(string szLine) {
            for(int i = 0; i < szLine.length(); i++) {
               if(szLine[i] != '[' && szLine[i] != ']' && szLine[i] != '\n') {
                szSectionName.push_back(szLine[i]);
               } 
            }
        }

};

#endif