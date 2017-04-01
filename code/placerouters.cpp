#pragma once
#include "util.cpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>

struct prio {
	reference_wrapper<int> score;
	int sumdist;
	pair<int, int> coord;
};

bool compare(const prio& a,const prio& b) {

	// score
	if (a.score != b.score) {
		return a.score < b.score;
	}

	if (a.sumdist != b.sumdist) {
		return a.sumdist > b.sumdist;
	}

	// x
	if (a.coord.first != b.coord.first) {
		return a.coord.first > b.coord.first;
	}

    return a.coord.second > b.coord.second;
}

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
	vector<prio> pq;//score, cell
	vector<pair<int, int>> routers;
	vector<vector<bool>> covered(input.h, vector<bool>(input.w, false));

	//fill pq with . or - cells with a score
	for(int r = 0; r < input.h; r++) {
		for(int c = 0; c < input.w; c++) {
			if (input.grid[r][c] != '#' && score[r][c] > 0) {
				pair<int, int> coord = make_pair(r, c);
				int sumdist = input.distc.at(r).at(c) + input.distr.at(r).at(c);
				prio p = { score.at(r).at(c), sumdist, coord };
				pq.push_back(p);
			}
		}
	}
	make_heap(pq.begin(), pq.end(), compare);

	//loop until best score 0
	while(!pq.empty() && pq.front().score > 0) {
		//move best cell from `pq` to `routers`
		//update covered, scores, pq
		prio tup = pq.front();
		pop_heap(pq.begin(), pq.end(), compare);
		pq.pop_back();

		routers.push_back(tup.coord);
		scores.push_back(tup.score);
		for (pair<int, int>& cell : connectedcells(input, tup.coord)) {
			if (!covered.at(cell.first).at(cell.second)) {
				covered.at(cell.first).at(cell.second) = true;

				for (pair<int, int>& cell2 : connectedcells(input, cell)) {
					score.at(cell2.first).at(cell2.second)--;
				}
			}
		}
		make_heap(pq.begin(), pq.end(), compare);
	}

	return routers;
}
