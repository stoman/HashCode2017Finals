#pragma once
#include "util.cpp"
#include <queue>
#include <vector>
#include <algorithm>
#include <functional>


struct prio {
	reference_wrapper<int> score;
	reference_wrapper<int> walls;
	reference_wrapper<int> doubles;
	int sumdist;
	pair<int, int> coord;
};

bool compare(const prio& a,const prio& b) {

	int ascore = a.score;// * 4 - a.doubles; 
	int bscore = b.score;// * 4 - b.doubles; 

	// score
	if (ascore != bscore) {
		return a.score < b.score;
	}

	if (a.walls != b.walls) {
		return a.walls < b.walls;
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

bool haswalls(Input& input, vector<vector<bool>>& covered, int r, int c) {
	pair<int, int> one = make_pair(0, 1);
	pair<int, int> two = make_pair(1, 0);
	pair<int, int> three = make_pair(-1, 0);
	pair<int, int> four = make_pair(0, -1);
	vector<pair<int, int>> dirs { one, two, three, four };

	for (auto& d : dirs) {
		int newr = r + d.first;
		int newc = c + d.second;
		if (0 < newr && newr < input.h && 0 < newc && newc < input.w && (input.grid.at(newr).at(newc) == '#' || covered.at(newr).at(newc) )) {
			return true;
		}
	}
	return false;
}

void updatewalls(Input& input, vector<vector<int>>& walls, vector<vector<bool>>& covered, int r, int c) {
	pair<int, int> p = make_pair(r, c);
	int sum = 0;
	for (pair<int, int>& cell: connectedcells(input, p)) {
		if (haswalls(input, covered, cell.first, cell.second)) {
			sum++;
		}
	}
	walls.at(r).at(c) = sum;
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

	vector<vector<bool>> covered(input.h, vector<bool>(input.w, false));
	vector<vector<int>> walls(input.h, vector<int>(input.w, 0));
	// init walls
	for (int r = 0; r < input.h; r++) {
		for (int c = 0; c < input.w; c++) {
			updatewalls(input, walls, covered, r, c);
		}
	}

	//compute routers
	vector<prio> pq;//score, cell
	vector<pair<int, int>> routers;

	vector<vector<int>> doubles(input.h, vector<int>(input.w, 0));

	//fill pq with . or - cells with a score
	for(int r = 0; r < input.h; r++) {
		for(int c = 0; c < input.w; c++) {
			if (input.grid[r][c] != '#' && score[r][c] > 0) {
				pair<int, int> coord = make_pair(r, c);
				int sumdist = input.distc.at(r).at(c) + input.distr.at(r).at(c);
				prio p = { score.at(r).at(c), walls.at(r).at(c), doubles.at(r).at(c), sumdist, coord };
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
		// cerr << "PQ places router at " << tup.coord.first << ", " << tup.coord.second <<endl;
		for (pair<int, int>& cell : connectedcells(input, tup.coord)) {
			if (!covered.at(cell.first).at(cell.second)) {
				covered.at(cell.first).at(cell.second) = true;

				for (pair<int, int>& cell2 : connectedcells(input, cell)) {
					score.at(cell2.first).at(cell2.second)--;
					doubles.at(cell2.first).at(cell2.second)++;
				}
			}
		}

		// update walls in 2r
		for (int r = max(0, tup.coord.first - 3 * input.r); r < min(input.h, tup.coord.first + 3 * input.r); r++) {
			for (int c = max(0, tup.coord.second - 3 * input.r); c < min(input.w, tup.coord.second + 3 * input.r); c++) {
				updatewalls(input, walls, covered, r, c);
			}
		}

		make_heap(pq.begin(), pq.end(), compare);
	}

	return routers;
}
