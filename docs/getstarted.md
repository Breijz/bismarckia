# Bismarckia, Getting started  
  
## Compiling  
The build system used is (GNU) Make, albeit BSD Make ought to work aswell, and it does compile with GCC 12.2.1, although it doesnt use anything GNU specific so it ought to compile with other compilers aswell.  
After it is done compiling a binary called `bmserver` should exist in the root of the project, for it and by extension any functions of the project to work, youll need a folder called `game` in the root which contains all of the Vic2 Data  
For sake of simplicity you can just symlink it. `ln -s game ~/.local/share/steam/steamapps/common/Victoria\ 2`

## Files  
/src/main.cpp - This is the entry point of the program, itll contain various demonstrations/usages of the functions provided.  
/src/ini.cpp - This contains functions related to tokenising files, its not recommended to use these directly unless implementing a function which needs to use data from Vic2s Files.
/src/prov.cpp - This contains functions which use the data provided by `map_ReadIniFile` from ini.cpp, this includes `populateProvinceWPops` which takes the files from `/history/pop/1836.1.1/` to populate provinces with their pops it also includes `populateProvinceWAttrib` which likewise populates provinces with their attributes, be this their owner, controller, trade good, buildings, so forth  
/src/province.h - This contains the class which defines the province  
/src/pop.h - This contains the class which defines the Pop (used in Provinces)
/src/market.hpp - This is currently WIP, but itll contain the class whichll model the market, to be used in both the global and common market system.  
/src/filelisting.cpp - This contains a function to read and retrieve the files from a directory, it is operating system specific, and thus wont work on Windows.  
/src/factory.h - This is currently WIP, but it contains the class defining a Factory.  

## Misc Folders  
/src/alt - this is old code that ought to be expunged later.

