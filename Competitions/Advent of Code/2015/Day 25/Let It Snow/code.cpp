#include <bits/stdc++.h>
#define lli long long int

const lli kStart = 20151125;
const lli kMult = 252533;
const lli kMod = 33554393;
const int kPadding = 8;
const int kMaxToPrint = 6;
// position(1, 1) = 1
// position(1, 2) = 3
// position(1, 3) = 6
// position(1, 4) = 10
// position(1, j) = apSum(a1=1, n=j, d=1)
// position(i, 1) = apSum(a1=1, n=i, d=1) - (i - 1)
// position(i, j) = position(1, j + i) - (i - 1)
// manual(i, j) = kStart * ModPow(kMult, position(i, j) - 1) % kMod

lli ApSum(lli a1, lli n, lli d) {
  lli an = a1 + (n - 1) * d;
  return n * (a1 + an) >> 1LL;
}
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1;
  }
  return ans;
}
lli CodeByCell(const int i, const int j) {
  const lli diagonal_counting = ApSum(/*a1=*/1,
                                      /*n=*/i + j + 1, /*d=*/1) -
                                i;
  return kStart * ModPow(kMult, diagonal_counting - 1) % kMod;
  // return diagonal_counting;
}

struct Manual {
  const int n, m;
  const std::vector<std::vector<lli>> mat;
  Manual(const int n_, const int m_)
      : n(n_), m(m_), mat([&]() {
          std::vector<std::vector<lli>> grid(n, std::vector<lli>(m, 0));
          for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
              grid[i][j] = CodeByCell(i, j);
              // grid[i][j] = diagonal_counting;
            }
          }
          return grid;
        }()) {}

  lli Code(const int ti, const int tj) const {
    // return CodeByCell(ti, tj);
    return mat[ti - 1][tj - 1];
  }
};
template <>
struct std::formatter<Manual> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Manual& m, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{} x {}\nmat:\n{:{}} | {}\n{}", m.n, m.m, "", kPadding,
        std::views::iota(1, kMaxToPrint + 1) |
            std::views::transform(
                [](const int j) { return std::format("{:{}}", j, kPadding); }) |
            std::views::join_with(' ') | std::ranges::to<std::string>(),
        m.mat | std::views::take(kMaxToPrint) | std::views::enumerate |
            std::views::transform([](const auto& iline) {
              const auto& [i, line] = iline;
              return std::format("{:{}} | {}", i + 1, kPadding,
                                 line | std::views::take(kMaxToPrint) |
                                     std::views::transform([](const lli a) {
                                       return std::format("{:{}}", a, kPadding);
                                     }) |
                                     std::views::join_with(' ') |
                                     std::ranges::to<std::string>());
            }) |
            std::views::join_with('\n') | std::ranges::to<std::string>());
  }
};

int main() {
  int n, m;
  std::cin >> n >> m;

  const Manual manual(n, m);
  std::println("manual:\n{}", manual);

  const lli ans = manual.Code(n, m);
  std::println("ans: {}", ans);

  return 0;
}
