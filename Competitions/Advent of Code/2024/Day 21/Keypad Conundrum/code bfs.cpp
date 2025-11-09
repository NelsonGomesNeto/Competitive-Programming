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

  std::string GetPath(const char s, const char t) const {
    const Vec ts = digit_map[t].Sub(digit_map[s]);

    std::string updown =
        ts.i != 0 ? std::string(std::abs(ts.i), ts.i > 0 ? 'v' : '^') : "";
    std::string rightleft =
        ts.j != 0 ? std::string(std::abs(ts.j), ts.j > 0 ? '>' : '<') : "";
    std::string vertical_horizontal = updown + rightleft;
    std::string horizontal_vertical = rightleft + updown;
    // std::swap(vertical_horizontal, horizontal_vertical);

    Vec u = digit_map[s];
    bool prohibited = false;
    for (const char c : vertical_horizontal) {
      u = u.Add(Direction(c));
      if (map[u.i][u.j] == '.') prohibited = true;
    }
    assert(map[u.i][u.j] == t);

    std::string res = prohibited ? horizontal_vertical : vertical_horizontal;
    res.push_back('A');

    return res;
  }
};
const Keypad kNumeric({"789", "456", "123", ".0A"});
const Keypad kDirectional({".^A", "<v>"});

struct State {
  Vec pos;
  int i, dist;
};
std::string FindShortestPath(const Keypad& keypad, const std::string& target) {
  std::string res;
  char curr = 'A';
  for (const char t : target) {
    res.append(keypad.GetPath(curr, t));
    curr = t;
  }
  return res;
  // std::queue<State> q;
  // q.emplace(keypad.start_pos, 0, 0);
  // while (!q.empty()) {
  //   State curr = q.front();
  //   q.pop();
  //   const auto [pos, i, dist] = curr;

  // }
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

      const std::string i0 = FindShortestPath(kNumeric, p);       // robot0
      const std::string i1 = FindShortestPath(kDirectional, i0);  // robot1
      const std::string i2 = FindShortestPath(kDirectional, i1);  // robot2
      std::cout << p << ": " << i2 << " | " << i1 << " | " << i0 << " | "
                << i2.size() << " * " << number_password << "\n";

      ans += (int)i2.size() * number_password;
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
