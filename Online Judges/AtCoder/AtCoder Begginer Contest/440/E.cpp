#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxN = 50;

struct TestCase {
  int n, k, x;
  std::vector<int> a;
  std::vector<std::tuple<int, int, int>> actions;

  std::vector<lli> sums;
  struct State {
    lli sum;
    std::array<int, kMaxN> picks;
    bool operator<(const State& other) const {
      return sum < other.sum || (sum == other.sum && picks > other.picks);
    }
  };
  void Dijkstra() {
    std::priority_queue<State> pq;
    std::set<std::array<int, kMaxN>> visited;
    std::array<int, kMaxN> hehe;
    std::ranges::fill(hehe, 0);
    hehe[0] = k;
    pq.emplace((lli)k * a[0], hehe);
    while (!pq.empty()) {
      auto [sum, picks] = pq.top();
      pq.pop();

      DEBUG std::println("{} {}", sum, picks);
      if (const bool inserted = visited.insert(picks).second; !inserted)
        continue;
      sums.push_back(sum);
      if ((int)sums.size() == x) break;

      for (const auto& [delta, i, j] : actions) {
        if (picks[i] == 0) continue;
        --picks[i], ++picks[j];
        pq.emplace(sum + delta, picks);
        ++picks[i], --picks[j];
      }
    }
  }

  bool Run() {
    if (!(std::cin >> n >> k >> x)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;
    std::ranges::sort(a, std::greater());

    for (int i = 1; i < n; ++i)
      actions.emplace_back(a[i] - a[i - 1], i - 1, i);
    std::ranges::sort(actions, std::greater());

    Dijkstra();
    std::ranges::sort(sums, std::greater());

    for (const auto sum : sums) std::println("{}", sum);

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
