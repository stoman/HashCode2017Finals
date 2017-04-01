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
    in >> input.h >> input.w >> input.r;
    in >> input.pb >> input.pr >> input.b;
    in >> input.br >> input.bc;

	input.grid.resize(input.h);
    for (int r = 0; r < input.h; r++) {
		input.grid[r].resize(input.w);
        for (int c = 0; c < input.w; c++) {
            in >> input.grid[r][c];       
        }
    }
}
