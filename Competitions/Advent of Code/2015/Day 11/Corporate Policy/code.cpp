#include <bits/stdc++.h>
#define lli long long int

const int kPasswordSize = 8;
const int kAlpha = 26;

bool IsValid(const std::string& s) {
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
lli StringToNumber(const std::string& s) {
  lli num = 0;
  for (const char c : s) {
    num = num * kAlpha + (c - 'a');
  }
  return num;
}
std::string NumberToString(lli num) {
  std::string s;
  while ((int)s.size() < kPasswordSize) {
    s.push_back('a' + (num % 26));
    num /= kAlpha;
  }
  std::ranges::reverse(s);
  return s;
}

struct Password {
  std::string str;

  std::string FindNextValid() const {
    lli curr = StringToNumber(str);
    while (!IsValid(NumberToString(curr))) ++curr;
    return NumberToString(curr);
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

    std::println("current_password: {}", password.str);

    const std::string ans = password.FindNextValid();
    std::println("ans: {}", ans);
  }
  return 0;
}
