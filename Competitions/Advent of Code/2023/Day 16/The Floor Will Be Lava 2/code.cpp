#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// R, D, U, L
enum Dir { R, D, U, L };
const char dir_name[4] = {'>', 'v', '^', '<'};
const int di[4] = {0, 1, -1, 0};
const int dj[4] = {1, 0, 0, -1};
const Dir turn_main[4] = {Dir::D, Dir::R, Dir::L, Dir::U};
const Dir turn_sec[4] = {Dir::U, Dir::L, Dir::R, Dir::D};

std::vector<Dir> GetNewDirection(const char c, const Dir d) {
  const auto same_dir = {d};
  switch (c) {
    case '|':
      if (d == Dir::R || d == Dir::L)
        return {Dir::U, Dir::D};
      else
        return same_dir;
      break;
    case '-':
      if (d == Dir::U || d == Dir::D)
        return {Dir::R, Dir::L};
      else
        return same_dir;
      break;
    case '\\':
      return {turn_main[d]};
      break;
    case '/':
      return {turn_sec[d]};
      break;
    default:
      return same_dir;
  }
  assert(false);
  return {};
}

struct Cave {
  int n, m;
  std::vector<std::string> cave;
  std::vector<std::vector<std::vector<int>>> light_path;

  Cave() {}
  Cave(const std::vector<std::string>& c)
      : cave(c),
        n(c.size()),
        m(c[0].size()),
        light_path(c.size(), std::vector<std::vector<int>>(
                                 c[0].size(), std::vector<int>(4, 0))) {}

  int Energy() {
    int ans = 0;
    for (const auto& row : light_path)
      for (const auto& col : row) {
        bool has_light = false;
        for (const int c : col) has_light |= c != 0;
        ans += has_light;
      }
    return ans;
  }
  int BuildLightPath(const int si, const int sj, const Dir sd) {
    std::fill(light_path.begin(), light_path.end(),
              std::vector<std::vector<int>>(m, std::vector<int>(4, 0)));

    std::queue<std::tuple<int, int, Dir>> q;
    q.emplace(si, sj, sd);
    while (!q.empty()) {
      auto [i, j, d] = q.front();
      q.pop();
      if (light_path[i][j][d]++) {
        continue;
      }
      std::vector<Dir> nds = GetNewDirection(cave[i][j], d);

      for (const Dir nd : nds) {
        const int ni = i + di[nd], nj = j + dj[nd];
        if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
        q.emplace(ni, nj, nd);
      }
    }
    return Energy();
  }

  int FindBestEnergy() {
    int ans = std::max({
        BuildLightPath(0, 0, Dir::D),
        BuildLightPath(0, m - 1, Dir::D),
        BuildLightPath(n - 1, 0, Dir::U),
        BuildLightPath(n - 1, m - 1, Dir::U),
    });

    for (int i = 0; i < n; ++i) {
      ans = std::max({ans, BuildLightPath(i, 0, Dir::R),
                      BuildLightPath(i, m - 1, Dir::L)});
    }

    for (int j = 0; j < m; ++j) {
      ans = std::max({ans, BuildLightPath(0, j, Dir::D),
                      BuildLightPath(m - 1, j, Dir::U)});
    }

    return ans;
  }

  void PrintLightPath() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int dir = -1;
        for (int d = 0; d < 4; ++d) {
          if (light_path[i][j][d] != 0) dir = d;
        }
        std::cout << (dir != -1 ? '#' : '.') << (j + 1 < m ? " " : "");
      }
      std::cout << std::endl;
    }
  }
};
Cave cave;

int main() {
  std::vector<std::string> mat;
  for (std::string line; std::getline(std::cin, line);) {
    mat.push_back(line);
  }
  cave = Cave(mat);

  int ans = cave.FindBestEnergy();
  std::cout << ans << std::endl;

  return 0;
}