#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main() {
  vector<int> myints {10,20,30,5,15};
  vector<reference_wrapper<int>> v;

  for (int i = 0; i < 5; i++) {
    v.push_back(myints.at(i));
  }

  std::make_heap (v.begin(),v.end());
  std::cout << "initial max heap   : " << v.front() << '\n';

  std::pop_heap (v.begin(),v.end()); v.pop_back();
  std::cout << "max heap after pop : " << v.front() << '\n';


  myints.at(0) = 100;
  std::make_heap (v.begin(),v.end());
  std::cout << "max heap after change : " << v.front() << '\n';

  std::cout << '\n';

  return 0;
}