#include <bits/stdc++.h>

bool IsNice(const std::string& s) {
  const bool has_repeated_pair = [&]() {
    for (const auto [i, pair] :
         s | std::views::slide(2) | std::views::enumerate) {
      if (s.find(std::string(pair.begin(), pair.end()), i + 2) != s.npos)
        return true;
    }
    return false;
  }();
  const bool has_one_between = [&]() {
    for (const auto trio : s | std::views::slide(3)) {
      if (trio[0] == trio[2]) return true;
    }
    return false;
  }();
  return has_repeated_pair && has_one_between;
}

int main() {
  int ans = 0;
  while (true) {
    std::string s;
    if (!(std::cin >> s)) break;
    const bool is_nice = IsNice(s);
    std::println("{} {}", s, is_nice);
    ans += is_nice;
  }
  std::println("ans: {}", ans);
  return 0;
}
