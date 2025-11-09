#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kSteps = 2000;
const lli kMod = 16777216;
const int kSequenceSize = 4;

lli Mix(const lli a, const lli b) { return a ^ b; }
lli Prune(const lli x) { return x % 16777216; }
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
lli Price(const lli x) { return x % 10; }

struct Problem {
  std::vector<lli> initial;

  std::map<std::vector<int>, lli> best_by_seq;
  std::vector<std::vector<std::pair<std::vector<int>, int>>> all_seqs;
  void Precompute() {
    best_by_seq.clear();
    all_seqs.clear();

    std::vector<int> current_seq(kSequenceSize);
    auto UpdateCurrentSeq = [&](const lli x) {
      for (int i = 1, end = kSequenceSize + 1; i < kSequenceSize; ++i)
        current_seq[i - 1] = current_seq[i];
      current_seq.back() = x;
    };
    for (const lli i : initial) {
      std::set<std::vector<int>> done;
      auto& buyer_seqs = all_seqs.emplace_back();
      lli x = i, prv = i;
      for (int j = 0; j < kSteps; ++j) {
        x = Evolve(x);
        UpdateCurrentSeq(Price(x) - Price(prv));
        prv = x;

        if (j < 3) continue;

        auto [_, inserted] = done.emplace(current_seq);
        if (!inserted) continue;
        best_by_seq[current_seq] += Price(x);

        buyer_seqs.emplace_back(current_seq, Price(x));
      }
    }
  }

  lli Eval() {
    auto it = best_by_seq.find(target_seq);
    if (it == best_by_seq.end()) return 0;
    return it->second;
  }

  std::vector<int> target_seq;

  void Solve() {
    for (lli i; std::cin >> i;) {
      initial.push_back(i);
    }

    Precompute();

    target_seq.resize(kSequenceSize);
    lli ans = 0;
    int todo = std::pow(19, 4);
    int done = 0;
    for (int i = -9; i <= 9; ++i) {
      target_seq[0] = i;
      for (int j = -9; j <= 9; ++j) {
        target_seq[1] = j;
        for (int k = -9; k <= 9; ++k) {
          target_seq[2] = k;
          for (int l = -9; l <= 9; ++l) {
            target_seq[3] = l;
            ans = std::max(ans, Eval());
            if (++done % 10000 == 0) {
              std::cout << "done: " << ((double)done / todo) << "\n";
              std::fflush(stdout);
            }
          }
        }
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
