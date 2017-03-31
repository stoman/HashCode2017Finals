//call this script like this to have live scores:
//while true; do git pull; make -j grades.html; sleep 15; done;
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "../code/util.cpp"

using namespace std;

//grade one single test case
int gradeFile(ifstream& in, ifstream& ans) {
  //read input
  Input input;
  readInput(input, in);
  
  //read answer
  //TODO read answer

  //compute score
  //TODO compute score

  return -1;
}

//iterate over all test cases
int main() {
  //open data directory
  DIR* datadir = opendir("data");
  if(!datadir) {
    cerr << "can't find data directory" << endl;
    return 1;
  }
  //save result data
  set<string> algorithms, testcases;
  map<pair<string, string>, int> scores;
  map<string, int> maxscores;
  //iterate over all files
  struct dirent* file;
  ifstream in, ans;
  while(0 != (file = readdir(datadir))) {
    string ansname = file->d_name;
    if(ansname.size() > 4 && !ansname.compare(ansname.size() - 4, 4, ".ans")) {
      cerr << "grading file " << ansname << "..." << endl;
      string testcase = ansname.substr(ansname.find_first_of(".") + 1, ansname.find_last_of(".") - ansname.find_first_of(".") - 1);
      testcases.insert(testcase);
      string algorithm = ansname.substr(0, ansname.find_first_of("."));
      algorithms.insert(algorithm);
      in.open("data/" + testcase + ".in");
      ans.open("data/" + ansname);
      scores[make_pair(algorithm, testcase)] = gradeFile(in, ans);
      maxscores[testcase] = max(maxscores[testcase], scores[make_pair(algorithm, testcase)]);
      in.close();
      ans.close();
    }
  }
  //print header
  cout << "<html><head><meta http-equiv=\"refresh\" content=\"15\" >"
          "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/icon?family=Material+Icons\">"
          "<link rel=\"stylesheet\" href=\"https://code.getmdl.io/1.3.0/material.indigo-pink.min.css\">"
          "<script defer src=\"https://code.getmdl.io/1.3.0/material.min.js\">"
          "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0\">"
          "</script></head><body style=\"padding: 3em\">" << endl;
  //print table
  cout << "<table class=\"mdl-data-table mdl-js-data-table mdl-shadow--2dp\" style=\"margin-left: auto; margin-right: auto;\">" << endl << "<thead><tr><th class=\"mdl-data-table__cell--non-numeric mdl-data-table__header--sorted-ascending\">algorithm</th>";
  for(string testcase: testcases) {
    cout << "<th class=\"mdl-data-table__cell--non-numeric\">" << testcase << "</th>";
  }
  cout << "<th class=\"mdl-data-table__cell--non-numeric\">sum</th></tr></thead><tbody>" << endl;
  for(string algorithm: algorithms) {
    int sum = 0;
    cout << "<tr><td class=\"mdl-data-table__cell--non-numeric\">" << algorithm << "</td>";
    for(string testcase: testcases) {
      if(scores.find(make_pair(algorithm, testcase)) != scores.end()) {
        cout << "<td" << (scores[make_pair(algorithm, testcase)] == maxscores[testcase] ? " style=\"font-weight: bold;\"" : "") << ">" << scores[make_pair(algorithm, testcase)] << "</td>";
        sum += scores[make_pair(algorithm, testcase)];
      }
      else {
        cout << "<td>-</td>";
      }
    }
    cout << "<td>" << sum << "</td></tr>" << endl;
  }
  int sum = 0;
  cout << "<tr><td class=\"mdl-data-table__cell--non-numeric\">maximum</td>";
  for(string testcase: testcases) {
    cout << "<td>" << maxscores[testcase] << "</td>";
    sum += maxscores[testcase];
  }
  cout << "<td style=\"font-weight: bold;\">" << sum << "</td></tr>" << endl << "</tbody></table>" << endl;
  //print footer
  cout << "</body></html>" << endl;
}
