#ifndef state_H
#define state_H

#include <iostream>
#include <string>
#include <vector>

#include "province.h"

using namespace std;



class State {
        public:
        State() {
                szStateName = "NULL";
                uStateID = 0;
                szRegion = "NULL";
                uContient = 0;
        }

        public:
                string szStateName;
                uint uStateID;
                vector<Province> ProvincesOfState;
                vector<string> Cores;
                string szRegion;
                uint uContient;
};

#endif