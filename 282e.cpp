// sausage maximization

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <queue>

using namespace std;

const int R = 2;

class TrieNode {
public:
  TrieNode *children[2] = {};
};

class Trie {
  TrieNode *root;
  void free_nodes() {
    queue<TrieNode*> q;
    q.push(root);

    while (!q.empty()) {
      auto cur_node = q.front();
      q.pop();
      for (int i = 0; i < R; ++i) {
        if (cur_node->children[i]) {
          q.push(cur_node->children[i]);
        }
      }
      delete cur_node;
    }
  }
public:
  Trie() {
    root = new TrieNode();
  }
  void insert(const vector<int> &v) {
    auto cur_node = root;
    for (int i = 0; i < v.size(); ++i) {
      if (!cur_node->children[v[i]]) {
        cur_node->children[v[i]] = new TrieNode();
      }
      cur_node = cur_node->children[v[i]];
    }
  }

  vector<int> max_xor(const vector<int> &v) {
    auto cur_node = root;
    vector<int> ans;
    for (auto &cur_bit: v) {
      if (cur_node->children[!cur_bit]) {
        cur_node = cur_node->children[!cur_bit];
        ans.push_back(1);
      } else {
        cur_node = cur_node->children[cur_bit];
        ans.push_back(0);
      }
    }
    return ans;
  }

  ~Trie() {
    free_nodes();
  }
};

vector<int> get_bits(long long x) {
  vector<int> ans;
  for (int i = 62; i >= 0; --i) {
    ans.push_back((x & (1ll << i)) != 0);
  }
  return ans;
}

long long bits_to_x(const vector<int> &v) {
  long long ans = 0;
  for (int i = 0; i < v.size(); ++i) {
    ans += (1ll << (62 - i)) * v[i];
  }
  return ans;
}

int main() {
  //freopen("output.txt", "w", stdout);
  int n;
  vector<long long> v;
  Trie trie;

  cin >> n;
  v.resize(n);

  long long pref_xor = 0, suff_xor = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    pref_xor ^= v[i];
  }

  long long ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    trie.insert(get_bits(suff_xor));
    ans = max(ans, bits_to_x(trie.max_xor(get_bits(pref_xor))));
    pref_xor ^= v[i];
    suff_xor ^= v[i];
  }

  trie.insert(get_bits(suff_xor));
  ans = max(ans, bits_to_x(trie.max_xor(get_bits(pref_xor))));
  cout << ans << "\n";
  return 0;
}
