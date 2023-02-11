#include <iostream>
#include <string>
#include <vector>

#include "market.hpp"
#include "ini.h"
#include "prov.h"

#include "goods.h"

using namespace std;



vector<Good> SetupGoods() {
	vector<Token> TokMap = mapReadIniFile("game/common/goods.txt");
}
