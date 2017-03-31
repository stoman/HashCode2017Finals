#include "../code/util.cpp"
#include <iostream>
#include <fstream>
#include <set>

//input/output code
int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    srand(time(NULL));

    //read input
    Input input;
    readInput(input, cin);

    //read command line args
    char* ansfile = argv[1];
    ifstream ans;
    ans.open(ansfile);

    // read number
    // int da;
    // ans >> da;

    // cerr << "done" << endl;
    ans.close();
    return 0;
};
