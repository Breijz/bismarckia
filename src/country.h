#ifndef country_H
#define country_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;



class Country {
    public:
        Country() {
            szName = "NULL";
            uPrestige_Score = 0;
            uMilitary_Score = 0;
            uIndustrial_Score = 0;
        }
        
    public:
        string szName;
        Common_Market CM;
        vector<State> StatesOfCountry;
        uint uPrestige_Score;
        uint uMilitary_Score;
        uint uIndustrial_Score;
};



#endif