#pragma once
#include "util.cpp"
#include "placerouters.cpp"
#include "mst.cpp"
#include "connectedcells.cpp"

ll score_this_try(Input& input, vector<pair<int, int>>& pqrouters, int n, vector<int>& scores) {
	vector<pair<int, int>> routersused(&pqrouters[0], &pqrouters[n - 1]);
	vector<pair<int, int>> backbone = mst(input, routersused);

	if(backbone.size() * input.pb + n * input.pr > input.b) {
		return -1;
	}
	else {
		ll r = input.b - backbone.size() * input.pb - n * input.pr;
		for(int i = 0; i < n; i++) {
			r += 1000 * scores.at(i);
		}
		return r;
	}
}

void runnaive(Input& input, vector<pair<int, int>>& routers, vector<pair<int, int>>& backbone) {
	//place routers
	cerr << "starting placerouters..." << endl;
	vector<int> scores;
	vector<pair<int, int>> pqrouters = placerouters(input, scores);
	if(pqrouters.size() == 0) return;

	//binary search
	cerr << "binary searching number of routers..." << endl;
	int lo = 1, hi = pqrouters.size();
	while(hi - lo > 1) {
		cerr << "trying interval [" << lo << ", " << hi << "]..." << endl;
		int mid = (hi + lo) / 2;
		ll score_mid = score_this_try(input, pqrouters, mid, scores);
		if(score_mid == -1) {
			hi = mid;
		}
		else if(score_this_try(input, pqrouters, mid+1, scores) < score_mid) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}

	//if hi == lo + 1: which to take?
	int res = lo;
	if(lo + 1 < pqrouters.size() && score_this_try(input, pqrouters, lo+1, scores) > score_this_try(input, pqrouters, lo, scores)) {
		res = lo + 1;
	}
	cerr << "Let's use " << res << " routers, sounds good..." << endl;

	//postprocessing
	vector<vector<int>> countcovered(input.h, vector<int>(input.w, 0));
	vector<bool> routerisused(pqrouters.size(), false);
	for(int i = 0; i < res; i++) {
		routerisused[i] = true;
		for(pair<int, int>& cell: connectedcells(input, pqrouters[i])) {
			countcovered[cell.first][cell.second]++;
		}
	}

	int routertoremove = -1, routertoremovescore = -1;
	int routertoadd= -1, routertoaddscore = -1;
	do {
		//find router to remove
		routertoremove = -1;
		routertoremovescore = -1;
		for(int i = 0; i < pqrouters.size(); i++) {
			if(routerisused[i]) {
				int score = 0;
				for(pair<int, int>& cell: connectedcells(input, pqrouters[i])) {
					if(countcovered[cell.first][cell.second] == 1 && input.grid[cell.first][cell.second] == '.') {
						score++;
					}
				}
				if(routertoremove == -1 || score < routertoremovescore) {
					routertoremove = i;
					routertoremovescore = score;
				}
			}
		}

		//remove it
		routerisused[routertoremove] = false;
		for(pair<int, int>& cell: connectedcells(input, pqrouters[routertoremove])) {
			countcovered[cell.first][cell.second]--;
		}

		//find router to add
		routertoadd= -1;
		routertoaddscore = -1;
		for(int i = 0; i < pqrouters.size(); i++) {
			if(!routerisused[i]) {
				int score = 0;
				for(pair<int, int>& cell: connectedcells(input, pqrouters[i])) {
					if(countcovered[cell.first][cell.second] == 0 && input.grid[cell.first][cell.second] == '.') {
						score++;
					}
				}
				if(routertoadd == -1 || score > routertoaddscore) {
					routertoadd = i;
					routertoaddscore = score;
				}
			}
		}

		//add it
		routerisused[routertoadd] = true;
		for(pair<int, int>& cell: connectedcells(input, pqrouters[routertoadd])) {
			countcovered[cell.first][cell.second]++;
		}

		cerr << "postprocessing improved our already huge score by " << (routertoaddscore - routertoremovescore) << " by removing " << routertoremove << " and adding " << routertoadd << ", its true, believe me" << endl;

		//did we use too much money?
		routers.clear();
		for(int i = 0; i < pqrouters.size(); i++) {
			if(routerisused[i]) {
				routers.push_back(pqrouters[i]);
			}
		}
		backbone = mst(input, routers);
		if(backbone.size() * input.pb + routers.size() * input.pr > input.b) {
			routerisused[routertoadd] = false;
			routerisused[routertoremove] = true;

			routers.clear();
			for(int i = 0; i < pqrouters.size(); i++) {
				if(routerisused[i]) {
					routers.push_back(pqrouters[i]);
				}
			}
			backbone = mst(input, routers);
			cerr << "runnaive done with budget panic" << endl;
			return;
		}
	}
	while(routertoaddscore > routertoremovescore);

	cerr << "runnaive done!" << endl;
}

