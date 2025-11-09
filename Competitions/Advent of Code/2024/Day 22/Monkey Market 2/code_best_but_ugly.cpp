#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kSteps = 2000;
const lli kMod = 16777216;
const int kSequenceSize = 4;

lli Mix(const lli a, const lli b) { return a ^ b; }
lli Prune(const lli x) { return x % kMod; }
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

using buy_sequence = std::array<short, 4>;

const int kMaxDelta = 18, kMid = 9;

struct Problem {
  std::vector<lli> initial;

  std::vector<std::vector<std::vector<std::vector<lli>>>> best_by_seq;
  void UpdateBest(const buy_sequence& seq, const int price) {
    best_by_seq[kMid + seq[0]][kMid + seq[1]][kMid + seq[2]][kMid + seq[3]] +=
        price;
  };
  lli FindBest() {
    lli ans = 0;
    for (int i = 0; i <= kMaxDelta; ++i) {
      for (int j = 0; j <= kMaxDelta; ++j) {
        for (int k = 0; k <= kMaxDelta; ++k) {
          for (int l = 0; l <= kMaxDelta; ++l) {
            ans = std::max(ans, best_by_seq[i][j][k][l]);
          }
        }
      }
    }
    return ans;
  };

  std::vector<std::vector<std::pair<buy_sequence, int>>> all_seqs;
  void Precompute() {
    best_by_seq.clear();
    all_seqs.clear();

    best_by_seq.clear();
    best_by_seq.resize(
        kMaxDelta + 1,
        std::vector<std::vector<std::vector<lli>>>(
            kMaxDelta + 1,
            std::vector<std::vector<lli>>(kMaxDelta + 1,
                                          std::vector<lli>(kMaxDelta + 1, 0))));

    buy_sequence current_seq;
    auto UpdateCurrentSeq = [&](const int x) {
      std::ranges::rotate(current_seq, current_seq.begin() + 1);
      current_seq.back() = x;
    };
    for (const lli i : initial) {
      std::set<buy_sequence> done;
      auto& buyer_seqs = all_seqs.emplace_back();
      lli x = i, prv = i;
      for (int j = 0; j < kSteps; ++j) {
        x = Evolve(x);
        UpdateCurrentSeq(Price(x) - Price(prv));
        prv = x;

        if (j < 3) continue;

        auto [_, inserted] = done.emplace(current_seq);
        if (!inserted) continue;
        // First time this sequence happened for this buyer, so we register
        // that it would buy at Price(x).
        UpdateBest(current_seq, Price(x));

        buyer_seqs.emplace_back(current_seq, Price(x));
      }
    }
  }

  void Solve() {
    for (lli i; std::cin >> i;) {
      initial.push_back(i);
    }

    Precompute();

    lli ans = FindBest();
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
