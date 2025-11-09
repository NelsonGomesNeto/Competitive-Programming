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
  int ManhattanDist(const Vec& other) const {
    return std::abs(i - other.i) + std::abs(j - other.j);
  }

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

void MakeUnique(std::vector<std::string>& a) {
  std::ranges::sort(a);
  a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));
}

struct Keypad {
  std::vector<std::string> map;
  int n, m;
  std::vector<Vec> digit_map;
  mutable std::vector<std::vector<std::string>> memo;

  Keypad(const std::vector<std::string>& map)
      : map(map),
        n(map.size()),
        m(map[0].size()),
        memo(256, std::vector<std::string>(256, "")) {
    digit_map.clear();
    digit_map.resize(256, {-1, -1});
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) digit_map[map[i][j]] = Vec{i, j};
  }

  int GetDistSum(const std::string& path) const {
    int dist_sum = 0;
    for (int i = 1; i < path.size(); ++i)
      dist_sum += digit_map[path[i]].ManhattanDist(digit_map[path[i - 1]]);
    return dist_sum;
  }

  std::string GetPath(const char s, const char t) const {
    std::string& ans = memo[s][t];
    if (!ans.empty()) return ans;

    const Vec ts = digit_map[t].Sub(digit_map[s]);

    const std::string updown =
        ts.i != 0 ? std::string(std::abs(ts.i), ts.i > 0 ? 'v' : '^') : "";
    const std::string rightleft =
        ts.j != 0 ? std::string(std::abs(ts.j), ts.j > 0 ? '>' : '<') : "";
    const std::string vertical_horizontal = updown + rightleft;
    const std::string horizontal_vertical = rightleft + updown;
    std::vector<std::pair<int, std::string>> to_try{
        {ts.j > 0 ? 0 : 1, vertical_horizontal},
        {ts.j > 0 ? 1 : 0, horizontal_vertical}};
    std::ranges::sort(to_try);

    auto IsValid = [&](const std::string& path) {
      Vec u = digit_map[s];
      for (const char c : path) {
        u = u.Add(Direction(c));
        if (map[u.i][u.j] == '.') return false;
      }
      assert(map[u.i][u.j] == t);
      return true;
    };

    for (const auto [_, path] : to_try) {
      if (IsValid(path)) return ans = path + 'A';
    }
    assert(false);
    return "";
  }
};
const Keypad kNumeric({"789", "456", "123", ".0A"});
const Keypad kDirectional({".^A", "<v>"});

std::string FindShortestPath(const Keypad& keypad, const std::string& target) {
  std::string res = "";
  char curr = 'A';
  for (const char t : target) {
    res.append(keypad.GetPath(curr, t));
    curr = t;
  }
  return res;
}

struct Problem {
  std::vector<std::string> passwords;
  void Solve() {
    for (std::string line; std::getline(std::cin, line);)
      passwords.push_back(line);
    for (const auto& p : passwords) std::cout << p << "\n";

    lli ans = 0;
    for (const auto& p : passwords) {
      const lli number_password = GetNumber(p);

      std::string target = p;
      for (int i = 0; i < 3; ++i) {
        std::string nxt =
            FindShortestPath(i == 0 ? kNumeric : kDirectional, target);
        target = nxt;
      }
      lli minimum_presses = target.size();

      // std::cout << "\t" << i0 << " | " << i1 << " | " << i2 << "\n";

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
