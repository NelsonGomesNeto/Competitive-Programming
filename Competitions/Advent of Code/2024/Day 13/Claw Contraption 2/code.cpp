#include <bits/stdc++.h>
#define DEBUG if (1)
#define DEBUG2 if (1)
#define lli long long int
#define ldouble long double

const int kInfinity = 1e7;
const lli kInputBugDelta = 10000000000000LL;

struct Machine {
  struct Vec {
    lli x, y;
    Vec(const lli x, const lli y) : x(x), y(y) {}
    Vec(std::istringstream& sin) {
      sin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
      sin.ignore(3);
      sin >> x;
      sin.ignore(4);
      sin >> y;
    }
    Vec Add(const Vec& other) const { return Vec{x + other.x, y + other.y}; };
    Vec Mult(const lli k) const { return Vec{x * k, y * k}; };
    bool operator==(const Vec& other) const {
      return x == other.x && y == other.y;
    }
    friend std::ostream& operator<<(std::ostream& out, const Vec& v) {
      return out << "(" << v.x << ", " << v.y << ")";
    }
  };
  const Vec a, b, prize;

  Machine(std::istringstream sin)
      : a(Vec(sin)),
        b(Vec(sin)),
        prize(Vec(sin).Add(Vec{kInputBugDelta, kInputBugDelta})) {}
  Machine(const std::string& input) : Machine(std::istringstream(input)) {}
  friend std::ostream& operator<<(std::ostream& out, const Machine& m) {
    return out << m.a << " | " << m.b << " = " << m.prize;
  }

  lli Solve() const {
    /*
    solve the system
      prize.x = p * a.x + q * b.x
      prize.y = p * a.y + q * b.y
    */
    const ldouble numerator = (prize.y - (ldouble)prize.x / a.x * a.y);
    const ldouble denominator = (b.y - (ldouble)b.x / a.x * a.y);

    const lli b_presses = std::roundl(numerator / denominator);
    const lli a_presses =
        std::roundl((ldouble)prize.x / a.x - (ldouble)b_presses / a.x * b.x);

    const Vec claw = a.Mult(a_presses).Add(b.Mult(b_presses));
    if (claw != prize) return 0;

    return 3 * a_presses + b_presses;
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

    lli ans = 0;
    for (const auto& machine : machines) {
      const lli res = machine.Solve();
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
