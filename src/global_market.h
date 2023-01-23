#ifndef global_market_H
#define global_market_H

#include <iostream>
#include <string>
#include <fstream>
//#include "unistd.h"


using namespace std;



typedef struct {
    string Keyname;
    string KeyValue;
} KeyResult;

class Global_Market {
    public:
        Global_Market() {
            bStockpile = false;
            ReadGoodsFile();
        }
    
    private:
        bool bStockpile;                    //May be public in feature?
    
    public:
        //vGloMarktGoods[0] == "NULL", counting/iterating vGloMarktGoods should always start from 1
        //!!! NEVER ITERATE FROM 0 !!! 
        vector<Good> vGloMarktGoods;
        //vector<Stockpile> vGloMarktStock; //Not needed for the Global Market
        
        
    public:
        /*
         * first we should take from the common market, if the common market doesnt have enough
         * then we should take from the global market to cover the defecit, if neither the global market 
         * nor the common market has enough then we'll just not have enough
        */
        //Needs reworking for Global market
        /*float fTakeGood(string szGood, float fAmount) {
            int i = 0;
            while(true) {
                if(i >= vGloMarktGoods.size()) { 
                    //No such good exists
                    return 0.0;
                }
                if(vGloMarktGoods[i].szName == szGood) {
                    break;
                }
                i++;
            }
            
            if(fAmount < vGloMarktGoods[i].fCurrentSupply || fAmount == vGloMarktGoods[i].fCurrentSupply) {
                vGloMarktGoods[i].fCurrentSupply = fAmount - vGloMarktGoods[i].fCurrentSupply;                  //TODO implement a private "Remove" function which'll calculate the new cost after removal + demand
                return fAmount;
            } else {
                //we reuse the code from before, i figure we wont need int i in this partint i = 0;
                while(true) {
                    if(i >= GM.vGloMarktGoods.size()) { 
                        //No such good exists
                        return 0.0;
                    }
                    if(GM.vGloMarktGoods[i].szName == szGood) {
                        break;
                    }
                    i++;
                }

                if(fAmount < GM.vGloMarktGoods[i].fCurrentSupply || fAmount == GM.vGloMarktGoods[i].fCurrentSupply) {
                    GM.vGloMarktGoods[i].fCurrentSupply = fAmount - GM.vGloMarktGoods[i].fCurrentSupply;                  //TODO implement a private "Remove" function which'll calculate the new cost after removal + demand
                    return fAmount;                    
                } else {
                    //we dont have enough of that good, so we return 0.0, caller will check return value
                    return 0.0;
                }
            }
            

            //we shouldn't get here so we just return 0.0
            return 0.0; 
        }*/
        
        private : int iPrevDay = 0;
        
        public : void DailyPriceChange(int iDay) {
            if(iDay > iPrevDay && iDay != iPrevDay) {
                int iDifferance = iDay - iPrevDay;
                for(int i = 0; i < vGloMarktGoods.size(); i++) {
                    if(vGloMarktGoods[i].fCurrentDemand > vGloMarktGoods[i].fCurrentSupply) {
                        float fProposedPrice = vGloMarktGoods[i].fCurrentCost + (0.01 * iDifferance);
                        if(fProposedPrice < (vGloMarktGoods[i].fBaseCost * 5.0) || fProposedPrice == (vGloMarktGoods[i].fBaseCost * 5.0)) {
                            vGloMarktGoods[i].fCurrentCost = fProposedPrice;
                        }
                        
                    } else if(vGloMarktGoods[i].fCurrentDemand < vGloMarktGoods[i].fCurrentSupply) {
                        float fProposedPrice = vGloMarktGoods[i].fCurrentCost - (0.01 * iDifferance);
                        if(fProposedPrice > (vGloMarktGoods[i].fBaseCost * 0.22) || fProposedPrice == (vGloMarktGoods[i].fBaseCost * 0.22)) {
                            vGloMarktGoods[i].fCurrentCost = fProposedPrice;
                        }
                    } else {
                        cout << "Global Market: Price Equilibrium!\n" << vGloMarktGoods[i].fCurrentDemand << " = " << vGloMarktGoods[i].fCurrentSupply << endl;
                    }
                }
            } else if(iDay == iPrevDay) {
                cout << "Already Calculated Prices for today!" << endl;
            } else {
                cout << "????? Error in DailyPriceChange in global_market.h" << endl;
            }
            iPrevDay = iDay;
        }

    // This is just INI file stuff past this point, as for why its in here, its because i cant figure out how to give a class a class (ie void Function(Global_Market GM) {} )
    // nothing should be public in here by-the-way
    private:
        string szKeyName;
        string szKeyValue;
        string szSectionName;
        

        void ReadGoodsFile() {
            ifstream Readfile;
            Good intl_Setup;
            string Line;
            bool ReadingGood = false;
            
            /*if(access("neu/00-goods.ini", F_OK) == 0) {
                cout << "Yes\n";
            } else {
                cout << "no\n";
            }*/

            Readfile.open("neu/00-goods.ini");
            while(getline(Readfile, Line)) {
                szKeyName.erase(0, szKeyName.length());
                szKeyValue.erase(0, szKeyValue.length());
                szSectionName.erase(0, szSectionName.length());
                if(Line[0] == '[' || Line[0] == ' ' && ReadingGood == true) {
                    //cout << vGloMarktGoods.size() << " : " << szSectionName << endl;
                    vGloMarktGoods.push_back(intl_Setup);
                    ReadingGood = false;
                }
                if(Line[0] == '[') {
                    ReadingGood = true;
                    GetSectionName(Line);
                    intl_Setup.szName = szSectionName;
                }
                if(Line[0] != '[' && Line[0] != ' ' && Line[0] != '\n' && ReadingGood == true && Line[0] != '#') {
                    SeperateKey(Line);
                    //cout << Line << " -> " << szKeyName << " & " << szKeyValue << endl;
                    //Here we check for keys
                    //if(szKeyName == "fOutputAmount") {
                    if(szKeyName.compare("fOutputAmount") == 0) {
                        //cout << "ini.h : szKeyValue = " << szKeyValue << endl;
                        intl_Setup.fOutputAmount = stof(szKeyValue);
                    } 
                    if(szKeyName.compare("fBasePrice") == 0) {
                        //cout << "ini.h : szKeyValue = " << szKeyValue << endl;
                        intl_Setup.fBaseCost = stof(szKeyValue);
                    }

                }
                
            }

        }
        
        /*void SeperateKey(string szKey) {
            szKeyName.erase(0, szKeyName.length());
            szKeyValue.erase(0, szKeyValue.length());
            szSectionName.erase(0, szSectionName.length());
            bool Delim = false;
            for(int i = 0; i < szKey.size(); i++) {
                if(szKey[i] == '=') { Delim = true; }
                else if(Delim == false && szKey[i] != ' ' || szKey[i] != '\n') { szKeyName.push_back(szKey[i]);}
                else if(Delim == true && szKey[i] != ' ' || szKey[i] != '\n') { szKeyValue.push_back(szKey[i]);}
            }
        }*/
        
        //Based off serviced's implemation of getKeyValue in src/getKeyValue.cpp
        void SeperateKey(string Line) {
            bool DelimPassed = false;
            for(int i = 0; i < Line.size(); i++) {
                if(Line[i] == '=') {
                    DelimPassed = true;
                } else if(DelimPassed == false) {
                    szKeyName.push_back(Line[i]);
                } else if(DelimPassed == true) {
                    szKeyValue.push_back(Line[i]);
                }
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