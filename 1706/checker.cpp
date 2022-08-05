#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    return 42;
  }

  ifstream file(argv[1]);
  vector<int> values1;
  int t;
  //cout << argv[1] << endl;
  while (!file.eof()) {
    file >> t;
    if (file.eof()) break;
    values1.push_back(t);
  }

  file = ifstream{argv[2]};
  //cout << argv[2] << endl;
  vector<int> values2;
  while (!file.eof()) {
    file >> t;
    if (file.eof()) break;
    values2.push_back(t);
  }
  //cout << values1.size() << " " << values2.size() << endl;

  int idx = 0;
  while (idx < values1.size() && values1[idx] == values2[idx]) {
    ++idx;
  }
  if (idx == values1.size()) {
    return 0;
  } else {
    cout << "query: " << idx + 1 << ", expected: " << values2[idx] << " got: " << values1[idx] << "\n";
    return 1;
  }
}
