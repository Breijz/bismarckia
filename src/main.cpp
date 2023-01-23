#include <iostream>
#include <thread>

#include "state.h"
#include "province.h"
#include "pop.h"
#include "rgo.h"
#include "common_market.h"
#include "global_market.h"
#include "goods.h"
#include "country.h"
//#include "ini.h"              No longer used


using namespace std;



int main(int argc, char* argv[]) {
        Global_Market GM;

        for(int i = 1; i < GM.vGloMarktGoods.size(); i++) {
                cout << i << " : " << GM.vGloMarktGoods[i].szName << " : " << GM.vGloMarktGoods[i].fOutputAmount << " : " << GM.vGloMarktGoods[i].fBaseCost << endl;
        }





        
        return EXIT_SUCCESS;
}
