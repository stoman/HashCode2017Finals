#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;


struct compare{
  vector<int>& input;

  bool compare(const int a,const int b) const{
    return input[a] < input[b];
    
  }
};

int main() {
  vector<int> myints {10,20,30,5,15};
  vector<int> v;

  for (int i = 0; i < 4; i++) {
    v.push_back(i);
  }

  compare comp;
  comp.input = myints;

  std::make_heap (v.begin(),v.end(), comp);
  std::cout << "initial max heap   : " << v.front() << '\n';

  std::pop_heap (v.begin(),v.end(), comp); v.pop_back();
  std::cout << "max heap after pop : " << v.front() << '\n';

  myints.at(0) = 100;
  std::make_heap (v.begin(),v.end(), comp);
  std::cout << "max heap after change : " << v.front() << '\n';

  std::cout << '\n';

  return 0;
}