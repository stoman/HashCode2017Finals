#pragma once
#include "util.cpp"

int addcell(Input &input, int i, int j)	{
	if (input.grid[i][j] == '#')
		return 1;
	else
		return 0;
}

// call before calling connectedcells
void countwalls(Input &input)	{

	input.countwalls.resize(input.h);
	for (int i = 0; i < input.h; i++)
		input.countwalls[i].resize(input.w);
		
	// cell (0,0)	
	input.countwalls[0][0] = addcell(input,0,0);
	
	// row 0	
	for (int j = 1; j < input.w; j++)
		input.countwalls[0][j] = input.countwalls[0][j-1] + addcell(input,0,j);
	
	// all other rows
	for (int i = 1; i < input.h; i++)	{
		input.countwalls[i][0] = input.countwalls[i-1][0] + addcell(input,i,0);
		for (int j = 1; j < input.w; j++)	
			input.countwalls[i][j] = input.countwalls[i-1][j] + input.countwalls[i][j-1] - input.countwalls[i-1][j-1] + addcell(input,i,j);
	}		
}

int getsum(Input &input, int i, int j)	{
	if (i >= 0 && j >= 0)
		return input.countwalls[i][j];
	else
		return 0;
}

int getrectanglesum(Input &input, int i1, int j1, int i2, int j2)	{
	return getsum(input,i2,j2) - getsum(input,i2,j1-1) - getsum(input,i1-1,j2) + getsum(input,i1-1,j1-1);
}

// gives back a list of all reachable target and void cells
vector<pair<int, int>> connectedcells(Input& input, pair<int, int>& cell) {
	int ci = cell.first;
	int cj = cell.second;
	static vector<vector<pair<int,int>>> allcells(input.w*input.h);
	static vector<bool> was(input.w*input.h,false);
	
	// wall as initial cell should automatically return an empty vector
	if (was[ci*input.w+cj])
		return allcells[ci*input.w+cj];
	
	was[ci*input.w+cj] = true;
	vector<pair<int,int>> cells;
	int rectanglesum = 0;
	for (int i = max(0,ci-input.r); i <= min(input.h-1,ci+input.r); i++)	{
		for (int j = max(0,cj-input.r); j <= min(input.w-1,cj+input.r); j++)	{
			rectanglesum = getrectanglesum(input,min(i,ci),min(j,cj),max(i,ci),max(j,cj)); 
			if (rectanglesum == 0)
				cells.push_back({i,j});
		}
	}
	allcells[ci*input.w+cj] = cells;
	
	//cerr << "starting from: " << ci << ' ' << cj;
	//cerr << " can reach " << cells.size() << endl;
	//for (auto i : cells)
	//	cerr << i.first << ' ' << i.second << endl;
	//cerr << endl;

	return cells;
}