#include <bits/stdc++.h>

// Right, Down, Left, Up
const int kDirectionCount = 4;
const std::array<int, kDirectionCount> kDi = {0, 1, 0, -1};
const std::array<int, kDirectionCount> kDj = {1, 0, -1, 0};

const std::map<std::string, char> kMorseToLetterMap{
    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
    {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'},
    {"---..", '8'}, {"----.", '9'},
};

struct PiGrid {
  int n, m;
  char op;
  int dash_cost, dot_cost;
  std::array<int, 10> digits_cost;
  std::vector<int> pi_digits;
  std::vector<std::vector<int>> grid;

  friend std::istream& operator>>(std::istream& sin, PiGrid& g) {
    sin >> g.n >> g.m >> g.dash_cost >> g.dot_cost;
    sin.ignore(1);
    sin >> g.op;
    sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string digits_str;
    digits_str.reserve(g.n * g.m);
    std::getline(sin, digits_str);
    assert(digits_str.size() == (g.n * g.m));
    g.pi_digits.resize(g.n * g.m);
    for (auto [digit, digit_char] : std::views::zip(g.pi_digits, digits_str)) {
      digit = digit_char - '0';
    }

    for (const auto& [morse, digit_char] : kMorseToLetterMap) {
      const int digit = digit_char - '0';
      g.digits_cost[digit] = g.dash_cost * std::ranges::count(morse, '-') +
                             g.dot_cost * std::ranges::count(morse, '.') +
                             (g.op == '+' ? digit : -digit);
    }

    g.grid.resize(g.n, std::vector<int>(g.m));
    for (auto [i, row] : g.grid | std::views::enumerate) {
      for (auto [j, value] : row | std::views::enumerate) {
        const int d = i * g.m + j;
        value = g.digits_cost[g.pi_digits[d]];
      }
    }

    return sin;
  }

  struct State {
    int i, j;
    int cost;
    auto operator<=>(const State& other) const { return other.cost <=> cost; }
    bool operator==(const State& other) const {
      return i == other.i && j == other.j && cost == other.cost;
    }
  };
  std::vector<std::vector<int>> memo;
  std::vector<std::vector<std::pair<int, int>>> prv;
  int Solve() {
    memo.resize(n, std::vector<int>(m, std::numeric_limits<int>::max()));
    prv.resize(n, std::vector<std::pair<int, int>>(m, {-1, -1}));
    std::priority_queue<State> pq;
    pq.emplace(0, 0, memo[0][0] = grid[0][0]);
    while (!pq.empty()) {
      const auto [i, j, cost] = pq.top();
      pq.pop();

      if (cost > memo[i][j]) continue;

      for (int d = 0; d < kDirectionCount; ++d) {
        const int ni = i + kDi[d], nj = j + kDj[d];
        if (ni < 0 || ni >= n || nj < 0 || nj >= m ||
            cost + grid[ni][nj] >= memo[ni][nj])
          continue;
        memo[ni][nj] = cost + grid[ni][nj];
        prv[ni][nj] = {i, j};
        pq.emplace(ni, nj, memo[ni][nj]);
      }
    }

    std::vector<std::pair<int, int>> path;
    for (int i = n - 1, j = m - 1; i != -1;) {
      path.emplace_back(i, j);
      const auto [ni, nj] = prv[i][j];
      i = ni, j = nj;
    }
    std::ranges::reverse(path);
    std::println("size: {}, cost: {}", path.size(), memo[n - 1][m - 1]);
    std::println("path: {}",
                 path | std::views::transform([](const auto& ij) {
                   return std::format("({}, {})", ij.first, ij.second);
                 }) | std::views::join_with(std::string_view(" -> ")) |
                     std::ranges::to<std::string>());

    std::vector<std::vector<bool>> plot(n, std::vector<bool>(m, false));
    for (const auto [i, j] : path) {
      plot[i][j] = true;
    }
    std::ofstream image("plot.ppm", std::ofstream::binary);
    std::println(image, "P6\n{} {}\n255\n", n, m);
    for (const auto& line : plot) {
      for (const bool visited : line) {
        std::print(image, "{}{}{}", (char)0, (char)(visited ? 255 : 0),
                   (char)0);
      }
    }

    const int passcode = path.size() * memo[n - 1][m - 1];
    return passcode;
  }
};
template <>
struct std::formatter<PiGrid> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const PiGrid& g, FormatContext& ctx) const {
    std::format_to(ctx.out(), "n x m: {} x {}\n", g.n, g.m);
    std::format_to(ctx.out(), "pi_digits[0:9]: {}\n",
                   g.pi_digits | std::views::take(10));
    std::format_to(ctx.out(), "digits_cost: {}\n",
                   g.digits_cost | std::views::enumerate);
    for (int i = 0, limit = std::min(g.n, 10); i < limit; ++i) {
      std::format_to(ctx.out(), "grid[{}][0:{}]: {}\n", i, limit - 1,
                     g.grid[i] | std::views::take(10));
    }
    return ctx.out();
  }
};

int main() {
  PiGrid pi_grid;
  std::cin >> pi_grid;

  std::println("\tpi_grid:\n{}", pi_grid);
  std::println("{}", std::string(80, '-'));

  const int passcode = pi_grid.Solve();
  std::println("passcode: {}", passcode);

  return 0;
}
