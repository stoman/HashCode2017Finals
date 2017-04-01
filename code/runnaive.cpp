#pragma once
#include "util.cpp"
#include "placerouters.cpp"
#include "mst.cpp"


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

	//TODO if hi == lo + 1: which to take?
	int res = lo;
	if(lo + 1 <= pqrouters.size() && score_this_try(input, pqrouters, lo+1, scores) > score_this_try(input, pqrouters, lo, scores)) {
		res = lo + 1;
	}
	cerr << "Let's use " << res << " routers, sounds good..." << endl;

	//return
	for(int i = 0; i < res; i++) {
		routers.push_back(pqrouters[i]);
	}
	backbone = mst(input, routers);
	cerr << "runnaive done!" << endl;
}

