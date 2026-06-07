#include <bits/stdc++.h>
#define DEBUG if (0)
// #define DEBUG if (1)
// #define DEBUG if (n == 4)
#define lli long long int

const int kHashVersions = 50;
std::mt19937 random_gen;

lli ApSum(lli a1, lli n, lli d) {
  lli an = a1 + (n - 1) * d;
  return n * (a1 + an) >> 1LL;
}

struct TestCase {
  int n, k;
  std::vector<int> c;

  std::array<std::vector<int>, kHashVersions> cs;
  std::array<std::vector<lli>, kHashVersions> accs;

  lli target;
  lli GetSum(const int lo, const int hi, const std::vector<lli>& acc) {
    return acc[hi + 1] - acc[lo];
  }
  lli GetSum(const int lo, const int hi) { return GetSum(lo, hi, accs[0]); }

  int BigK() {
    DEBUG std::println("\tbig");
    int ans = 0;
    for (int i = k - 1; i < n; ++i) {
      for (int j = ans + 1; i - j * k + 1 >= 0; ++j) {
        const int lo = i - j * k + 1, hi = i;
        const lli sum = GetSum(lo, hi);
        const lli k_target = j * target;
        if (sum != k_target) continue;
        const bool valid = [&]() {
          for (const auto& acc : accs) {
            if (GetSum(lo, hi, acc) != k_target) return false;
          }
          return true;
        }();
        if (!valid) continue;
        ans = std::max(ans, j);
      }
    }
    return ans * k;
  }

  int SmallK() {
    DEBUG std::println("\tsmall");
    std::map<std::vector<int>, int> pos_map;
    pos_map.emplace(std::vector<int>(k, 0), -1);
    std::vector<int> cnt(k, 0);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      ++cnt[c[i] - 1];
      // TODO: Try to optimize this!
      if (*std::ranges::min_element(cnt) > 0) {
        for (int& cnti : cnt) --cnti;
      }
      const auto [it, inserted] = pos_map.try_emplace(cnt, i);
      if (inserted) continue;
      ans = std::max(ans, i - it->second);
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    c.resize(n);
    for (int& ci : c) {
      std::cin >> ci;
    }

    target = ApSum(1, k, 1);
    // Precalc "hash" versions.
    std::vector<int> mapping(k + 1);
    std::ranges::iota(mapping, 0);
    for (auto [nc, acc] : std::views::zip(cs, accs)) {
      acc.resize(n + 1);
      // std::ranges::next_permutation(mapping.begin() + 1, mapping.end());
      std::ranges::shuffle(mapping.begin() + 1, mapping.end(), random_gen);
      nc = c;
      acc[0] = 0;
      for (int i = 0; i < n; ++i) {
        nc[i] = mapping[nc[i]];
        acc[i + 1] = acc[i] + nc[i];
      }
    }

    int ans = 0;
    // if (k > std::sqrt(n)) {
    // if (k > 100) {
    if (k > 300) {
      ans = BigK();
    } else {
      ans = SmallK();
    }
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::random_device rd;
  random_gen = std::mt19937(rd());

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
