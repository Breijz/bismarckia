#ifndef ini_H
#define ini_H

#include <iostream>
#include <fstream>
#include <string>

#include "global_market.h"
#include "common_market.h"

using namespace std;



class INI {
    
    public:
    INI(Global_Market GM) {
        GM = GM;
    }
    
    public:
        Global_Market GM;
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
                if(Line[0] == '[' && ReadingGood == true) {
                    GM.vGloMarktGoods.push_back(intl_Setup);
                    ReadingGood = false;
                }
                if(Line[0] == '[') {
                    ReadingGood = true;
                }
                if(ReadingGood == true) {
                   SeperateKey(Line);
                    
                }
                
            }

        }
        
        void SeperateKey(string szKey) {
            bool Delim = false;
            for(int i = 0; i < szKey.length(); i++) {
                if(szKey[i] == '=') { Delim = true; }
                if(Delim == false && szKey != ' ' || szKey != '\n') { szKeyName.push_back(szKey[i]);}
                if(Delim == true && szKey != ' ' || szKey != '\n') { szKeyValue.push_back(szKey[i]);}
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