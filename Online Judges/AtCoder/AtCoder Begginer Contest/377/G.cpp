#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Trie {
  Trie* prv = nullptr;
  std::map<char, Trie> nxt;
  int closest = 1e9;
  Trie() {};
  Trie(Trie* prv) : prv(prv) {}

  Trie* Add(const std::string& s) {
    Trie* curr = this;
    for (int i = 0; i < s.size(); ++i) {
      const char c = s[i];
      if (!curr->nxt.count(c)) curr->nxt[c] = Trie(curr);
      curr = &curr->nxt[c];
    }

    return curr;
  }

  int Bfs(Trie* u) {
    int res = 1e9, d = 0;
    while (u != nullptr) {
      res = std::min(res, d + u->closest);
      u = u->prv, ++d;
    }
    return res;
  }
};

struct TestCase {
  int n;
  std::vector<std::string> s;
  Trie trie;

  bool Run() {
    if (!(std::cin >> n)) return false;
    s.resize(n);
    for (auto& si : s) std::cin >> si;

    trie.closest = 0;
    for (const auto& si : s) {
      const auto it = trie.Add(si);
      const int ans = trie.Bfs(it);
      Trie* u = it;
      int d = 0;
      while (u != nullptr) {
        u->closest = std::min(u->closest, d);
        u = u->prv, ++d;
      }
      std::cout << ans << "\n";
    }

    return true;
  }
};
TestCase test_case;

int main() {
  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
