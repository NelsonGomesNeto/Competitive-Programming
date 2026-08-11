#include <bits/stdc++.h>

const std::vector<std::string> kProhibiteds = {"ab", "cd", "pq", "xy"};

bool IsVowel(const char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
bool IsNice(const std::string& s) {
  int vowel_count = 0;
  for (const auto c : s) {
    vowel_count += IsVowel(c);
  }
  const bool has_repeated_letter = [&]() {
    for (const auto [a, b] : s | std::views::adjacent<2>) {
      if (a == b) return true;
    }
    return false;
  }();
  const bool has_prohibited = [&]() {
    for (const auto& p : kProhibiteds) {
      if (s.contains(p)) return true;
    }
    return false;
  }();
  return vowel_count >= 3 && has_repeated_letter && !has_prohibited;
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
