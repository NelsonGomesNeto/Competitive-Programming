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

### Better yet, use "hash sum"
It's possible to simplify all of the above with:
  hash_values[1 : k - 1] = random values
  hash_values[0] = sum(hash_values[1 : k - 1])
Then, sum(hash_values) = 0
So, instead of manually building the hashes and manipulating/normalizing the
frequency count prefixes. All we need is to do:
  hash_sum += hash_values[ci]
  :)
Since sum(hash_values) = 0, it automatically normalized itself :).
In the very worst case, we can add more `hash_values` versions to reduce solve
conflicts.
*/

using hash_sum_t = uint64_t;
std::mt19937_64 random_gen;

struct TestCase {
  int n, k;
  std::vector<int> c;

  std::vector<std::vector<int>> mappings;

  int SmallKWithHashes() {
    // Precalc hash_values for the hash_sum.
    std::vector<hash_sum_t> hash_values(k, 0);
    for (int i = 1; i < k; ++i) {
      hash_values[i] = random_gen();
      hash_values[0] -= hash_values[i];
    }

    std::unordered_map<hash_sum_t, int> pos_map;
    hash_sum_t hash_sum = 0;
    pos_map.emplace(hash_sum, -1);
    int ans = 0;
    for (const auto [i, ci] : c | std::views::enumerate) {
      hash_sum += hash_values[ci];
      const auto [it, inserted] = pos_map.try_emplace(hash_sum, i);
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

    const int ans = SmallKWithHashes();
    std::println("{}", ans);

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::random_device rd;
  random_gen = std::mt19937_64(rd());

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
