#ifndef goods_H
#define goods_H

#include <iostream>
#include <string>

#include "common.h"

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


/*
#define fCattleOutputAmount 1.8
#define fCattleBasePrice 2.0
#define fCattleTotalBasePrice 3.6

#define fCoalOutputAmount 2.4
#define fCoalBasePrice 2.3
#define fCoalTotalBasePrice 5.52

#define fCoffeeOutputAmount 1.5
#define fCoffeeBasePrice 2.1
#define fCoffeeTotalBasePrice 3.15

#define fCottonOutputAmount 2.2
#define fCottonBasePrice 2.0
#define fCottonTotalBasePrice 4.4

#define fDyeOutputAmount 0.22
#define fDyeBasePrice 1.2      //Written as '12' on https://vic2.paradoxwikis.com/Production i changed it to 1.2 as it seemed to be a typo
#define fDyeTotalBasePrice 2.64

#define fFishOutputAmount 2.2
#define fFishBasePrice 1.5
#define fFishTotalBasePrice 3.3

#define fGrainOutputAmount 1.8
#define fGrainBasePrice 2.2
#define fGrainTotalBasePrice 3.96

#define fIronOutputAmount 1.8
#define fIronBasePrice 3.5
#define fIronTotalBasePrice 6.3

#define fOilOutputAmount 1.0
#define fOilBasePrice 12.0       //
#define fOilTotalBasePrice 12.0  // is 12.0 typo aswell?

#define fOpiumOutputAmount 0.7
#define fOpiumBasePrice 3.2      //the fuck? how is base price > total base price
#define fOpiumTotalBasePrice 2.24

#define fFruitOutputAmount 2.8
#define fFruitBasePrice 1.8
#define fFruitTotalBasePrice 5.04

#define fPreciousMetalOutputAmount 2.0
#define fPreciousMetalBasePrice 8.0
#define fPreciousMetalTotalBasePrice 16.0

#define fRubberOutputAmount 0.75
#define fRubberBasePrice 7.0      //base price > total base price, again
#define fRubberTotalBasePrice 5.25

#define fWoolOutputAmount 5.0
#define fWoolBasePrice 0.7
#define fWoolTotalBasePrice 3.5

#define fSilkOutputAmount 0.25
#define fSilkBasePrice 10         //base price > total base price, again...
#define fSilkTotalBasePrice 2.5

#define fSulpherOutputAmount 2.0
#define fSulpherBasePrice 6.0
#define fSulpherTotalBasePrice 12.0

#define fTeaOutputAmount 1.75
#define fTeaBasePrice 2.6
#define fTeaTotalBasePrice 4.55

#define fTimberOutputAmount 8.0
#define fTimberBasePrice 0.9
#define fTimberTotalBasePrice 7.2

#define fTobaccoOutputAmount 2.5
#define fTobaccoBasePrice 1.1
#define fTobaccoTotalBasePrice 2.75

#define fTropicalWoodOutputAmount 4.0
#define fTropicalWoodBasePrice 5.4
#define fTropicalWoodTotalBasePrice 21.6
*/