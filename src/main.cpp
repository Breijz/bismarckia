#include <iostream>

#include "ini.h"

using namespace std;

int main() {
	multimap<string, IniTypes> mapToken = mapReadIniFile("game/common/goods.txt");
	
	cout << "size: " << mapToken.size() << endl;

	for(auto autItr = mapToken.begin(); autItr != mapToken.end(); autItr++) {
		cout << autItr->first << " : " << autItr->second << endl;
	}

	return 0;
}
