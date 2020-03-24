#include <iostream>
#include <map>

using namespace std;

class Obj {
  public:
  Obj() {
    cout << "default ctor\n";
  }
  Obj(const Obj &obj) {
    cout << "copy ctor\n";
  }
  Obj& operator=(int x) {
    cout << "operator= with " << x;
    return *this;
  }
  ~Obj() {
    cout << "dtor\n";
  }


};

int main() {
  map<int, Obj> mp;
  mp[1] = 3;
  mp[1] = 4;
  return 0;

}
