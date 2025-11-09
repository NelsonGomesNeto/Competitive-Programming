#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kDirectionCount = 4;
const int kDi[kDirectionCount] = {-1, 0, 1, 0};
const int kDj[kDirectionCount] = {0, 1, 0, -1};

bool Valid(const int x, const int limit) { return x >= 0 && x < limit; }

struct Problem {
  int n, m;
  std::vector<std::string> garden;

  struct Region {
    int plant_type, n, m;
    std::vector<std::string> map;
    int perimeter, area;
    Region(const int plant_type, const std::set<std::pair<int, int>>& filled,
           const int max_n, const int max_m)
        : plant_type(plant_type) {
      int loi = max_n, loj = max_m, hii = -1, hij = -1;
      for (const auto& [i, j] : filled) {
        loi = std::min(loi, i), loj = std::min(loj, j);
        hii = std::max(hii, i), hij = std::max(hij, j);
      }

      n = hii - loi + 1, m = hij - loj + 1;
      map.resize(n, std::string(m, ' '));
      for (int i = loi; i <= hii; ++i) {
        for (int j = loj; j <= hij; ++j) {
          const auto ij = std::make_pair(i, j);
          if (!filled.contains(ij)) continue;
          map[i - loi][j - loj] = plant_type;
        }
      }
      area = 0, perimeter = CalculatePerimeter();
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
          if (map[i][j] != plant_type) continue;
          ++area;
        }
    }
    bool HasNeighbor(const int i, const int j, const int d) const {
      const int ni = i + kDi[d], nj = j + kDj[d];
      return Valid(ni, n) && Valid(nj, m) && map[ni][nj] == plant_type;
    }
    int CalculatePerimeter() const {
      int res = 0;
      // Up and Down
      for (const int d : std::vector<int>{0, 2}) {
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < m; ++j) {
            if (map[i][j] != plant_type) continue;

            if (HasNeighbor(i, j, d)) continue;

            while (j + 1 < m && map[i][j + 1] == plant_type &&
                   !HasNeighbor(i, j + 1, d))
              ++j;

            ++res;
          }
      }
      // Right and left
      for (const int d : std::vector<int>{1, 3}) {
        for (int j = 0; j < m; ++j)
          for (int i = 0; i < n; ++i) {
            if (map[i][j] != plant_type) continue;

            if (HasNeighbor(i, j, d)) continue;

            while (i + 1 < n && map[i + 1][j] == plant_type &&
                   !HasNeighbor(i + 1, j, d))
              ++i;

            ++res;
          }
      }
      return res;
    }
    int Price() const { return perimeter * area; }
    void PrintMap() const {
      std::cout << "\t" << n << " " << m << "\n";
      for (const auto& line : map) std::cout << "\t|" << line << "|\n";
    }
  };
  std::map<char, std::vector<Region>> regions_map;

  std::vector<std::vector<bool>> done;
  void FloodFill(const int si, const int sj) {
    const int plant_type = garden[si][sj];
    std::set<std::pair<int, int>> filled;
    std::queue<std::pair<int, int>> q;
    q.emplace(si, sj);
    while (!q.empty()) {
      const auto [i, j] = q.front();
      q.pop();

      if (done[i][j]) continue;
      done[i][j] = true;
      filled.emplace(i, j);

      for (int d = 0; d < kDirectionCount; ++d) {
        const int ni = i + kDi[d], nj = j + kDj[d];
        if (!Valid(ni, n) || !Valid(nj, m) || garden[ni][nj] != plant_type)
          continue;
        q.emplace(ni, nj);
      }
    }
    regions_map[plant_type].emplace_back(plant_type, filled, n, m);
  }
  void FindRegions() {
    done.resize(n, std::vector<bool>(m, false));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (done[i][j]) continue;
        FloodFill(i, j);
      }
    }
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line);) {
      garden.push_back(line);
    }
    n = garden.size(), m = garden[0].size();

    FindRegions();

    int ans = 0;
    for (const auto& [name, regions] : regions_map) {
      for (const auto& region : regions) {
        const int price = region.Price();
        std::cout << name << " | " << region.perimeter << " * " << region.area
                  << " = " << price << "\n";
        DEBUG region.PrintMap();
        ans += price;
      }
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
