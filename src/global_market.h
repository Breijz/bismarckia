#ifndef global_market_H
#define global_market_H

#include <iostream>
#include <string>

#include "goods.h"

using namespace std;



class Global_Market {
    public:
        Global_Market() {
            bStockpile = false;
    }
    
    private:
        bool bStockpile;                    //May be public in feature?
    
    public:
        vector<Good> vGloMarktGoods;
        //vector<Stockpile> vGloMarktStock; //Not needed for the Global Market
        
    private : void InitaliseWithGoods() {
     
    }
        
        
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

        
        
        

};

#endif