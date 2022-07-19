#include <iostream>
#include <cmath>
#include <ctime>
#include <set>

using namespace std;

void gen() {
  constexpr int k = 200000;
  srand(time(NULL));
  int el = rand() % k;

  set<int> st;
  for (int i = 1; i <= 20; ++i) {
    st.insert(rand() % k + 1);
  }

  cout << st.size() << " " << 20 << "\n";
  for (auto el: st) {
    cout << el << " ";
  }
  cout << "\n";
}

int main() {
  gen();
}

