#include "util.cpp"
#include "mst.cpp"
#include "connectedcells.cpp"
#include "placerouters.cpp"
#include "runnaive.cpp"

//input/output code
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	srand(time(NULL));

	//read input
	Input input;
	readInput(input, cin);

	//read command line args
	string algorithm = "";
	if(argc > 1) {
		algorithm = argv[1];
	}

	vector<pair<int, int>> routers, backbone;
		
	//solve problem
	cerr << "using algorithm " << algorithm << endl;
	if(algorithm == "naive") {
		runnaive(input, routers, backbone);
	}
	else {
		cerr << "unknown algorithm" << endl;
		return 1;
	}
	
	//print output
	cout << routers.size() << endl;
	for(pair<int, int>& cell: routers) {
		cout << cell.first << " " << cell.second << endl;
	}
	for(pair<int, int>& cell: backbone) {
		cout << cell.first << " " << cell.second << endl;
	}
};
