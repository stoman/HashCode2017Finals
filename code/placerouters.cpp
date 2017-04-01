#pragma once
#include "util.cpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

//give a list of routers to place, order by priority in descending order
vector<pair<int, int>> placerouters(Input& input, vector<int>& scores) {
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
	vector<pair<reference_wrapper<int>, pair<int, int>>> pq;//score, cell
	vector<pair<int, int>> routers;
	vector<vector<bool>> covered(input.h, vector<bool>(input.w, false));

	//fill pq with . or - cells with a score
	for(int r = 0; r < input.h; r++) {
		for(int c = 0; c < input.w; c++) {
			if (input.grid[r][c] != '#' && score[r][c] > 0) {
				pair<int, int> coord = make_pair(r, c);
				reference_wrapper<int> ref = score.at(r).at(c);
				pair<reference_wrapper<int>, pair<int, int>> tup = make_pair(ref, coord);
				pq.push_back(tup);
			}
		}
	}
	make_heap(pq.begin(), pq.end());

	//loop until best score 0
	while(!pq.empty() && pq.front().first > 0) {
		//move best cell from `pq` to `routers`
		//update covered, scores, pq
		pair<int, pair<int, int>> tup = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		routers.push_back(tup.second);
		scores.push_back(tup.first);
		for (pair<int, int>& cell : connectedcells(input, tup.second)) {
			if (!covered.at(cell.first).at(cell.second)) {
				covered.at(cell.first).at(cell.second) = true;

				for (pair<int, int>& cell2 : connectedcells(input, cell)) {
					score.at(cell2.first).at(cell2.second)--;
				}
			}
		}
		make_heap(pq.begin(), pq.end());
	}

	return routers;
}
