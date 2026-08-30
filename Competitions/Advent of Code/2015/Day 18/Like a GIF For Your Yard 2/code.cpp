#include <bits/stdc++.h>
#define ANIMATE if (1)
#define lli long long int

const int kAnimationSeconds = 5;
const std::string_view kClearScreen = "\e[2J";
const std::string_view kMoveTo00 = "\e[0;0H";
const std::string_view kHideCursor = "\e[?25l";
const std::string_view kShowCursor = "\e[?25h";
const std::string_view kBlackBackgrund = "\e[48;2;0;0;0m";
const std::string_view kWhiteForeground = "\e[38;2;255;255;255m";
const std::string_view kResetColor = "\e[0m";

struct Animation {
  const int steps;
  const std::chrono::nanoseconds frame_time;
  const std::vector<std::string> initial_grid;
  const int n, m;
  Animation(std::istringstream&& sin)
      : steps([&]() {
          int num;
          sin >> num;
          return num;
        }()),
        frame_time(std::chrono::nanoseconds((lli)std::round(
            (long double)kAnimationSeconds / (steps + 1) *
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::seconds(1))
                .count()))),
        initial_grid([&]() {
          std::vector<std::string> g;
          for (std::string line; sin >> line;) g.push_back(line);
          return g;
        }()),
        n(initial_grid.size()),
        m(initial_grid[0].size()) {}
  Animation(const std::string& str) : Animation(std::istringstream(str)) {}

  void ComputeNextFrame(const std::vector<std::string>& grid,
                        std::vector<std::string>& next) const {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        const int neighbors = [&]() {
          int cnt = 0;
          for (int ii = std::max(i - 1, 0), end = std::min(i + 1, n - 1);
               ii <= end; ++ii) {
            for (int jj = std::max(j - 1, 0), end = std::min(j + 1, m - 1);
                 jj <= end; ++jj) {
              if (ii == i && jj == j) continue;
              cnt += grid[ii][jj] == '#';
            }
          }
          return cnt;
        }();
        if ((i == 0 || i == n - 1) && (j == 0 || j == m - 1)) {
          next[i][j] = grid[i][j];
        } else if (grid[i][j] == '#' && neighbors != 2 && neighbors != 3) {
          next[i][j] = '.';
        } else if (grid[i][j] != '#' && neighbors == 3) {
          next[i][j] = '#';
        } else {
          next[i][j] = grid[i][j];
        }
      }
    }
  }

  void Animate() const {
    std::vector<std::string> grid = initial_grid, next = initial_grid;
    std::print("{}{}", kClearScreen, kHideCursor);
    std::fflush(stdout);
    for (int t = 0; t <= steps; ++t) {
      auto start_time = std::chrono::system_clock::now();
      grid = next;
      ComputeNextFrame(grid, next);
      std::println(
          "{}{}{}t={}\n{}{}", kMoveTo00, kBlackBackgrund, kWhiteForeground, t,
          grid | std::views::join_with('\n') | std::ranges::to<std::string>(),
          kResetColor);
      auto end_time = std::chrono::system_clock::now();
      std::this_thread::sleep_for(
          std::chrono::nanoseconds(frame_time - (end_time - start_time)));
    }
  }

  int CountOnAfter() const {
    std::vector<std::string> grid = initial_grid, next = initial_grid;
    for (int t = 0; t <= steps; ++t) {
      grid = next;
      ComputeNextFrame(grid, next);
    }
    ANIMATE {}
    else {
      std::println(
          "t={}\n{}", steps,
          grid | std::views::join_with('\n') | std::ranges::to<std::string>());
    }
    const int ans = std::transform_reduce(
        grid.begin(), grid.end(), 0, std::plus(),
        [](const std::string& line) { return std::ranges::count(line, '#'); });
    return ans;
  }
};
template <>
struct std::formatter<Animation> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Animation& a, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}",
                          a.initial_grid | std::views::join_with('\n') |
                              std::ranges::to<std::string>());
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::stringstream ss;
  ss << std::cin.rdbuf();
  const std::string input = ss.str();

  const Animation animation(input);
  std::println("animation:\n{}", animation);

  ANIMATE animation.Animate();

  const int ans = animation.CountOnAfter();
  std::println("ans: {}", ans);

  return 0;
}
