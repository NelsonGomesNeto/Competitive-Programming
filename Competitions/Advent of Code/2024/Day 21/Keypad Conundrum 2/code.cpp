#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Oh wow, this one made my head spin a lot hahahaha. I thought I wasn't going to
make it pass this one, but it's still an AWESOME problem! And I was able to
solve it \o/.

The most important thing is to understand the recursive nature of this
problem. Which is:
curr = 'A'
for `t` in password:
  for `buttons` in all button combinations from `curr` to `t`:
    *recursively* expand `buttons` as if it were a "password" for another robot
That way, all you gotta do is minimize the total key presses.

At part 1 I quickly coded that non-recursively but struggled to piece the
recursion together hahaha. I even found a formula to find the best button
presses for any pair of buttons (from-to) (I didn't understand that in the day).
But it helped me reduce one complication, build the recusion, add a memoization
and breathe in relief hahahaha.

Now, I was able to understand it at `Exploration()` and remove that hacky thing
from the recursion while still keeping it under `20ms` \o/.
*/

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
  std::vector<std::vector<std::vector<std::string>>> memo;

  Keypad(const std::vector<std::string>& map)
      : map(map),
        n(map.size()),
        m(map[0].size()),
        memo(256, std::vector<std::vector<std::string>>(
                      256, std::vector<std::string>{})) {
    digit_map.clear();
    digit_map.resize(256, {-1, -1});

    std::string buttons;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        digit_map[map[i][j]] = Vec{i, j};
        if (map[i][j] == '.') continue;
        buttons.push_back(map[i][j]);
      }

    // Precalc GetPaths
    auto PrecalcGetPaths = [&](const char s, const char t) {
      std::vector<std::string>& ans = memo[s][t];
      if (!ans.empty()) return ans;

      const Vec ts = digit_map[t].Sub(digit_map[s]);

      const std::string updown =
          ts.i != 0 ? std::string(std::abs(ts.i), ts.i > 0 ? 'v' : '^') : "";
      const std::string rightleft =
          ts.j != 0 ? std::string(std::abs(ts.j), ts.j > 0 ? '>' : '<') : "";

      auto IsValid = [&](const std::string& path) {
        Vec u = digit_map[s];
        for (const char c : path) {
          u = u.Add(Direction(c));
          if (map[u.i][u.j] == '.') return false;
        }
        assert(map[u.i][u.j] == t);
        return true;
      };

      std::vector<std::string> valid_paths;
      for (const auto& path : {updown + rightleft, rightleft + updown}) {
        if (!IsValid(path)) continue;
        valid_paths.push_back(path + 'A');
      }
      MakeUnique(valid_paths);
      return ans = valid_paths;
    };
    for (const char s : buttons) {
      for (const char t : buttons) {
        PrecalcGetPaths(s, t);
      }
    }
  }

  std::vector<std::string> GetPaths(const char s, const char t) const {
    const std::vector<std::string> ans = memo[s][t];
    assert(!ans.empty());
    return ans;
  }
};
const Keypad kNumeric({"789", "456", "123", ".0A"});
const Keypad kDirectional({".^A", "<v>"});

struct Problem {
  std::vector<std::string> passwords;

  const int kRecursionLevel = 26;
  std::vector<std::map<std::string, lli>> memo;
  lli FindMinimumPresses(int i, const std::string& target) {
    if (i == kRecursionLevel) {
      return target.size();
    }
    auto [it, inserted] = memo[i].try_emplace(target, 0);
    if (!inserted) return it->second;

    const Keypad& keypad = i == 0 ? kNumeric : kDirectional;

    lli& ans = it->second;
    char curr = 'A';
    for (const char t : target) {
      lli res = std::numeric_limits<lli>::max();
      for (const auto& path : keypad.GetPaths(curr, t)) {
        res = std::min(res, FindMinimumPresses(i + 1, path));
      }
      ans += res;
      curr = t;
    }
    return ans;
  }

  // [debug] Finds all paths, given a keypad and target.
  std::vector<std::string> FindAllPaths(const Keypad& keypad,
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
    MakeUnique(res);
    return res;
  }
  // [debug] Finds all paths of a given recursion depth
  std::vector<std::string> FindPaths(const std::string& target,
                                     const int max_depth, const int depth = 0) {
    const std::vector<std::string> paths = FindAllPaths(kDirectional, target);
    for (const auto& path : paths) {
      std::println("{}{} {} {}", std::string(depth + 1, '\t'), target,
                   path.size(), path);
    }

    if (depth == max_depth) {
      return paths;
    }
    std::vector<std::string> ans;
    for (const auto& path : paths) {
      std::vector<std::string> res = FindPaths(path, max_depth, depth + 1);
      ans.insert(ans.end(), res.begin(), res.end());
    }
    if (depth == 0) std::println("{}", std::string(20, '-'));
    return ans;
  }
  void Explore() {
    // We can press `v` through `<vA` and `v<A`. But `<vA` is better because
    // then we minimize going back and forth.
    FindPaths("v", 2);
    // `<v` expands to `v<<A>A` (size=6) and `v<` expands to `<vA<A` (size=5).
    // At depth 0, `v<` wins but in the long run: `<v` is still best.
    FindPaths("<v", 1);
    FindPaths("v<", 1);
    // However, if we had to go back to press `A`: then both tie at depth 0 and
    // `<vA` win in the long run.
    FindPaths("<vA", 1);
    FindPaths("v<A", 1);
    // All this to say that having to go back to `A` helps to keep
    // sub-problem optimality. But we still need to test different paths and
    // minimize the long run.
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line);)
      passwords.push_back(line);
    for (const auto& p : passwords) std::cout << p << "\n";

    memo.clear();
    memo.resize(kRecursionLevel, std::map<std::string, lli>{});
    lli ans = 0;
    for (const auto& p : passwords) {
      const lli number_password = GetNumber(p);
      const lli minimum_presses = FindMinimumPresses(/*i=*/0, /*target=*/p);

      std::println("{}: {} * {}", p, minimum_presses, number_password);

      ans += minimum_presses * number_password;
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  DEBUG problem.Explore();
  problem.Solve();

  return 0;
}
