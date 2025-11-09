#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int GetNumber(const std::string& s) {
  std::string digits;
  for (const char c : s)
    if (std::isdigit(c)) digits.push_back(c);
  std::istringstream sin(digits);
  int number;
  sin >> number;
  return number;
}

struct Vec {
  int i, j;
  Vec Add(const Vec& other) const { return Vec{i + other.i, j + other.j}; }
  Vec Sub(const Vec& other) const { return Vec{i - other.i, j - other.j}; }

  friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
    return out << "(" << v.i << ", " << v.j << ")";
  }
};
Vec Direction(const char c) {
  switch (c) {
    case '^':
      return Vec{-1, 0};
    case 'v':
      return Vec{1, 0};
    case '>':
      return Vec{0, 1};
    case '<':
    default:
      return Vec{0, -1};
      break;
  }
}

struct Keypad {
  std::vector<std::string> map;
  int n, m;
  std::vector<Vec> digit_map;
  Keypad(const std::vector<std::string>& map)
      : map(map), n(map.size()), m(map[0].size()) {
    digit_map.clear();
    digit_map.resize(256, {-1, -1});
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) digit_map[map[i][j]] = Vec{i, j};
  }

  std::vector<std::string> GetPaths(const char s, const char t) const {
    const Vec ts = digit_map[t].Sub(digit_map[s]);

    const std::string updown =
        ts.i != 0 ? std::string(std::abs(ts.i), ts.i > 0 ? 'v' : '^') : "";
    const std::string rightleft =
        ts.j != 0 ? std::string(std::abs(ts.j), ts.j > 0 ? '>' : '<') : "";
    const std::string vertical_horizontal = updown + rightleft;
    const std::string horizontal_vertical = rightleft + updown;

    auto IsValid = [&](const std::string& path) {
      Vec u = digit_map[s];
      for (const char c : path) {
        u = u.Add(Direction(c));
        if (map[u.i][u.j] == '.') return false;
      }
      return true;
    };

    std::vector<std::string> res;
    if (IsValid(vertical_horizontal)) res.push_back(vertical_horizontal + "A");
    if (IsValid(horizontal_vertical)) res.push_back(horizontal_vertical + "A");
    return res;
  }
};
const Keypad kNumeric({"789", "456", "123", ".0A"});
const Keypad kDirectional({".^A", "<v>"});

struct State {
  Vec pos;
  int i, dist;
};
std::vector<std::string> FindShortestPaths(const Keypad& keypad,
                                           const std::string& target) {
  std::queue<std::tuple<char, int, std::string>> q;
  q.emplace('A', 0, "");
  std::vector<std::string> res;
  while (!q.empty()) {
    const auto [c, i, buttons] = q.front();
    q.pop();
    if (i == target.size()) {
      res.push_back(buttons);
      continue;
    }

    for (const auto nxt_buttons : keypad.GetPaths(c, target[i])) {
      q.emplace(target[i], i + 1, buttons + nxt_buttons);
    }
  }
  int minimum_size = std::numeric_limits<int>::max();
  for (const auto& r : res) minimum_size = std::min(minimum_size, (int)r.size());

  std::vector<std::string> ans;
  for (const auto& r : res) if ((int)r.size() == minimum_size) ans.push_back(r);

  return ans;
}

struct Problem {
  std::vector<std::string> passwords;
  void Solve() {
    for (std::string line; std::getline(std::cin, line);)
      passwords.push_back(line);
    for (const auto& p : passwords) std::cout << p << "\n";

    int ans = 0;
    for (const auto& p : passwords) {
      const int number_password = GetNumber(p);

      const std::vector<std::string> i0s =
          FindShortestPaths(kNumeric, p);  // robot0
      std::cout << "\ti0s_size: " << i0s.size() << "\n";
      std::fflush(stdout);
      std::vector<std::string> i1s;
      for (const auto& i0 : i0s) {
        const auto& to_add = FindShortestPaths(kDirectional, i0);
        i1s.insert(i1s.end(), to_add.begin(), to_add.end());
      }
      std::cout << "\ti1s_size: " << i1s.size() << "\n";
      std::fflush(stdout);
      std::vector<std::string> i2s;
      for (const auto& i1 : i1s) {
        const auto& to_add = FindShortestPaths(kDirectional, i1);
        i2s.insert(i2s.end(), to_add.begin(), to_add.end());
      }
      std::cout << "\ti2s_size: " << i2s.size() << "\n";
      std::fflush(stdout);
      int minimum_presses = std::numeric_limits<int>::max();
      for (const auto& i2 : i2s) {
        minimum_presses = std::min(minimum_presses, (int)i2.size());
      }
      // std::cout << p << ": " << i2 << " | " << i1 << " | " << i0 << " | "
      //           << i2.size() << " * " << number_password << "\n";

      std::cout << p << ": " << minimum_presses << " * " << number_password
                << "\n";
      std::fflush(stdout);

      ans += minimum_presses * number_password;
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
