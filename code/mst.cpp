#pragma once
#include "util.cpp"
#include <limits>
#include <set>

void addRoute(vector<pair<int,int>> &cables, int from_row, int from_col, int to_row, int to_col)
{
	int row_diff = abs(from_row - to_row);
	int col_diff = abs(from_col - to_col);
	int p_row = from_row;
	int p_col = from_col;
	while (row_diff > 0 || col_diff > 0)
	{
		// go down
		if (p_row < to_row)
			p_row++;
		else if (p_row > to_row)
			p_row--;

		// go right
		if (p_col < to_col)
			p_col++;
		else if (p_col > to_col)
			p_col--;

		cables.push_back(make_pair(p_row, p_col));
		row_diff = abs(p_row - to_row);
		col_diff = abs(p_col - to_col);
	}
}

/*
void prim(int br, int bc, vector<pair<int, int>> &cables, 
	vector<pair<int, int>> routers)
{
	routers.push_back(make_pair(br,bc));
	int from[routers.size()];
	set<pair<int, int> > pq;
}*/

//give cells to connect to backbone
vector<pair<int, int>> mst(Input& input, vector<pair<int, int>> &routers) 
{
	vector<pair<int,int>> cables;
	int from_row = input.br;
	int from_col = input.bc;
	for (pair<int,int> &p : routers)
	{
		int to_row = p.first;
		int to_col = p.second;
		addRoute(cables, from_row, from_col, to_row, to_col);
		from_row = to_row;
		from_col = to_col;
	}	
	set<pair<int,int>> setCables(cables.begin(), cables.end());
	vector<pair<int,int>> cablesReturn(setCables.begin(), setCables.end());
	return cablesReturn;
}


