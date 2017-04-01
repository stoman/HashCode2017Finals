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


vector<pair<int, int>> prim(int br, int bc, vector<pair<int, int>> routers)
{
	vector<pair<int, int>> cables;
	routers.push_back(make_pair(br,bc));
	vector<int> prev(routers.size(), -1);
	vector<int> dist(routers.size(), numeric_limits<int>::max());
	dist[routers.size()-1] = 0;

	set<pair<int, int> > pq;
	for (int i = 0; i < routers.size(); ++i)
		pq.insert(make_pair(dist[i], i));
	while (!pq.empty())
	{
		int cur = pq.begin()->second;
		pq.erase(pq.begin());
		dist[cur] = -1;
		int parent = prev[cur];
		if (parent != -1)
		{
			addRoute(cables, routers[parent].first, routers[parent].second, 
				routers[cur].first, routers[cur].second);
		}
		for (int i = 0; i < routers.size(); ++i)
		{
			int x_diff = abs(routers[cur].first - routers[i].first);
			int y_diff = abs(routers[cur].second - routers[i].second);
			int newDist = max(x_diff, y_diff);
			if (newDist < dist[i])
			{
				pq.erase(make_pair(dist[i],i));
				dist[i] = newDist;
				prev[i] = cur;
				pq.insert(make_pair(dist[i],i));
			}
		}
	}
	return cables;
}


vector<pair<int, int>> dummyMST(int br, int bc, vector<pair<int, int>> &routers) 
{
	vector<pair<int,int>> cables;
	int from_row = br;
	int from_col = bc;
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
	return cables;
}


//give cells to connect to backbone
vector<pair<int, int>> mst(Input& input, vector<pair<int, int>> &routers) 
{
	// return dummyMST(input.br, input.bc, routers);
	return prim(input.br, input.bc, routers);
}


