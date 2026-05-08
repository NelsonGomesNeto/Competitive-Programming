#include <bits/stdc++.h>
#define DEBUG if (0)
#define LEARN if (0)
#define lli long long int
#define ldouble long double

/*
Grid is beautiful iff all subgrids corners xorsum 0

a, b, c, d are corners
a ^ b ^ c ^ d = 0
for each bit: sum(bit) is even
*/

const lli kMod = 1e9 + 7;
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1LL;
  }
  return ans;
}

struct TestCase {
  int n, m, k, q;
  std::vector<std::tuple<int, int, lli>> fixed;
  std::vector<std::vector<lli>> grid;

  std::vector<std::vector<lli>> columns, rows;

  bool Run() {
    if (!(std::cin >> n >> m >> k >> q)) return false;

    LEARN std::cout << "-------------------\n";

    LEARN grid.resize(n, std::vector<lli>(m, -1));
    fixed.resize(k);

    columns.resize(m, {}), rows.resize(n, {});
    for (auto& [i, j, x] : fixed) {
      std::cin >> i >> j >> x;
      --i, --j;

      columns[j].push_back(x);
      rows[i].push_back(x);

      LEARN grid[i][j] = x;
    }

    LEARN {
      for (int loi = 0; loi < n; ++loi) {
        for (int hii = loi + 1; hii < n; ++hii) {
          for (int loj = 0; loj < m; ++loj) {
            for (int hij = loj + 1; hij < m; ++hij) {
              lli sum = 0;
              for (const int i : std::vector<int>{loi, hii}) {
                for (const int j : std::vector<int>{loj, hij}) {
                  if (grid[i][j] == -1) continue;
                  sum ^= grid[i][j];
                }
              }
              for (int i = loi; i <= hii; ++i) {
                for (int j = loj; j <= hij; ++j) {
                  if (grid[i][j] == -1) continue;
                  sum ^= grid[i][j];
                }
              }
              std::cout << "(" << loi << ", " << loj << ") (" << hii << ", "
                        << hij << ") -> " << std::format("{:b}", sum) << "\n";
            }
          }
        }
      }
    }

    auto IsDirectionValid = [&](const std::vector<std::vector<lli>>& blocks,
                                const int max_cnt) -> bool {
      lli forced = -1;
      for (const auto& values : blocks) {
        if (values.size() != max_cnt) continue;

        lli xor_sum = 0;
        for (const lli& value : values) xor_sum ^= value;
        if (forced == -1) forced = xor_sum;
        if (forced != xor_sum) return false;
      }
      return true;
    };
    const bool columns_valid = IsDirectionValid(columns, n);
    const bool rows_valid = IsDirectionValid(rows, m);
    std::cout << "\t" << columns_valid << " " << rows_valid << "\n";

    lli ans = 0;
    if (columns_valid && rows_valid) {
      lli rem_cells = ((lli)n * m - k);
      ans = ModPow(2, rem_cells / 2 * 30);
    }

    std::cout << ans << "\n";

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
