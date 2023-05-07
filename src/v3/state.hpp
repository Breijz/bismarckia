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
		uint uStateID = 0;
		std::vector<i_StateProvPos> Provinces;
};
