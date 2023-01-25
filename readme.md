Bismarckia
==========  
  
Bismarckia is a attempt to create a open source vic2 recreation, mainly server and shared files.  
  
Use of original vic2 files
--------------------------  
  
Longterm the plan isnt to use any files provided by the original vic2 or its DLCs, currently
some files are used, however not redistributed, and so a original copy of vic2 must be owned.

However i *do* create files based off data provided by the Vic2 Wiki, atleast for everything
licensed under CC BY-SA.

File Structure
--------------
/ - Root of directory (this includes this readme)
/src - source code, should be mostly generic stuff (stuff that can be used in a engine, client, and/or server)
/neu - relic, used for anything custom made
/game - contains game files, it is excluded in the .gitignore, files from the orignal vic2 should be put in here (for example /game/history)