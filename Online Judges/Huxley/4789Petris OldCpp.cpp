#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// template <class T>
// struct std::formatter<std::vector<T>> {
//   constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin();
//   } auto format(const std::vector<T>& arr, std::format_context& ctx) const {
//     auto out = ctx.out();
//     std::format_to(out, "[");
//     bool first = true;
//     for (const T& v : arr) {
//       if (!first) std::format_to(out, ", ");
//       std::format_to(out, "{}", v), first = false;
//     }
//     return std::format_to(out, "]");
//   }
// };

int GetInt(std::istream& sin) {
  int value;
  sin >> value;
  return value;
}
struct Rock {
  int column, color;
  Rock(std::istream&& sin) : column(GetInt(sin)), color(GetInt(sin)) {}
  Rock(const std::string& input) : Rock(std::istringstream(input)) {}
};
// template <>
// struct std::formatter<Rock> {
//   constexpr auto parse(std::format_parse_context& ctx) { return ctx.end(); }
//   auto format(const Rock& rock, std::format_context& ctx) const {
//     return std::format_to(ctx.out(), "(i:{}, c:{})", rock.column,
//     rock.color);
//   }
// };

struct Game {
  const std::vector<Rock> rocks;
  std::vector<std::vector<int>> mat;
  Game(const std::vector<Rock> rocks_) : rocks(rocks_) {}

  // void DebugPrint() {
  //   for (const auto& [i, column] : std::views::enumerate(mat)) {
  //     std::println("{} | {}", i, column);
  //   }
  //   std::println("-------");
  // }

  std::string TopColumnsString() {
    std::ostringstream sout;
    bool first = true;
    for (const auto& column : mat) {
      sout << " " << column.back();
    }
    return sout.str();
  }

  void AddRock(const int pos, const int color) {
    if (mat[pos].empty() || mat[pos].back() != color) {
      mat[pos].push_back(color);
      return;
    }

    mat[pos].pop_back();
    if (!mat[pos].empty()) return;

    mat.erase(mat.begin() + pos);
  }

  void Emulate() {
    for (const auto& r : rocks) {
      if (r.column == 0) {
        if (mat.empty())
          mat.emplace_back();
        else
          mat.insert(mat.begin(), std::vector<int>{});
        AddRock(0, r.color);
      } else if (r.column == (int)mat.size() + 1) {
        mat.emplace_back();
        AddRock((int)mat.size() - 1, r.color);
      } else {
        assert(r.column <= (int)mat.size());
        AddRock(r.column - 1, r.color);
      }

      // DEBUG DebugPrint();
    }
  }
};

struct TestCase {
  std::vector<Rock> rocks;
  bool Run(const int test_case) {
    for (std::string line; std::getline(std::cin, line) && line[0] != 'E';) {
      rocks.emplace_back(line);
    }
    // DEBUG std::println("rocks: {}", rocks);

    Game g(rocks);
    g.Emulate();
    // std::println("caso {}:{}", test_case, g.TopColumnsString());
    std::cout << "caso " << (test_case - 1) << ":" << g.TopColumnsString()
              << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    std::string ignore;
    std::getline(std::cin, ignore);
    test_case = TestCase{};
    test_case.Run(t);
  }

  return 0;
}
