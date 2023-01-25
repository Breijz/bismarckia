#include "filelisting.h"

#include <iostream>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

/*
    NOTE: This is inherited from serviced/src/getServices.cpp   -Breizh
*/

vector<string> listingOfFolder(char* Directory) {
    DIR* dir;
    struct dirent* Readed;

    vector<string> Listing;

    dir = opendir(Directory);

    while(Readed = readdir(dir)){
        if(Readed->d_name[0] != '.') {
            Listing.push_back(Readed->d_name);
        }
    }
    
    return Listing;
}