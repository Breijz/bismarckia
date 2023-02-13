#pragma once

#include <iostream>
#include <string>
#include <vector>

struct i_StateProvPos {
	uint uProvID;
	uint uProvPos;
};

class State {
	public:
		std::vector<i_StateProvPos> Provinces;
};
