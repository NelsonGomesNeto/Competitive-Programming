#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

/*
operation_cost = |range| + color_cost
We need to minimize the total cost of painting all positions with their targeted
cost.

The circular part is tricky, but we can prove that all circular movements are be
done in a non-circular array by just rotating the array beforehand. That allows
us to run the solution over all rotations of the input (instead of having to
handle circularity on the solution).
So, it's mostly here as a clever way of forcing us to not do a O(n^3) solution.

Some people found it easier to think about the reverse problem:
  Given a colored array, minimize the cost of painting all positions with color
  0. With the additional restriction that you can only paint a range if that
  range has color `x` or `0`.
  This may be easier to think for BottomUp indeed and to identify the
  optimization to drop one `n` in the complexity.

But anyways, I solved TopDown by:
  Solve(lo, hi, done_color = no_color):
    for all prefixes [lo : j]:
      remaining_range = Solve(lo + 1, hi, done_color)
      paint_individual =
        total cost of painting all positions with their own colors (no
        recursion, just group all the ones that have the same color). Note that
        we need to skip positions with color `done_color` since this range might
        have been painted with that color already.
      paint_range =
        paint this whole range with color `c[lo]`, then
        Solve(lo + 1, j - 1, c[lo]) to find the best option for the inner range
      ans = min(
        paint_individual,
        paint_range (iff c[lo] == c[j])
      ) + remaining_range
*/

const lli kInf = 1e18;
int hehe = 0;

struct TestCase {
  int n;
  std::vector<int> c, x;

  std::vector<std::vector<std::vector<lli>>> memo;
  struct Choice {
    int j, color;
  };
  std::vector<std::vector<std::vector<Choice>>> path_memo;
  lli Solve(const int lo, const int hi, const int done_color = -1) {
    if (lo > hi) return 0;
    if (lo == hi) return c[lo] == done_color ? 0 : 1 + x[c[lo]];

    // Note that we don't need more than a bool for `done_color` because it will
    // always *traceback* to a single `c[lo]` who called that recursion painting
    // that range *exact* range. The only choice here is just whether or not the
    // range was painted.
    lli& ans = memo[lo][hi][done_color == -1];
    Choice& path = path_memo[lo][hi][done_color == -1];
    if (ans != -1) return ans;

    ans = kInf;
    lli total_sum = 0;
    int previous_color = -1, current_length = 1;
    for (int j = lo; j <= hi; ++j) {
      // Solve for the remaining range [j + 1 : hi]
      const lli rem_range = Solve(j + 1, hi, done_color);

      const int current_color = c[j];
      if (current_color == previous_color)
        ++current_length;
      else
        current_length = 1;
      previous_color = c[j];

      // Individually flip every group of colors in [lo : j]
      lli to_add = 1 + (current_length == 1 ? x[current_color] : 0);
      if (current_color == done_color) to_add = 0;
      total_sum += to_add;
      const lli paint_individual = rem_range + total_sum;
      if (paint_individual < ans) ans = paint_individual, path = {j, -1};

      // If both ends are the same, we can try painting this range with color
      // c[lo] (and avoid paiting that color again on some subranges
      // at [lo + 1 : j - 1]). Note that we still need to find the optimal
      // choices inside [lo + 1 : j - 1].
      if (c[lo] == c[j]) {
        // c[lo] == current_color
        const lli paint_cost = (j - lo + 1) + x[current_color];
        const lli paint_range = rem_range + paint_cost +
                                Solve(lo + 1, j - 1,
                                      /*done_color=*/current_color);
        if (paint_range <= ans) ans = paint_range, path = {j, current_color};
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    c.resize(2 * n), x.resize(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> c[i];
      --c[i];
      c[n + i] = c[i];
    }
    for (auto& xi : x) std::cin >> xi;

    DEBUG if (std::set<int>{4, 127, 239}.contains(hehe)) {
      std::ostringstream str;
      str << n << " |";
      for (const auto ci : c) str << " " << (ci + 1);
      str << " |";
      for (const auto xi : x) str << " " << xi;
      std::cout << "foundit: " << str.str() << "\n";
    }

    memo.resize(2 * n,
                std::vector<std::vector<lli>>(2 * n, std::vector<lli>(2, -1)));
    path_memo.resize(
        2 * n, std::vector<std::vector<Choice>>(2 * n, std::vector<Choice>(2)));
    lli ans = kInf;
    int best_i = 0;
    // Try all rotations of `c` \o/.
    for (int i = 0; i < n; ++i) {
      const lli res = Solve(i, n - 1 + i);
      DEBUG2 std::cout << "\t" << i << ": " << res << "\n";
      if (res < ans) best_i = i;
      ans = std::min(ans, res);
    }
    std::cout << ans << "\n";

    // Reconstruct the path here with `best_i`.
    std::vector<std::tuple<int, int, int, int, int>> path;
    auto AddChoice = [&path, best_i](const int lo, const int hi,
                                     const int color, const int paint_range,
                                     const int depth) {
      path.emplace_back(lo - best_i, hi - best_i, color + (color != -1),
                        paint_range, depth);
    };
    std::queue<std::tuple<int, int, int, int>> q;
    q.emplace(best_i, n - 1 + best_i, -1, 0);
    while (!q.empty()) {
      const auto [lo, hi, done_color, depth] = q.front();
      q.pop();
      if (lo > hi) continue;
      if (lo == hi) {
        if (c[lo] != done_color) AddChoice(lo, hi, c[lo], false, depth);
        continue;
      }

      const Choice& choice = path_memo[lo][hi][done_color == -1];
      q.emplace(choice.j + 1, hi, done_color, depth + 1);
      if (choice.color == -1) {
        for (int i = lo; i <= choice.j; ++i) {
          int k = i;
          while (k + 1 <= choice.j && c[k + 1] == c[i]) ++k;
          if (c[i] != done_color) AddChoice(i, k, c[i], false, depth);
          i = k;
        }
      } else {
        AddChoice(lo, choice.j, choice.color, true, depth);
        q.emplace(lo + 1, choice.j - 1, choice.color, depth + 1);
      }
    }
    std::reverse(path.begin(), path.end());
    std::vector<int> rc = c;
    rc.resize(n);
    std::rotate(rc.begin(), rc.begin() + best_i, rc.end());
    std::cout << "rc:";
    for (const int rci : rc) std::cout << " " << (rci + 1);
    std::cout << "\n";
    for (const auto& [lo, hi, color, paint_range, depth] : path) {
      std::cout << std::string(depth, '\t') << "[" << lo << " : " << hi << "] "
                << (paint_range ? "r " : "i ") << color << "\n";
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    ++hehe;
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
