#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define DEBUG3 if (0)
#define lli long long int
#define ldouble long double

/*
WARNING! THIS PROBLEM IS BROKEN!
At https://www.udebug.com/UVa/10272 we get that 7 2 1600 yields "Yes" but if you
try all arrow combinations, you can only get to 1500!
So, we clearly need to bend one of the rules.
*/

const int kMaxN = 500;
const int kInf = 1e9;

std::vector<int> memo_perfect(kMaxN + 1, 0);
int Perfect(const int c) {
  const int c4 = c / 4;
  return (c4 * c4 + 1) * 3;
}
std::vector<int> memo_great(kMaxN + 1, 0);
int Great(const int c) {
  const int c4 = c / 4;
  return (c4 * c4 + 1);
}
void PrecomputeScores() {
  for (int c = 0; c <= kMaxN; ++c) {
    memo_great[c] = Great(c);
    memo_perfect[c] = Perfect(c);
  }
}

struct TestCase {
  int n, k, m;

  int MaximumScore() {
    int score = 0;
    for (int i = 0, c = 0; i < n; ++i) {
      if (c == k) {
        c = 0;
        continue;
      }
      ++c;
      score += Perfect(c);
    }
    return score;
  }

  std::vector<std::vector<int>> memo_max_score;
  void PrecomputeMaxScore() {
    memo_max_score.resize(n + 1, std::vector<int>(k + 1, 0));
    for (int start_c = 0; start_c <= k; ++start_c) {
      for (int i = 0, c = start_c, score = 0; i < n; ++i) {
        if (c == k) {
          c = 0;
          memo_max_score[i + 1][start_c] = score;
          continue;
        }
        ++c;
        score += Perfect(c);
        memo_max_score[i + 1][start_c] = score;
      }
    }
  }
  std::vector<int> memo_min_score;
  void PrecomputeMinScore() {
    memo_min_score.resize(k + 1, 0);
    for (int start_c = 0; start_c <= k; ++start_c) {
      int& score = memo_min_score[start_c];
      for (int c = start_c; c < k; ++c) {
        score += Great(c + 1);
      }
    }
  }

  enum Action { kNothing, kGreat, kPerfect };
  struct State {
    int i, c, score;
    bool done;
    bool operator<(const State& other) const {
      return done < other.done || (done == other.done && score < other.score);
    }
  };
  std::vector<std::vector<std::array<bool, 4>>> visited;
  bool Dijkstra() {
    visited.resize(n,
                   std::vector<std::array<bool, 4>>(
                       k + 1, std::array<bool, 4>{false, false, false, false}));
    // bool& visited_this_state = visited[0][0][0][0];
    std::priority_queue<State> pq;
    pq.emplace(0, 0, 0, false);
    int hehe = 0, min_dist = 1e9;
    bool below = false, above = false;
    while (!pq.empty()) {
      const auto [i, c, score, done] = pq.top();
      pq.pop();

      if (i == n) {
        DEBUG3 std::println("finished {} {} {}", score, m, m - score);
        if (n > 100) {
          if (done && ((score & 1) == (m & 1))) {
            if (score < m) below = true;
            if (score > m) above = true;
            if (below && above) return true;
          }
        }
        if (done && score == m) {
          // DEBUG std::cout << "\t" << seq << "\n";
          return true;
        }
        continue;
      }
      if (score > m) continue;
      if (!done && c + (n - i) < k) continue;
      if (!done && score + memo_min_score[c] > m) continue;
      if (score + memo_max_score[n - i][c] < m) continue;

      if (n > 100) {
        bool& visited_this_state = visited[i][c][(done << 1) | (score & 1)];
        if (visited_this_state) continue;
        visited_this_state = true;
      }

      if (i > hehe || m - score < min_dist) {
        hehe = i;
        min_dist = std::min(min_dist, m - score);
        DEBUG2 std::println("\t{} {} {} {} | {} {}", i, c, score, done,
                            memo_max_score[n - i][c], memo_min_score[c]);
      }

      auto TryAdd = [&](const int new_c, const Action action) {
        const int new_score = score + [new_c, action]() {
          switch (action) {
            case kNothing:
              return 0;
            case kGreat:
              return memo_great[new_c];
            case kPerfect:
            default:
              return memo_perfect[new_c];
          }
        }();
        const int new_i = i + 1;
        const bool new_done = (new_c == k) || done;
        DEBUG3 if (new_i == n && new_done) {
          std::println("here {} {} {}", new_score, m, m - new_score);
        }
        if (new_i == n && new_done && ((new_score & 1) == (m & 1))) {
        } else {
          if (new_score > m) return;
          if (!new_done && new_c + (n - new_i) < k) return;
          if (!new_done && new_score + memo_min_score[new_c] > m) return;
          if (new_score + memo_max_score[n - new_i][new_c] < m) return;
        }
        pq.emplace(new_i, new_c, new_score, new_done);
      };

      if (c + 1 <= k) {
        TryAdd(c + 1, kPerfect);
        TryAdd(c + 1, kGreat);
      }

      TryAdd(0, kNothing);
    }

    DEBUG3 {
      // for (int i = 0; i < n; ++i) {
      //   auto& visits = visited[i][i][false];
      //   auto [min_it, max_it] =
      //       std::minmax_element(visits.begin(), visits.end());
      //   int mini = visits.empty() ? -1 : *min_it,
      //       maxi = visits.empty() ? -1 : *max_it;
      //   std::println("size at i={}, c={}: {} | {} {}", i, i,
      //                visited[i][i][false].size(), mini, maxi);
      // }
    }

    return false;
  }

  bool Run() {
    if (!(std::cin >> n >> k >> m)) return false;

    if (m % 100 != 0) {
      std::cout << "No\n";
      return true;
    }
    m /= 100;

    // The scores alternate between even and odd. So, for n=k=500, it's totaly
    // expected that we can't control the parity of numbers.
    const lli max_score = MaximumScore();
    if (m > max_score) {
      std::cout << "No\n";
      return true;
    }
    DEBUG {
      std::cout << "\t" << max_score << "\n";
      std::fflush(stdout);
    }

    PrecomputeMaxScore();
    PrecomputeMinScore();
    PrecomputeScores();

    const bool ans = Dijkstra();
    std::cout << (ans ? "Yes\n" : "No\n");

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
