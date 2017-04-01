#pragma once

typedef long long ll;

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <time.h>
#include <utility>
#include <vector>

using namespace std;

//util classes
struct Input {
	int h, w, r, pb, pr, b, br, bc;
	vector<vector<char>> grid;
	vector<vector<int>> countwalls;
};

//input handling
void readInput(Input& input, istream& in) {
	//TODO read input
}
