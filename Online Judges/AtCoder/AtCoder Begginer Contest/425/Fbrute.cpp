#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

size_t hash_combine(const size_t a, const size_t b) {
  return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
}

int N;
std::string T;
struct TestCase {
  std::string unique_letters;
  std::vector<int> total_cnt;

  bool IsSubsequence(const std::string& s) {
    for (int i = 0, j = 0; j < (int)s.size(); ++j) {
      while (i < (int)T.size() && T[i] != s[j]) ++i;
      if (i == (int)T.size()) return false;
    }
    return true;
  }

  struct Way {
    // replace this by a single string? nope, still too slow.
    std::string moves;
    // int last_size, last_pos;
    size_t hash;
    const std::string& LastString() const { return moves; }
    const int LastSize() const { return moves.size(); }
    Way NewMove(const std::string& move) const {
      // return {moves + move, (int)move.size(), (int)moves.size(),
      //         hash_combine(hash, std::hash<std::string>{}(move))};
      return {move, hash_combine(hash, std::hash<std::string>{}(move))};
    }
    bool operator<(const Way& other) const {
      // return last_size < other.last_size ||
      //        (last_size == other.last_size && moves < other.moves);
      return LastSize() < other.LastSize() ||
             (LastSize() == other.LastSize() && moves < other.moves) ||
             (LastSize() == other.LastSize() && moves == other.moves &&
              hash < other.hash);
    }
    bool operator>(const Way& other) const {
      // return last_size > other.last_size ||
      //        (last_size == other.last_size && moves < other.moves);
      return LastSize() > other.LastSize() ||
             (LastSize() == other.LastSize() && moves < other.moves) ||
             (LastSize() == other.LastSize() && moves == other.moves &&
              hash < other.hash);
    }
  };
  void PrintWays(const std::set<Way>& ways) {
    for (const auto& wi : ways) {
      std::cout << wi.hash << " " << wi.moves << "\n";
    }
  }
  void PrintWays(const std::set<Way, std::greater<Way>>& ways) {
    for (const auto& wi : ways) {
      std::cout << wi.hash << " " << wi.moves << "\n";
      std::cout << "\n";
    }
  }
  std::set<Way> AddBrute(const int target) {
    std::set<Way> ways;
    auto TryAdd = [&](const Way& w, const std::string& new_s) {
      if (!IsSubsequence(new_s)) return;
      ways.emplace(w.NewMove(new_s));
    };
    ways.emplace("", 0);
    for (auto it = ways.begin(); it != ways.end();) {
      if (it->LastSize() == target) break;
      const auto& wi = *it;
      // const auto& s = wi.moves.substr(wi.last_pos);
      const auto& s = wi.LastString();
      std::vector<int> cnt(26, 0);
      for (const auto si : s) ++cnt[si - 'a'];
      for (const auto c : unique_letters) {
        if (cnt[c - 'a'] == total_cnt[c]) continue;

        // Check if the new string is a subsequence of T
        TryAdd(wi, c + s);
        for (int i = 1; i < (int)s.size(); ++i) {
          TryAdd(wi, s.substr(0, i) + c + s.substr(i));
        }
        TryAdd(wi, s + c);
      }
      DEBUG {
        PrintWays(ways);
        std::cout << "--------\n";
      }
      ways.erase(it);
      it = ways.begin();
    }
    return ways;
  }
  std::set<Way, std::greater<Way>> RemoveBrute(const int target) {
    std::set<Way, std::greater<Way>> ways;
    auto TryAdd = [&](const Way& w, const std::string& new_s) {
      if (!IsSubsequence(new_s)) return;
      ways.emplace(w.NewMove(new_s));
    };
    ways.emplace(T, std::hash<std::string>{}(T));
    for (auto it = ways.begin(); it != ways.end();) {
      if (it->LastSize() == target) break;
      const auto& wi = *it;
      // const auto& s = wi.moves.substr(wi.last_pos);
      const auto& s = wi.LastString();
      // Check if the new string is a subsequence of T
      TryAdd(wi, s.substr(1));
      for (int i = 1; i + 1 < (int)s.size(); ++i) {
        // skip i
        TryAdd(wi, s.substr(0, i) + s.substr(i + 1));
      }
      TryAdd(wi, s.substr(0, (int)s.size() - 1));
      DEBUG {
        PrintWays(ways);
        std::cout << "--------\n";
      }
      ways.erase(it);
      it = ways.begin();
    }
    return ways;
  }

  bool Run() {
    if (!(std::cin >> N >> T)) return false;
    if (N == 22) return false;

    if (N == 1) {
      std::cout << "1\n";
      return true;
    }

    total_cnt.resize(256, 0);
    for (const auto ti : T) ++total_cnt[ti];
    for (char c = 'a'; c <= 'z'; ++c) {
      if (total_cnt[c] == 0) continue;
      unique_letters.push_back(c);
    }
    const int mid = N >> 1;
    // This brute is too much, I need to find all subsequences of size `mid`
    // and then count the number of ways to get to that subsequences through
    // addition and removal.
    const std::set<Way> add_ways = AddBrute(mid);
    const std::set<Way, std::greater<Way>> remove_ways = RemoveBrute(mid);
    // PrintWays(add_ways);
    // PrintWays(remove_ways);
    std::map<std::string, int> add_cnt, remove_cnt;
    for (const auto& wi : add_ways) {
      auto [it, _] = add_cnt.emplace(wi.LastString(), 0);
      ++it->second;
    }
    for (const auto& wi : remove_ways) {
      auto [it, _] = remove_cnt.emplace(wi.LastString(), 0);
      ++it->second;
    }

    lli ans = 0;
    for (const auto& [s, cnt] : add_cnt) {
      auto it = remove_cnt.find(s);
      if (it == remove_cnt.end()) continue;
      ans += cnt * it->second;
    }
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

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
