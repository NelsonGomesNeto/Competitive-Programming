#include <bits/stdc++.h>
#define lli long long int

const int kPasswordSize = 8;
const int kAlpha = 26;

bool SlowIsValid(const std::string& s) {
  // 2nd rule
  const bool has_iol = [&]() {
    return s.contains('i') || s.contains('o') || s.contains('l');
  }();
  if (has_iol) return false;

  // 1st rule
  const bool has_sequence = [&]() {
    for (const auto [i, j, k] : s | std::views::adjacent<3>) {
      if (i + 1 == j && j + 1 == k) return true;
    }
    return false;
  }();
  if (!has_sequence) return false;

  // 3rd rule
  const bool has_two_pairs = [&]() {
    char first_pair = '\0';
    for (const auto [i, j] : s | std::views::adjacent<2>) {
      if (i != j) continue;
      if (first_pair == '\0')
        first_pair = i;
      else if (i != first_pair)
        return true;
    }
    return false;
  }();
  return has_two_pairs;
}
bool IsValid(const std::string& s) {
  // 1st optimization: 2.9s -> 2.6s on `ghijklmn` twice
  bool has_sequence = false, has_two_pairs = false;
  char prv1 = '\0', prv2 = '\0', pair = '\0';
  for (const char c : s) {
    // 2nd rule
    if (c == 'i' || c == 'o' || c == 'l') return false;

    // 1st rule
    if (prv2 != '\0' && c == prv1 + 1 && prv1 == prv2 + 1) {
      has_sequence = true;
    }

    // 3rd rule
    if (prv1 != '\0' && c == prv1) {
      if (pair == '\0')
        pair = c;
      else if (c != pair)
        has_two_pairs = true;
    }

    prv2 = prv1;
    prv1 = c;
  }
  return has_sequence && has_two_pairs;
}
lli StringToNumber(const std::string& s) {
  lli num = 0;
  for (const char c : s) {
    num = num * kAlpha + (c - 'a');
  }
  return num;
}
void NumberToString(lli num, std::string& s) {
  for (int i = kPasswordSize - 1; i >= 0; --i) {
    s[i] = 'a' + (num % 26);
    num /= kAlpha;
  }
  // 2nd optimization: 2.7s -> 700ms! on `ghijklmn` twice
  // s.clear();
  // s.reserve(kPasswordSize);
  // while ((int)s.size() < kPasswordSize) {
  //   s.push_back('a' + (num % 26));
  //   num /= kAlpha;
  // }
  // std::ranges::reverse(s);
}

struct Password {
  std::string str;

  void TrySkipIol(lli& curr, std::string& s) const {
    for (int i = 0; i < kPasswordSize; ++i) {
      if (s[i] == 'i' || s[i] == 'o' || s[i] == 'l') {
        ++s[i];
        std::ranges::fill(s.begin() + i + 1, s.end(), 'a');
        curr = StringToNumber(s);
        return;
      }
    }
  }
  std::string FindNextValid(const bool skip_current = false) const {
    std::string s = str;
    lli curr = StringToNumber(str) + skip_current;
    while (true) {
      // 3rd optimization: 60s to 2ms on!!!! `iaaaaaaa`
      TrySkipIol(curr, s);
      NumberToString(curr, s);
      if (IsValid(s)) break;
      ++curr;
    }
    return s;
  }

  friend std::istream& operator>>(std::istream& sin, Password& p) {
    sin >> p.str;
    return sin;
  }
};
template <>
struct std::formatter<Password> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Password& p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}", p.str);
  }
};

int main() {
  while (true) {
    Password password;
    if (!(std::cin >> password)) break;
    assert(password.str.size() == kPasswordSize);

    std::println("current_password: {}", password);

    const Password next_password = Password{password.FindNextValid()};
    std::println(
        "next_password: {} | {} distance", next_password,
        StringToNumber(next_password.str) - StringToNumber(password.str) + 1);

    const std::string ans = next_password.FindNextValid(/*skip_current=*/true);
    std::println("ans: {}", ans);
  }
  return 0;
}
