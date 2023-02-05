#ifndef pop_H
#define pop_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;

//Minor rework, we'll just add things as we need them.
class Pop {
        public:
                Pop(){
                        szType = "NULL";
                        szCulture = "NULL";
                        szReligion = "NULL";
                        szRebelType = "NULL";
                        fMilitancy = 0;
                        uSize = 0;
                }

        public:
                string szType;
                string szCulture;
                string szReligion;
                string szRebelType;
                float fMilitancy;
                uint uSize;
};

#endif
