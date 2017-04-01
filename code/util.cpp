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
	vector<vector<int>> distc, distr;
};

//preprocessing	
void computedistances(Input& input)	{
	input.distr.resize(input.h);
	input.distc.resize(input.h);
	for (int i = 0; i < input.h; i++)
	{
		input.distc[i].resize(input.w);
		input.distr[i].resize(input.w);
	}
	
	for (int i = 0; i < input.h; i++)
	{ 
		 for (int j = 0; j < input.w; j++)
		 {
			 input.distc[i][j] = input.h+input.w;
			 input.distr[i][j] = input.h+input.w;
			 
			 for (int l = 0; l < input.h; l++)
			 	if (input.grid[l][j] == '#')
			 		input.distr[i][j] = min(input.distr[i][j],abs(i-l));
			
			 for (int l = 0; l < input.w; l++)
			 	if (input.grid[i][l] == '#')
					input.distc[i][j] = min(input.distc[i][j],abs(j-l));
		 }
	}
}

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
