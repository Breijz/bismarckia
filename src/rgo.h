#ifndef rgo_H
#define rgo_H

#include <iostream>
#include <string>
#include <cmath>

#include "common.h"

using namespace std;

/*
    Heres a sundry list of what we need, variable wise:

        iWorkers (this is how many Farmers/Labourers in the province)
        fTerrain ??? i dont quite know what this is, however in https://vic2.paradoxwikis.com/Resource_gathering_operation it uses -.10 as a example,
         so its a terrain modifier
        fRGOSizeMod (this is the RGO Size Modifier, presumably from tech/terrain?)
        fOverseaPenalty (this is presumably from tech/distance?)
        fWarExhaustion (this is just normal War Exhaustion)
        fRGOThroughPutEfficencyMod (this is from Tech)
        fMobilizedPenalty (just normal Mobilized Penalty)
        iProvInfrastructure (just normal Province Infrastructure)
        fAristocratPercent (this is what percentage of the Province are Aristocrats)
        fRGOSizeMod (presumably from Tech/Terrain)
        fOutputAmount (this is from goodnums, it changes with each good)
        iProvWorkers (this is how many workers (farmers/labourer) in the province)
        iStateAristocrats (this is how many aristocrats are in the state)
*/


class RGO {
    
        public:
                int iGiveProvSize(int iWorkers, float fTerrain) {
                    // iWorkers can be Farmers or Labourers, it depends on if the Good uses a farm or mine respectively
                    // This code works for both though.
                    // https://vic2.paradoxwikis.com/Resource_gathering_operation
                    
                    float x, y, z;
                    x = 40000 * (1 - fTerrain);
                    y = iWorkers / x;
                    z = ceil(y);
                    z = z * 1.5;

                    return floor(z);
                }

                float fMaxWorkers(int iProvSize, float fTerrain, float fRGOSizeMod) {
                    //What is Terrain and RGO Size Modifier? https://vic2.paradoxwikis.com/Production
                    return 40000 * iProvSize * (1 + fTerrain + fRGOSizeMod);
                }
        
                float fProduction(float fBaseProduction, float fThroughput, float fOutputEfficiency) {
                    return fBaseProduction * fThroughput * fOutputEfficiency;
                }
                
                float fThroughPut(int iNumWorkers, int iMaxWorkers, float fRGOThroughPutEfficiencyMod, float fWarExhaustion, float fOverseaPenalty) {
                    return (iNumWorkers / iMaxWorkers) * (1 + fRGOThroughPutEfficiencyMod - fWarExhaustion) * fOverseaPenalty;
                }
                
                float fOutputEfficiency(float fAristocratPercent, float fRGOThroughPutEfficiencyMod, float fTerrain, int iProvInfrastructure, float fMobilizedPenalty) {
                    return 1 + fAristocratPercent + fRGOThroughPutEfficiencyMod + fTerrain + iProvInfrastructure * (1 + fMobilizedPenalty);
                }
                

                /*
                    iProvSize is provided by iGiveProvSize Function
                    fTerrain i dont know TODO
                    fRGOSizeMod i dont know TODO
                    fOutputAmount provided in goodnums.h, this changes for each good

                */
                
                float fBaseProduction(int iProvSize, float fTerrain, float fRGOSizeMod, float fOutputAmount) {
                    return iProvSize * (1 + fTerrain + fRGOSizeMod) * fOutputAmount;
                }
        
                float fOwnerIncome(float fRGOIncome, int iStateAristocrats, int iProvWorkers) {
                    return fRGOIncome * 2 * iStateAristocrats / iProvWorkers;
                }

};

#endif