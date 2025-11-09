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

std::string GetMinimumAndMaximumSize(const std::vector<std::string>& a) {
  std::ostringstream sout;
  int minimum = std::numeric_limits<int>::max(),
      maximum = std::numeric_limits<int>::min();
  for (const auto& b : a)
    minimum = std::min(minimum, (int)b.size()),
    maximum = std::max(maximum, (int)b.size());
  sout << minimum << " " << maximum;
  return sout.str();
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

void MakeUniqueAndOnlySmalls(std::vector<std::string>& a) {
  int minimum = std::numeric_limits<int>::max();
  for (const auto& b : a) minimum = std::min(minimum, (int)b.size());
  std::vector<std::string> res;
  for (const auto& b : a)
    if (minimum == (int)b.size()) res.push_back(b);
  a = res;
  std::ranges::sort(a);
  a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));
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
    if (IsValid(horizontal_vertical) &&
        vertical_horizontal != horizontal_vertical)
      res.push_back(horizontal_vertical + "A");
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
  return res;
}

struct Problem {
  std::vector<std::string> passwords;
  void Solve() {
    for (std::string line; std::getline(std::cin, line);)
      passwords.push_back(line);
    for (const auto& p : passwords) std::cout << p << "\n";

    int ans = 0;
    for (const auto& p : passwords) {
      std::cout << "-----------------------------\n";
      std::cout << p << "\n";

      std::vector<std::string> targets{p};
      for (int i = 0; i < 4; ++i) {
        std::vector<std::string> nxt;
        for (const auto& t : targets) {
          const auto& nxt_moves = FindShortestPaths(kDirectional, t);
          // const auto& nxt_moves =
          //     FindShortestPaths(i == 0 ? kNumeric : kDirectional, t);
          nxt.insert(nxt.end(), nxt_moves.begin(), nxt_moves.end());
        }
        // MakeUniqueAndOnlySmalls(nxt);
        std::cout << "\t" << i << ": " << nxt.size() << " "
                  << GetMinimumAndMaximumSize(nxt) << "\n";
        std::fflush(stdout);
        targets = nxt;
      }
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
