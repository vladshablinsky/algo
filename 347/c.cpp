#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <cstdlib>
#include <queue>

using namespace std;

struct Node {
  char val;
  int depth;
  bool used;
  Node *father;
  Node *sons[10];
};

void add_son(Node* node, int i) {
  node->sons[i] = new Node();
  node->sons[i]->depth = node->depth + 1;
  node->sons[i]->father = node;
  node->sons[i]->val = i + '0';
}

struct Trie {
  Node *root;
  Trie() {
    root = new Node();
    root->val = '#';
  }

  string retrieve(Node* cur) {
    string ans;
    while (cur->val != '#') {
      ans.push_back(cur->val);
      cur = cur->father;
    }
    return ans;
  }

  void add_s(string s, bool print_flag=false) {
    Node *cur_node = root;
    for (int i = s.length() - 1; i >= 0; --i) {
      char cur_c = s[i];
      if (cur_node->sons[cur_c - '0'] == NULL) {
        add_son(cur_node, cur_c - '0');
        cur_node = cur_node->sons[cur_c - '0'];
        //if (print_flag) {
          //cout << "ADD ON " << cur_c << endl;
        //}
      } else {
        //if (print_flag) {
          //cout << "NEXT ON " << cur_c << endl;
        //}
        cur_node = cur_node->sons[cur_c - '0'];
      }
    }



    if (cur_node->used) {
      queue<Node*> q;
      q.push(cur_node);

      int ans_depth = 1e9;
      int ans_num = 1e9;
      Node* ans_node = NULL;
      int char_to_add;

      while (!q.empty()) {
        Node* cur = q.front();
        bool found = false;
        q.pop();

        //if (print_flag) {
          //cout << "CUR IS " << cur->val << endl;
        //}

        if (cur->depth >= ans_depth) {
          add_son(ans_node, char_to_add - '0');
          ans_node->sons[char_to_add - '0']->used = true;
          if (print_flag) {
            printf("%d\n", ans_num);
            //cout << "PRINTING ANSWER...\n";
          }
          return;
        }

        for (int i = 1; i < 10; ++i) {
          if (cur->sons[i] == NULL) {
            long long num = atol((char(i + '0') + retrieve(cur)).c_str());
            //if (print_flag) {
              //cout << " NUM IS " << num << endl;
            //}
            if (num < ans_num) {
              ans_num = num;
              ans_node = cur;
              ans_depth = cur->depth + 1;
              char_to_add = i + '0';
            }
            found = true;
            break;
          }
        }

        if (found) {
          continue;
        }

        if (cur->sons[0] == NULL) {
          add_son(cur, 0);
        }

        for (int i = 0; i < 10; ++i) {
          q.push(cur->sons[i]);
        }
      }
      add_son(ans_node, char_to_add - '0');
      ans_node->sons[char_to_add - '0']->used = true;
      if (print_flag) {
        //cout << "PRINTING ANSWER...\n";
        printf("%d\n", ans_num);
      }
      return;
    } else if (print_flag) {
      //cout << "IN ELSE..." <<endl;
      cout << retrieve(cur_node) << "\n";
    }
    cur_node->used = true;
  }
};

set<int> st;
Trie *t = new Trie();
const int FST = 1989;

void prepare() {
  for (int i = 1; i < FST; ++i) {
    t->add_s(to_string(i));
  }
  t->add_s("0");
  t->add_s("00");
  t->add_s("000");
}

int main() {
  prepare();

  //cout << "AFTER PREPARE" << endl;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    s.erase(0, 4);
    t->add_s(s, true);
  }
  return 0;
}
