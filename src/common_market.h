#ifndef common_market_H
#define common_market_H

#include <iostream>
#include <string>

#include "common.h"

using namespace std;

class Common_Market {
    public:
        Common_Market(Global_Market GM) {
            bStockpile = false;
            GM = GM;
    }
    
    private:
        //In the future we want to allow multiple countries to be part of the same common market (namely spherelings with their great powers)
        vector<Good> vComMarktGoods;
        vector<Stockpile> vComMarktStock;
        bool bStockpile;                    //May be public in feature?
        Global_Market GM;
        
    private : void InitaliseWithGoods() {
     
    }
        
        
    public:
        /*
         * first we should take from the common market, if the common market doesnt have enough
         * then we should take from the global market to cover the defecit, if neither the global market 
         * nor the common market has enough then we'll just not have enough
        */
        float fTakeGood(string szGood, float fAmount) {
            int i = 0;
            while(true) {
                if(i >= vComMarktGoods.size()) { 
                    //No such good exists
                    return 0.0;
                }
                if(vComMarktGoods[i].szName == szGood) {
                    break;
                }
                i++;
            }
            
            if(fAmount < vComMarktGoods[i].fCurrentSupply || fAmount == vComMarktGoods[i].fCurrentSupply) {
                vComMarktGoods[i].fCurrentSupply = fAmount - vComMarktGoods[i].fCurrentSupply;                  //TODO implement a private "Remove" function which'll calculate the new cost after removal + demand
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
        }
        
        private : int iPrevDay = 0;
        
        public : void DailyPriceChange(int iDay) {
            if(iDay > iPrevDay && iDay != iPrevDay) {
                int iDifferance = iDay - iPrevDay;
                for(int i = 0; i < vComMarktGoods.size(); i++) {
                    if(vComMarktGoods[i].fCurrentDemand > vComMarktGoods[i].fCurrentSupply) {
                        float fProposedPrice = vComMarktGoods[i].fCurrentCost + (0.01 * iDifferance);
                        if(fProposedPrice < (vComMarktGoods[i].fBaseCost * 5.0) || fProposedPrice == (vComMarktGoods[i].fBaseCost * 5.0)) {
                            vComMarktGoods[i].fCurrentCost = fProposedPrice;
                        }
                        
                    } else if(vComMarktGoods[i].fCurrentDemand < vComMarktGoods[i].fCurrentSupply) {
                        float fProposedPrice = vComMarktGoods[i].fCurrentCost - (0.01 * iDifferance);
                        if(fProposedPrice > (vComMarktGoods[i].fBaseCost * 0.22) || fProposedPrice == (vComMarktGoods[i].fBaseCost * 0.22)) {
                            vComMarktGoods[i].fCurrentCost = fProposedPrice;
                        }
                    } else {
                        cout << "Global Market: Price Equilibrium!\n" << vComMarktGoods[i].fCurrentDemand << " = " << vComMarktGoods[i].fCurrentSupply << endl;
                    }
                }
            } else if(iDay == iPrevDay) {
                cout << "Already Calculated Prices for today!" << endl;
            } else {
                cout << "????? Error in DailyPriceChange in common_market.h" << endl;
            }
            iPrevDay = iDay;
        }

        
        
        

};

#endif