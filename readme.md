Bismarckia
==========  
  

File Structure
--------------
/ - Root of directory (this includes this readme)  
/src - source code, should be mostly generic stuff (stuff that can be used in a engine, client, and/or server)  
/neu - relic, used for anything custom made  
/game - contains game files, it is excluded in the .gitignore, files from the orignal vic2 should be put in here (for example /game/history)  

Compiling
=========
  
On Linux
--------
This is only tested on Artix (as thats the distro I use, it compiles with gcc + gnu Make, to compile both the client and server
just type 'make' or 'make all', to just compile the server/client just type 'make server' or 'make client' respectively.
