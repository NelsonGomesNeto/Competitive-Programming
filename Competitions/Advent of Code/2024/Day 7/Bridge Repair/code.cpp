#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

struct Equation {
  const lli test_value;
  const std::vector<lli> values;
  const int max_mask;
  std::string operators;

  Equation(std::istringstream sin)
      : test_value([&]() {
          lli a;
          sin >> a;
          return a;
        }()),
        values([&]() {
          sin.ignore(2);
          std::vector<lli> as;
          for (lli a; sin >> a;) {
            as.push_back(a);
          }
          return as;
        }()),
        max_mask(1 << (int)(values.size() - 1)),
        operators(values.size() - 1, '?') {}
  Equation(const std::string& input) : Equation(std::istringstream(input)) {}

  lli Evaluate(const int mask) {
    lli res = values[0];
    for (int i = 0; i < operators.size(); ++i) {
      const bool multiplication = (mask >> i) & 1;
      if (multiplication)
        res *= values[i + 1];
      else
        res += values[i + 1];
    }
    return res;
  }
  bool Solve() {
    for (int mask = 0; mask < max_mask; ++mask) {
      lli res = Evaluate(mask);
      if (res != test_value) continue;

      for (int i = 0; i < operators.size(); ++i) {
        operators[i] = mask & (1 << i) ? '*' : '+';
      }
      return true;
    }
    return false;
  }

  friend std::ostream& operator<<(std::ostream& out, const Equation& e) {
    out << e.test_value << ":";
    for (int i = 0; i < e.values.size(); ++i) {
      out << " " << e.values[i];
      if (i < e.operators.size()) out << " " << e.operators[i];
    }

    return out;
  }
};

struct Problem {
  std::vector<Equation> equations;
  void Solve() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      equations.emplace_back(line);
    }

    lli ans = 0;
    for (Equation& equation : equations) {
      bool solvable = equation.Solve();
      if (!solvable) continue;

      DEBUG std::cout << equation << "\n";
      ans += equation.test_value;
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
