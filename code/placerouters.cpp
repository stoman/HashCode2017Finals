#pragma once
#include "util.cpp"
#include <queue>
#include <vector>

//give a list of routers to place, order by priority in descending order
vector<pair<int, int>> placerouters(Input& input) {
	//compute scores
	vector<vector<int>> score(input.h, vector<int>(input.w, 0));
	for(int r = 0; r < input.h; r++) {
		for(int c = 0; c < input.w; c++) {
			pair<int, int> p = make_pair(r, c);
			for(pair<int, int>& cell: connectedcells(input, p)) {
				if(input.grid[cell.first][cell.second] == '.') {
					score[r][c]++;
				}
			}
		}
	}

	//compute routers
	priority_queue<pair<int, pair<int, int>>> pq;//score, cell
	vector<pair<int, int>> routers;
	vector<vector<bool>> covered(input.h, vector<bool>(input.w, false));

	//fill pq with . cells

	//loop until best score 0
		//move best cell from `pq` to `routers`
		//update, covered, scores, pq

	return routers;
}
