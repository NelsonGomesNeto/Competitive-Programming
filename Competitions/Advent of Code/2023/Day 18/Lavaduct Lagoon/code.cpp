#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int inf = 1e5;
const int n = 400, m = 400;

enum Dir { R, U, L, D, X };
const int di[5] = {0, -1, 0, 1, 0};
const int dj[5] = {1, 0, -1, 0, 0};
std::map<char, Dir> dir_by_name = {
    {'R', Dir::R}, {'U', Dir::U}, {'L', Dir::L}, {'D', Dir::D}, {'X', Dir::X}};
const char dir_name[5] = {'R', 'U', 'L', 'D', 'X'};
bool IsVerticalDir(const Dir dir) { return dir == Dir::U || dir == Dir::D; }

const int kBlueMask = (1 << 8) - 1;
const int kGreenMask = ((1 << 16) - 1) & ~kBlueMask;
const int kRedMask = ((1 << 24 - 1)) & ~(kGreenMask | kBlueMask);
struct Color {
  int rgb = 0;
  Color() {}
  Color(int c) : rgb(c) {}

  int Red() const { return rgb >> 16; }
  int Green() const { return (rgb & kGreenMask) >> 8; }
  int Blue() const { return rgb & kBlueMask; }
  std::string ToString() {
    std::ostringstream sout;
    sout << Red() << " " << Green() << " " << Blue();
    return sout.str();
  }

  friend std::ostream& operator<<(std::ostream& stream, const Color& c) {
    stream << (char)c.Red() << (char)c.Green() << (char)c.Blue();
    return stream;
  }
};

struct Dig {
  Dir dir;
  int steps;
  Color color;

  Dig(const std::string& d) {
    std::istringstream sin(d);

    char dir_name;
    sin >> dir_name >> steps;

    dir = dir_by_name[dir_name];

    sin.ignore(3) >> std::hex >> color.rgb;

    std::cout << dir << " " << steps << " " << color.ToString() << "\n";
  }
};
struct DigPlan {
  std::vector<Dig> digs;
  std::vector<std::tuple<int, int, Color, Dir>> positions;
  int min_i = inf, min_j = inf;
  int max_i = -inf, max_j = -inf;
  int n, m;
  std::vector<std::vector<std::pair<Color, Dir>>> result;

  DigPlan() {}
  DigPlan(const std::vector<std::string>& ds) {
    for (const auto& d : ds) digs.emplace_back(d);
    ExecutePlan();
  }

  void FillInside() {
    for (int i = 0; i < n; ++i) {
      int cnt = 0;
      for (int j = 0; j < m; ++j) {
        if (result[i][j].first.rgb == 0) {
          if (cnt & 1) result[i][j] = std::make_pair(Color(0xffffff), Dir::X);
          continue;
        }

        int k = j;
        while (k + 1 < m && result[i][k + 1].first.rgb != 0) {
          ++k;
        }

        const Dir start = result[i][j].second, end = result[i][k].second;
        // Otherwise it's an outer border.
        if (start == end) {
          ++cnt;
        }

        j = k;
      }
    }
  }
  void ExecutePlan() {
    auto UpdateBB = [&](const int i, const int j) {
      min_i = std::min(min_i, i), max_i = std::max(max_i, i);
      min_j = std::min(min_j, j), max_j = std::max(max_j, j);
    };
    int i = 0, j = 0;
    positions.emplace_back(i, j, digs[0].color, digs[0].dir);
    UpdateBB(i, j);
    for (const auto& dig : digs) {
      for (int k = 0; k < dig.steps; ++k) {
        if (IsVerticalDir(dig.dir)) std::get<3>(positions.back()) = dig.dir;
        const int ni = i + di[dig.dir], nj = j + dj[dig.dir];
        i = ni, j = nj;
        positions.emplace_back(i, j, dig.color, dig.dir);
        UpdateBB(i, j);
      }
    }

    n = max_i - min_i + 1, m = max_j - min_j + 1;
    result = std::vector<std::vector<std::pair<Color, Dir>>>(
        n,
        std::vector<std::pair<Color, Dir>>(m, std::make_pair(Color(), Dir::X)));
    for (const auto [i, j, c, dir] : positions) {
      result[i - min_i][j - min_j] = std::make_pair(c, dir);
    }

    FillInside();
  }

  void PrintResult() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cout << (result[i][j].first.rgb == 0
                          ? '.'
                          : dir_name[result[i][j].second]);
      }
      std::cout << "\n";
    }
  }

  void PrintImage() {
    std::ofstream ofs("image.ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6\n" << m << " " << n << "\n255\n";

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        // ofs << (char)(i % 256) << (char)(j % 256) << (char)(i * j % 256);
        ofs << result[i][j].first;
      }
  }

  int CubicMeters() {
    int ans = 0;
    for (const auto& row : result)
      for (const auto& cell : row) ans += cell.first.rgb != 0;
    return ans;
  }
};

int main() {
  std::vector<std::string> ds;
  for (std::string line; std::getline(std::cin, line);) {
    ds.push_back(line);
  }
  DigPlan dig_plan(ds);

  dig_plan.PrintResult();
  dig_plan.PrintImage();
  int ans = dig_plan.CubicMeters();
  std::cout << ans << "\n";

  return 0;
}
