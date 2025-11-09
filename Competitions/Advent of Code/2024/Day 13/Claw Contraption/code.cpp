#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kInfinity = 1e7;

struct Machine {
  struct Vec {
    int x, y;
    Vec(const int x, const int y) : x(x), y(y) {}
    Vec(std::istringstream& sin) {
      sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
      sin.ignore(3);
      sin >> x;
      sin.ignore(4);
      sin >> y;
    }
    Vec Add(const Vec& other) const { return Vec{x + other.x, y + other.y}; };
    bool operator==(const Vec& other) const {
      return x == other.x && y == other.y;
    }
    friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
      return out << "(" << v.x << ", " << v.y << ")";
    }
  };
  const Vec a, b, prize;

  Machine(std::istringstream sin) : a(Vec(sin)), b(Vec(sin)), prize(Vec(sin)) {}
  Machine(const std::string& input) : Machine(std::istringstream(input)) {}
  friend std::ostream& operator<<(std::ostream& out, const Machine& m) {
    return out << m.a << " | " << m.b << " = " << m.prize;
  }

  mutable std::vector<std::unordered_map<int, int>> memo;
  int Solve(const Vec curr) const {
    if (curr.x > prize.x || curr.y > prize.y) return kInfinity;
    if (curr == prize) return 0;

    auto [ans, inserted] = memo[curr.x].try_emplace(curr.y, kInfinity);
    if (!inserted) return ans->second;

    return ans->second =
               std::min(Solve(curr.Add(a)) + 3, Solve(curr.Add(b)) + 1);
  }
  int Solve() const {
    memo.resize(prize.x + 1, std::unordered_map<int, int>{});
    const int ans = Solve(Vec{0, 0});
    if (ans >= kInfinity) return 0;
    return ans;
  }
};
struct Problem {
  std::vector<Machine> machines;

  bool ReadMachine() {
    std::string input;
    if (!(std::getline(std::cin, input))) return false;
    for (int i = 0; i < 2; ++i) {
      input.push_back('\n');
      std::string line;
      std::getline(std::cin, line);
      input += line;
    }
    machines.emplace_back(input);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  }

  void Solve() {
    while (ReadMachine());

    int ans = 0;
    for (const auto& machine : machines) {
      const int res = machine.Solve();
      DEBUG std::cout << "\t" << machine << " || res: " << res << "\n";
      ans += res;
    }
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
