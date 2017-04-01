#pragma once
#include "util.cpp"
#include "placerouters.cpp"
#include "mst.cpp"

void runnaive(Input& input, vector<pair<int, int>>& routers, vector<pair<int, int>>& backbone) {
	//place routers
	cerr << "starting placerouters..." << endl;
	vector<pair<int, int>> pqrouters = placerouters(input);

	//binary search
	cerr << "binary saearching number of routers..." << endl;
	int lo = 1, hi = routers.size();
	while(hi - lo > 1) {
		int mid = (hi + lo) / 2;
		vector<pair<int, int>> routersused(&pqrouters[0], &pqrouters[mid - 1]);
		backbone = mst(input, routersused);
		if(backbone.size() * input.pb + mid * input.pr <= input.b) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}

	//TODO if hi == lo + 1: which to take?
	int res = lo;

	//return
	for(int i = 0; i < res; i++) {
		routers.push_back(pqrouters[i]);
	}
	backbone = mst(input, routers);
	cerr << "runnaive done!" << endl;
}
