#ifndef goods_H
#define goods_H

#include <iostream>
#include <string>


using namespace std;

class Good {

    public:
        //Good(string szGoodName) {
        //    szName = szGoodName;
        Good() {
            szName = "NULL";
            fActivity = 0.0;
            fBaseCost = 0.0;
            uBasePop = 0;
            fOutputAmount = 0.0;
            fCurrentCost = 0.0;
            fCurrentDemand = 0.0;
            fCurrentSupply = 0.0;
        }
    
        public:
            string szName;
            float fActivity;        //Activity is how much the country+spherelings export/import, positive numbers mean exports > imports and vice versa
            float fBaseCost;
            float fOutputAmount;
            float fCurrentCost;
            float fCurrentDemand;
            float fCurrentSupply;
            uint uBasePop;
            vector<string> vLifeNeeds;
            vector<string> vEveryNeeds;
            vector<string> vLuxNeeds;

};


class Stockpile {
    public:
    Stockpile() {
        szName = "NULL";
        fStock = 0.0;
        fPrevStock = 0.0;
    }
    
    public:
        string szName;
        float fStock;
        
    private:
        float fPrevStock;
        
    public:
        float fGiveIncrease() {
            return (fStock - fPrevStock);
        }
        
        void fAddStock(float fGoods) {
            fPrevStock = fStock;
            fStock = fGoods + fStock;
            return;
        }

};


#endif
