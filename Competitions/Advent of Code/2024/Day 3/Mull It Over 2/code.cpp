#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<std::string> lines;

  bool FindSubstring(const std::string& line, const std::string& target,
                     int& i) {
    if (i + (int)target.size() > (int)line.size() || line[i] != target[0])
      return false;

    const std::string substring = line.substr(i, target.size());
    if (substring != target) return false;

    i += target.size();
    return true;
  }

  std::pair<int, int> FindMul(const std::string& line, int i) {
    auto nil = std::make_pair(-1, i);

    if (!FindSubstring(line, "mul(", i)) return nil;

    auto GetNum = [&]() -> int {
      if (i >= line.size() || !std::isdigit(line[i])) return -1;

      const int a_start = i;
      while (i + 1 < line.size() && std::isdigit(line[i + 1])) ++i;
      const int a_end = i;
      const int size = a_end - a_start + 1;
      if (size > 3) return -1;

      i = a_end + 1;
      std::istringstream num_in(line.substr(a_start, size));
      int num;
      num_in >> num;
      return num;
    };
    const int a = GetNum();
    if (a == -1) return nil;

    if (!FindSubstring(line, ",", i)) return nil;

    const int b = GetNum();
    if (b == -1) return nil;

    if (!FindSubstring(line, ")", i)) return nil;

    return std::make_pair(a * b, i - 1);
  }

  enum class Do { kNil, kDo, kDont };

  std::pair<Do, int> FindDo(const std::string& line, int i) {
    if (FindSubstring(line, "do()", i)) return std::make_pair(Do::kDo, i - 1);
    if (FindSubstring(line, "don't()", i))
      return std::make_pair(Do::kDont, i - 1);
    return std::make_pair(Do::kNil, i);
  }

  void Solve() {
    for (std::string line; std::getline(std::cin, line);) {
      lines.push_back(line);
    }

    bool to_mul = true;
    lli ans = 0;
    for (const auto& line : lines) {
      for (int i = 0; i < line.size(); ++i) {
        const auto [kind, do_nxt_i] = FindDo(line, i);
        const auto [ab, mul_nxt_i] = FindMul(line, i);

        DEBUG std::cout << "\t" << i << " | mul: " << ab << ", " << mul_nxt_i
                        << " | do: "
                        << std::vector<std::string>{"nil", "do",
                                                    "dont"}[(int)kind]
                        << ", " << do_nxt_i << "\n";

        if (kind != Do::kNil) {
          to_mul = kind == Do::kDo ? true : false;
          i = do_nxt_i;
          continue;
        }

        if (ab == -1) continue;
        i = mul_nxt_i;
        ans += to_mul ? ab : 0;
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
