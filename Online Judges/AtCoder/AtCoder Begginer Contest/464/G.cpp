#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
This is my implementation of the solution described on
https://atcoder.jp/contests/abc464/editorial/22271.

Unfortunately, I don't understand why this transformation works yet.

BUT, here are the transformations:
### 1. Append 'S' and 'R' in the start and end (`s` -> 'S' + s + 'R').

After this, `s` will be composed of S(R...)(S...)(R...)(S...)R.
Let `a` = count of all "SR" and "RS" pairs.
Then, "RS" count = (`a` - 1) / 2.
So, we can maximize `a` (without changing the added letters).

### 2. Transform `s` in the pairwise diffs `t`.
SRRSR -> 1011 (1 = SR or RS, 0 = SS or RR).

After this, we want to maximize the ones and the only operation which increases
the number of ones is to transform a pair of 0s in 1s. For example:
SRRR (100) -> SRSR (111)
It's worth noting that any other operation new 0s will just move it:
SRRSR (1011) -> SRSSR (1101)

So, we want to bundle 0s together and convert them into 1s.

### 3. Transform the pairwise diffs `t` in distances of 0s `D`.
10100101 -> 2, 1, 2

This is the part where I don't have a proof of good intuition. But, here you go:
Greedily:
1. Pick the minimum at `D` (let that be position `i`);
2. Remove the adjacents (i - 1, i, i + 1);
3. Add D[i - 1] + D[i + 1] - D[i];
4. Repeat until empty.
Then:
sum of removed `D` = number of operations
`a` = 1s (every iteration adds 2)

Example:
10100101 -> 2, 1, 2
10111101 -> 3 (yes, I know, the distance isn't "real" anymore. But here is why:
If we were to move the 0s in the middle instead of merging them, we would need
exactly 4 moves:
10100101 - 0
11000101 - 1
11000011 - 2
11110011 - 3
11111111 - 4
So, "D[i - 1] + D[i + 1] - D[i]" magically adjusts for that.
Sorry, this is exactly the part that I'm confused about hahaha.
)

### Is it possible to get all answers in O(n^2 * MaybeSomeLog)?
I believe the transformation can be reversed and that's exactly what I want to
try \o/.
*/

const int kInf = 1e8;

struct TestCase {
  int n;
  std::string s;

  std::vector<bool> flips;
  std::vector<int> zero_dists;

  bool Run() {
    if (!(std::cin >> n >> s)) return false;

    s = "S" + s + "R";
    flips.reserve((int)s.size() - 1);
    int ones = 0;
    for (const auto [prv, curr] : s | std::views::adjacent<2>) {
      const bool flipped = prv != curr;
      flips.push_back(flipped);
      ones += flipped;
    }
    zero_dists.push_back(kInf);
    for (int i = 0; i < (int)flips.size(); ++i) {
      if (flips[i]) continue;
      int j = i;
      while (j + 1 < (int)flips.size() && flips[j + 1]) ++j;
      if (j + 1 == (int)flips.size()) break;
      zero_dists.push_back(j - i + 1);
      i = j;
    }
    zero_dists.push_back(kInf);
    DEBUG {
      std::println("{}", s);
      std::println("{}", flips | std::views::transform([](const bool x) {
                           return std::format("{}", x ? 1 : 0);
                         }) | std::views::join_with(std::string_view("")) |
                             std::ranges::to<std::string>());
      std::println("{}", zero_dists);
    }

    std::list<int> zero_dists_list(zero_dists.begin(), zero_dists.end());
    auto cmp = [](const auto& a, const auto& b) {
      return a.first < b.first ||
             (a.first == b.first &&
              std::to_address(a.second) < std::to_address(b.second));
    };
    std::set<std::pair<int, std::list<int>::iterator>, decltype(cmp)>
        zero_dists_set(cmp);
    for (auto it = zero_dists_list.begin(); it != zero_dists_list.end(); ++it) {
      zero_dists_set.emplace(*it, it);
    }
    std::vector<int> all_ans(n + 1, 0);
    all_ans[0] = (ones - 1) >> 1;
    int edits = 0;
    while ((int)zero_dists_list.size() >= 3) {
      // auto it = std::ranges::min_element(
      //     zero_dists.begin() + 1,
      //     zero_dists.begin() + (int)zero_dists.size() - 1);
      auto it = zero_dists_set.begin()->second;
      auto prv = std::prev(it), nxt = std::next(it);
      zero_dists_set.erase(zero_dists_set.begin());
      auto prv_it = zero_dists_set.find({*prv, prv});
      assert(prv_it != zero_dists_set.end());
      zero_dists_set.erase(prv_it);
      auto nxt_it = zero_dists_set.find({*nxt, nxt});
      assert(nxt_it != zero_dists_set.end());
      zero_dists_set.erase(nxt_it);

      const int new_dist = *prv + *nxt - *it;
      edits += *it;
      ones += 2;
      all_ans[edits] = (ones - 1) >> 1;

      // zero_dists.erase(nxt);
      // zero_dists.erase(it);
      // auto after_prv_it = zero_dists.erase(prv);
      // zero_dists.insert(after_prv_it, new_dist);
      zero_dists_list.erase(nxt);
      zero_dists_list.erase(it);
      auto after_prv_it = zero_dists_list.erase(prv);
      auto new_it = zero_dists_list.insert(after_prv_it, new_dist);
      zero_dists_set.emplace(new_dist, new_it);
      DEBUG {
        std::println("\t{}", zero_dists_list);
        std::fflush(stdout);
      }
    }
    for (auto [prv, curr] : all_ans | std::views::adjacent<2>) {
      curr = std::max(prv, curr);
    }

    // std::println("{} | {} | {}", ones, ones >> 1, (ones - 1) >> 1);

    std::println("{}", all_ans | std::views::transform([](const int x) {
                         return std::format("{}", x);
                       }) | std::views::join_with(' ') |
                           std::ranges::to<std::string>());

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
