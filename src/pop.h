#ifndef pop_H
#define pop_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;

/*class Pop { 

        public:
        Pop() {
                POPID = 0;
                iSize = 0;
                szType = "Farmer";
                szNationality = "Frisian";
                szReligion = "Catholic";
                fMilitancy = 0.00;
                fConsciousness = 0.00;
                //Implement Idealogy
                // Format is NationalistL25.6, LiberalL45.8, etc...
                // L is the delminator between the Idealogy's name and its amount
                vector<string> Idealogy;
                //Implement Political wants (pro military, residency etc
                // Similar to Idealogy
                // JingoismL88.8, Pro-CitizenshipL12.3, etc...
                vector<string> Causes;
                fBasicneeds = 0.00;
                fEverydayneeds = 0.00;
                fLuxuryneeds = 0.00;
        }

        public:
                uint POPID;
                uint iSize;
                string szType;
                string szNationality;
                string szReligion;
                float fMilitancy;
                float fConsciousness;
                //Implement Idealogy
                // Format is NationalistL25.6, LiberalL45.8, etc...
                // L is the delminator between the Idealogy's name and its amount
                vector<string> Idealogy;
                //Implement Political wants (pro military, residency etc
                // Similar to Idealogy
// JingoismL88.8, Pro-CitizenshipL12.3, etc...
                vector<string> Causes;
                float fBasicneeds;
                float fEverydayneeds;
                float fLuxuryneeds;
                float fLiteracy;

};*/

//Minor rework, we'll just add things as we need them.
class Pop {
        public:
                Pop(){
                        szType = "farmer";
                        szCulture = "minnesotan";
                        szReligion = "protestant";
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
