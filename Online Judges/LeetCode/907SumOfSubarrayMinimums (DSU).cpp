#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

using time_precision = std::chrono::milliseconds;

const int kMaxA = 3e4;
const lli kMod = 1e9 + 7;

struct DSU {
  int size;
  std::vector<int> parents;
  DSU() : size(0) { parents.clear(); }
  DSU(const int sz) : size(sz) { Init(); }
  void Init() { parents.resize(size, -1); }
  int Root(const int u) {
    return parents[u] < 0 ? u : parents[u] = Root(parents[u]);
  }
  void Merge(int u, int v) {
    u = Root(u), v = Root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) std::swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int SetSize(const int u) { return -parents[Root(u)]; }
  bool SameSet(const int u, const int v) { return Root(u) == Root(v); }
};

class Solution {
 public:
  lli subarryCount(const int sz) {
    // 1 -> 1
    // 2 -> 3
    // 3 -> 6
    return sz * (sz + 1) >> 1;
  }
  int sumSubarrayMins(const std::vector<int>& arr) {
    const int n = (int)arr.size();
    std::array<std::vector<int>, kMaxA + 1> positions_by_value;
    for (const auto [i, ai] : arr | std::views::enumerate) {
      positions_by_value[ai].push_back((int)i);
    }

    DSU dsu(n);
    lli ans = 0;
    for (int val = kMaxA; val >= 0; --val) {
      const std::vector<int>& positions = positions_by_value[val];
      if (positions.empty()) continue;

      // left border
      if (const int pos = *positions.begin();
          pos - 1 >= 0 && arr[pos - 1] > val) {
        ans = (ans - val * subarryCount(dsu.SetSize(pos - 1)) % kMod + kMod) %
              kMod;
        dsu.Merge(pos - 1, pos);
      }
      // right border
      if (const int pos = positions.back(); pos + 1 < n && arr[pos + 1] > val) {
        ans = (ans - val * subarryCount(dsu.SetSize(pos + 1)) % kMod + kMod) %
              kMod;
        dsu.Merge(pos, pos + 1);
      }

      // gaps between
      // merge and subtract
      for (const auto [curr, nxt] : positions | std::views::adjacent<2>) {
        if (curr + 1 == nxt) {
          dsu.Merge(curr, nxt);
          continue;
        }
        // min between [curr, nxt] is >= val
        if (const int gap_size = nxt - curr + 1;
            arr[curr + 1] > val && dsu.SetSize(curr + 1) == gap_size - 2) {
          ans =
              (ans - val * subarryCount(dsu.SetSize(curr + 1)) % kMod + kMod) %
              kMod;
          dsu.Merge(curr, curr + 1);
          dsu.Merge(curr, nxt);
        } else {
          if (arr[curr + 1] > val) {
            ans = (ans - val * subarryCount(dsu.SetSize(curr + 1)) % kMod +
                   kMod) %
                  kMod;
            dsu.Merge(curr, curr + 1);
          }
          if (arr[nxt - 1] > val) {
            ans =
                (ans - val * subarryCount(dsu.SetSize(nxt - 1)) % kMod + kMod) %
                kMod;
            dsu.Merge(nxt - 1, nxt);
          }
        }
      }

      // add all groups with `val`
      for (const auto [i, curr] : positions | std::views::enumerate) {
        if (i - 1 >= 0 && dsu.SameSet(positions[i - 1], curr)) continue;
        ans = (ans + val * subarryCount(dsu.SetSize(curr)) % kMod) % kMod;
      }
    }

    return ans;
  }
};

struct TestCase {
  bool Run() {
    std::string line;
    if (!(std::getline(std::cin, line))) return false;
    std::istringstream linein(line);
    std::vector<int> arr;
    for (std::string num; std::getline(linein, num, ' ');) {
      arr.push_back(std::stoi(num));
    }
    const auto start = std::chrono::high_resolution_clock::now();
    const lli ans = Solution().sumSubarrayMins(arr);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    std::println("\ttime: {}", duration);
    std::println("{}", ans);
    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
