#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Hehe {
  int a, b;
  std::string ToString() const { return std::format("({}, {:b})", a, b); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<Hehe> a{{1, 7}, {2, 4}};
  std::println("{}",
               a | std::views::transform([](const Hehe& hehe) -> std::string {
                 return hehe.ToString();
               }));

  return 0;
}
