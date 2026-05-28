#include <bits/stdc++.h>
#define lli long long int

struct KMP {
  std::vector<int> pi;
  // Note that it's definitely possible to expand `pi` if the substring grows
  // for some reason \o/. But I never needed it yet.
  KMP(const std::string& s) {
    pi.resize(s.size() + 1);
    pi[0] = -1;
    for (int i = 0, j = -1; i < s.size();) {
      while (j >= 0 && s[i] != s[j]) j = pi[j];
      pi[++i] = ++j;
    }
  }
  // Returns all occurrences of `sub` on `s`.
  // `sub` must be a prefix of the input on the constructor of KMP.
  // `sub` is left as an argument to allow the optimization of precomputing the
  // `pi` for a bigger string than `sub`. But `sub` MUST be a prefix.
  std::vector<int> AllOccurrences(const std::string& s, const std::string sub,
                                  const bool allow_overlap = false) const {
    std::vector<int> occurrences;
    for (int i = 0, j = 0; i < s.size();) {
      while (j >= 0 && s[i] != sub[j]) j = pi[j];
      i++, j++;
      if (j == sub.size()) {
        occurrences.push_back(i - j);
        if (allow_overlap)
          j = pi[j];
        else
          j = 0;
      }
    }
    return occurrences;
  }
};

const int maxN = 1e5;
int n, m;
std::string s, t;

int main() {
  std::getline(std::cin, s);
  std::getline(std::cin, t);

  const KMP kmp(t);

  for (const bool allow_overlap : std::vector<bool>{false, true}) {
    std::println("allow_overlap={}", allow_overlap);

    const std::vector<int> occurrences =
        kmp.AllOccurrences(s, t, allow_overlap);

    std::println("{} occurrences", (int)occurrences.size());
    std::println("{}", occurrences | std::views::transform([](const int x) {
                         return std::format("{}", x);
                       }) | std::views::join_with(' ') |
                           std::ranges::to<std::string>());
    std::println("{}", s);
    int prev_pos = 0;
    for (const auto [i, pos] : occurrences | std::views::enumerate) {
      std::print("{}^", std::string(pos - prev_pos - (i != 0), ' '));
      prev_pos = pos;
    }
    std::println("");
    std::println("{}", std::string(80, '-'));
  }

  return 0;
}