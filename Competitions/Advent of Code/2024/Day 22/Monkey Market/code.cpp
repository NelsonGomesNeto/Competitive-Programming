#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kSteps = 2000;
const lli kMod = 16777216;

lli Mix(const lli a, const lli b) {
  return a ^ b;
}
lli Prune(const lli x) {
  return x % 16777216;
}
lli Evolve(lli x) {
  x = Prune(Mix(x, x * 64));
  x = Prune(Mix(x, x / 32));
  x = Prune(Mix(x, x * 2048));
  return x;
}
lli NextSecret(lli x, const int steps) {
  for (int i = 0; i < steps; ++i) {
    x = Evolve(x);
  }
  return x;
}

struct Problem {
  std::vector<lli> initial;
  void Solve() {
    for (lli i; std::cin >> i;) {
      initial.push_back(i);
    }

    lli ans = 0;
    for (const lli i : initial) {
      const lli f = NextSecret(i, kSteps);
      std::cout << i << ": " << f << "\n";
      ans += f;
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
