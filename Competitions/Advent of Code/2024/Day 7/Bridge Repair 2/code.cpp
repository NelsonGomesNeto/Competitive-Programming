#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const std::string kOperators = {'+', '*', '|'};

struct Equation {
  const lli test_value;
  const std::vector<lli> values;
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
        operators(values.size() - 1, '?') {}
  Equation(const std::string& input) : Equation(std::istringstream(input)) {}

  lli Evaluate(const lli a, const lli b, const char op) {
    switch (op) {
      case '+':
        return a + b;
      case '*':
        return a * b;
      case '|':
      default: {
        auto GetDigits = [&](lli x) {
          int digits = x == 0;
          while (x) ++digits, x /= 10;
          return digits;
        };
        const int digits = GetDigits(b);
        const lli shift = (lli)std::pow(10, digits);
        lli res = a * shift + b;

        // lli res2;
        // std::istringstream sin(std::to_string(a) + std::to_string(b));
        // sin >> res2;
        // if (res != res2) {
        //   std::cout << a << " " << op << " " << b << "\n";
        //   std::cout << res << " " << res2 << "\n";
        //   std::fflush(stdout);
        // }
        return res;
      }
    }
  }
  bool Solve(int i, lli curr) {
    if (i == values.size()) return curr == test_value;

    for (const char op : kOperators) {
      operators[i - 1] = op;
      if (Solve(i + 1, Evaluate(curr, values[i], op))) return true;
    }
    operators[i - 1] = '?';
    return false;
  }
  bool Solve() { return Solve(1, values[0]); }

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
