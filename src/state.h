#ifndef state_H
#define state_H

#include <iostream>
#include <string>
#include <vector>

#include "common.h"

using namespace std;



class State {
        public:
        State() {
                string szRegion = "NULL";
                iContient = 0;
        }

        public:
                vector<Province> ProvincesOfState;
                vector<string> Cores;
                string szRegion;
                uint iContient;
};

#endif