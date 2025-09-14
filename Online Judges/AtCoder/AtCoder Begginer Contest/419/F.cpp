#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kMod = 998244353LL;
const int kMaxN = 8;
const int kMaxSize = 10;
using mask_t = std::bitset<kMaxN * kMaxSize>;

std::vector<int> PrefixFunction(const std::string& s) {
  std::vector<int> pi(s.size() + 1);
  pi[0] = -1;
  for (int i = 0, j = -1; i < (int)s.size();) {
    while (j >= 0 && s[i] != s[j]) j = pi[j];
    pi[++i] = ++j;
  }
  return pi;
}

struct TestCase {
  int n, l;
  std::vector<std::string> s;
  std::vector<std::vector<int>> s_pi;
  std::vector<mask_t> s_mask;
  mask_t kAllMask;
  std::vector<mask_t> mask_by_size;

  int GetPos(const int i, mask_t mask) {
    mask >>= (i * kMaxSize);
    int pos = 0;
    while (pos < (int)s[i].size() && mask[0]) {
      ++pos, mask >>= 1;
    }
    return pos;
  }

  std::vector<std::unordered_map<mask_t, lli>> memo;
  lli Solve(int i = 0, mask_t mask = 0) {
    if (i == l) {
      return mask == kAllMask;
    }
    auto [it, inserted] = memo[i].emplace(mask, 0);
    if (!inserted) {
      return it->second;
    }

    lli ans = 0;
    mask_t new_mask;
    for (char letter = 'a'; letter <= 'z'; ++letter) {
      new_mask = mask;
      for (int j = 0; j < n; ++j) {
        if ((mask & s_mask[j]) == s_mask[j]) continue;
        int curr_pos = GetPos(j, mask);
        assert(curr_pos < (int)s[j].size());
        if (s[j][curr_pos] == letter) {
          new_mask[(j * kMaxSize) + curr_pos] = true;
        } else {
          // move to matching prefix
          int new_pos = curr_pos;
          while (new_pos >= 0 && letter != s[j][new_pos])
            new_pos = s_pi[j][new_pos];
          ++new_pos;
          new_mask &= ~s_mask[j];
          new_mask |= (mask_by_size[new_pos]) << (j * kMaxSize);
        }
      }
      ans = (ans + Solve(i + 1, new_mask)) % kMod;
    }
    return it->second = ans;
  }

  bool Run() {
    if (!(std::cin >> n >> l)) return false;

    mask_by_size.resize(kMaxSize + 1, mask_t{1});
    mask_by_size[0] = 0;
    for (int i = 2; i <= kMaxSize; ++i) {
      mask_by_size[i] |= mask_by_size[i - 1] << 1;
    }

    s.resize(n), s_mask.resize(n), s_pi.resize(n);
    kAllMask = 0;
    for (int i = 0; i < n; ++i) {
      auto& si = s[i];
      std::cin >> si;
      s_mask[i] = mask_by_size[(int)si.size()] << (i * kMaxSize);
      kAllMask |= s_mask[i];
      s_pi[i] = PrefixFunction(si);
    }

    memo.resize(l, {});
    const lli ans = Solve();
    std::cout << ans << "\n";

    return true;
  }
};

int main() {
  while (true) {
    TestCase test_case{};
    if (!test_case.Run()) break;
  }
  return 0;
}