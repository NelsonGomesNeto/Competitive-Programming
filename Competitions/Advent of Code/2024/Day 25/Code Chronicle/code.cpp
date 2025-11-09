#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  struct Schematic {
    const int n, m;
    const std::vector<std::string> mat;
    const std::vector<int> schematic;
    Schematic(const std::vector<std::string>& mat)
        : mat(mat), n(mat.size()), m(mat[0].size()), schematic([&]() {
            std::vector<int> s;
            for (int j = 0; j < m; ++j) {
              int& cnt = s.emplace_back();
              for (int i = 0; i < n; ++i) cnt += mat[i][j] == '#';
              --cnt;
            }
            return s;
          }()) {}
    bool Fits(const Schematic& other) const {
      if (schematic.size() != other.schematic.size()) return false;
      const int target_sum = n - 1;
      for (const auto [a, b] : std::views::zip(schematic, other.schematic)) {
        if (a + b < target_sum) continue;
        return false;
      }
      return true;
    }
    std::string SchematicString() const {
      std::ostringstream sout;
      for (const auto [i, v] : std::views::enumerate(schematic)) {
        if (i) sout << ",";
        sout << v;
      }
      return sout.str();
    }
    friend std::ostream& operator<<(std::ostream& out, const Schematic& s) {
      out << std::format("NxM: {}x{}\n", s.n, s.m);
      for (const auto& line : s.mat) out << line << "\n";
      for (const auto [i, v] : std::views::enumerate(s.schematic)) {
        if (i) out << ",";
        out << v;
      }
      return out;
    }
  };
  std::vector<Schematic> keys, locks;
  void PrintSchematics(const std::vector<Schematic>& schematics) {
    for (const auto& s : schematics) {
      std::cout << s << "\n";
    }
  }

  bool ReadKeysAndLocks() {
    std::vector<std::string> mat;
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      mat.push_back(line);
    }
    if (mat.empty()) return false;
    if (mat[0][0] == '#')
      locks.emplace_back(mat);
    else
      keys.emplace_back(mat);
    return true;
  }

  int TryAll() {
    int ans = 0;
    for (const auto& lock : locks)
      for (const auto& key : keys) {
        const bool fits = key.Fits(lock);
        DEBUG {
          std::cout << "\t" << lock.SchematicString() << "\n";
          std::cout << "\t" << key.SchematicString() << "\n";
          std::cout << std::format("\t\tfits: {}\n", fits);
        }
        ans += fits;
      }
    return ans;
  }

  void Solve() {
    while (ReadKeysAndLocks());

    std::cout << "keys:\n";
    PrintSchematics(keys);
    std::cout << "---------------------\n";
    std::cout << "locks:\n";
    PrintSchematics(locks);
    std::cout << "---------------------\n";

    const int ans = TryAll();
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
