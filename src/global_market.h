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
        bool bStockpile;
        
    public:
        vector<Good> vGloMarktGoods;
        vector<Stockpile> vGloMarktStock;
        
        
    public:
        /*
         * first we should take from the common market, if the common market doesnt have enough
         * then we should take from the global market to cover the defecit, if neither the global market 
         * nor the common market has enough then we'll just not have enough
        */
        float fTakeGood(string szGood, float fAmount) {
            
        }
        
        

};

#endif