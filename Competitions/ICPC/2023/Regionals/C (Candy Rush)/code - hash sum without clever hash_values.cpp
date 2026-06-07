#include <bits/stdc++.h>
#define DEBUG if (0)
// #define DEBUG if (1)
// #define DEBUG if (n == 4)
#define lli long long int

/*
https://maratona.sbc.org.br/hist/2023/contest/editorial.pdf shares the core of
the idea.

A solution with 2 cases for k bigger or smaller than sqrt(n) passes.
Yup, it's O(n*sqrt(n)*lg(n)) but the time limit is generous.

The O(n*lg(n)) solution is an improvement over the k < sqrt(n) solution.

### Idea
For each prefix, maintain a frequency count for each candy.
We want the subtraction of two frequency vectors to be have the same count on
all positions. But searching for previous prefixes will be hard.
So, we use normalization trick to subtract by the frequency count by the minimum
(e.g. [2, 3, 2] -> [0, 1, 0]). You want the subtraction of two frequency vectors
to be 0.
Then, you just need to find an exact match \o/.

### Example
For example: 2 1 2 1 2 2 3
Prefix([0 : 0]) = [0, 1, 0]
Prefix([0 : 6]) = [2, 3, 2] ([0, 1, 0] if normalized)
So, [1 : 6] would have [2, 3, 2] - [0, 1, 0] = [2, 2, 2] frequency count.

### Optimization from O(n*k*lg(n)) to O(n*lg(n))
Instead of maintaining a map of the prefixes, we can maintain a map of a hash
of the prefixes! \o/

The hash is (i * freq[i], [1 : k]). I had to use 5 hashes to avoid conflicts.
The hashes were based on randomized permutations of [1 : k]
*/

const int kHashCount = 5;
std::mt19937 random_gen;

struct TestCase {
  int n, k;
  std::vector<int> c;

  std::vector<std::vector<int>> mappings;

  int SmallKWithHashes() {
    DEBUG std::println("\tsmall");
    std::map<std::array<size_t, kHashCount>, int> pos_map;
    std::vector<int> cnt(k, 0);
    std::array<size_t, kHashCount> hashes;
    std::ranges::fill(hashes, 0);
    pos_map.emplace(hashes, -1);
    int curr_min = 0, min_pos = 0;
    int ans = 0;
    for (const auto [i, ci] : c | std::views::enumerate) {
      for (auto [hash, mapping] : std::views::zip(hashes, mappings)) {
        hash ^= mapping[ci] * (cnt[ci] - curr_min);
        hash ^= mapping[ci] * (cnt[ci] - curr_min + 1);
      }
      ++cnt[ci];

      // Maybe we need to normalize all frequencies.
      if (cnt[min_pos] > curr_min) {
        auto nxt_min_it =
            std::ranges::find(cnt.begin() + min_pos + 1, cnt.end(), curr_min);
        // Normalize all frequencies.
        // This only happens once every O(n / k). So, the complexity becomes
        // O(n) :) (*lg(n) due to the map).
        if (nxt_min_it == cnt.end()) {
          for (auto [hash, mapping] : std::views::zip(hashes, mappings)) {
            for (auto [v, cntv] : cnt | std::views::enumerate) {
              hash ^= mapping[v] * (cntv - curr_min);
              hash ^= mapping[v] * (cntv - (curr_min + 1));
            }
          }
          ++curr_min;
          nxt_min_it = std::ranges::find(cnt, curr_min);
        }
        min_pos = nxt_min_it - cnt.begin();
      }

      const auto [it, inserted] = pos_map.try_emplace(hashes, i);
      // New frequency hash.
      if (inserted) continue;
      ans = std::max(ans, (int)i - it->second);
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    c.resize(n);
    for (int& ci : c) {
      std::cin >> ci;
      --ci;
    }

    mappings.resize(kHashCount, std::vector<int>(k));
    for (auto& mapping : mappings) {
      std::ranges::iota(mapping, 0);
      std::ranges::shuffle(mapping, random_gen);
    }

    int ans = SmallKWithHashes();
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
