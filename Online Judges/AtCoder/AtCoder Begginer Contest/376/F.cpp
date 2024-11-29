#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::vector<std::pair<char, int>> queries;

  int AdjustPos(const int pos) {
    if (pos > n) return pos - n;
    if (pos < 1) return n - pos;
    return pos;
  }
  int DirectDist(const int delta, const int from, const int to) {
    if (delta == -1) {
      if (from <= to) {
        return (from - 1) + (n - to) + 1;
      } else {
        return from - to;
      }
    } else {
      if (from <= to) {
        return to - from;
      } else {
        return (n - from) + (to - 1) + 1;
      }
    }
  }
  bool WillHit(const int delta, const int from, const int to, const int block) {
    return DirectDist(delta, from, block) <= DirectDist(delta, from, to);
    // bool between = from <= block && to <= block;
    // DEBUG std::cout << "\t\t" << delta << " " << from << " " << to << " " <<
    // block
    //           << " | " << between << "\n";
    // return (between && delta == 1) ||
    //        (!between && delta == -1);
  }
  // Returns min operations, new block position
  std::pair<int, int> GetMinDist(const int delta, const int from, const int to,
                                 const int block) {
    int operations = DirectDist(delta, from, to), new_block_pos = block;
    if (WillHit(delta, from, to, block)) {
      new_block_pos = AdjustPos(to + delta);
      const int move_block_operations = DirectDist(delta, block, new_block_pos);
      DEBUG std::cout << "\tMove Block " << block << " " << new_block_pos << " "
                      << move_block_operations << "\n";
      operations += move_block_operations;
    }
    return std::make_pair(operations, new_block_pos);
  }
  std::vector<std::vector<std::unordered_map<int, int>>> memo;
  int Solve(const int i = 0, const int l = 1, const int r = 2) {
    if (i == q) return 0;
    if (memo[i][l].count(r)) return memo[i][l][r];
    int& ans = memo[i][l][r];

    const auto [h, t] = queries[i];
    ans = std::numeric_limits<int>::max();
    if (h == 'L') {
      auto Eval = [&](const int delta) {
        auto [operations, new_r] = GetMinDist(delta, l, t, r);
        DEBUG std::cout << "L_eval: " << delta << " " << operations << " "
                        << new_r << "\n";
        return Solve(i + 1, t, new_r) + operations;
      };
      ans = std::min(Eval(-1), Eval(1));
    } else {
      auto Eval = [&](const int delta) {
        auto [operations, new_l] = GetMinDist(delta, r, t, l);
        DEBUG std::cout << "R_eval: " << delta << " " << operations << " "
                        << new_l << "\n";
        return Solve(i + 1, new_l, t) + operations;
      };
      ans = std::min(Eval(-1), Eval(1));
    }

    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    queries.resize(q);
    for (auto& [h, t] : queries) std::cin >> h >> t;

    memo.resize(q, std::vector<std::unordered_map<int, int>>(n + 1));
    const int ans = Solve();
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Run());
  return 0;
}
