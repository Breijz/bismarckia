#include "filelisting.h"

#include <iostream>
#include <filesystem>
#include <dirent.h>
#include <sys/types.h>

#include "unistd.h"

using namespace std;

/*
    NOTE: This is inherited from serviced/src/getServices.cpp   -Breizh
*/

vector<string> listingOfFolder(char* Directory, bool keepFilePath) {
    vector<string> Listing;
        if(access(Directory, F_OK) != 0) {
                cout << "File Doesnt Exist: " << Directory << endl;
                return Listing;
        }
        

    DIR* dir;
    struct dirent* Readed;


    dir = opendir(Directory);

    while(Readed = readdir(dir)){
        if(Readed->d_name[0] != '.') {
            Listing.push_back(Readed->d_name);
        }
    }

    // Fixes the Listing 
    if(keepFilePath == true) {
    	for(int i = 0; i < Listing.size(); i++) {
		Listing[i] = Directory + Listing[i];
    	}
    }
    
    return Listing;
}
