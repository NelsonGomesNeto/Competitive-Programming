#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kRepeats = 3;
int kN = -1, kQueries = -1, kMaxValue = -1;

using time_precision = std::chrono::milliseconds;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  std::random_device os_seed;

  std::vector<int> values, queries;
  auto Reset = [&]() {
    values.resize(kN);
    queries.resize(kQueries);
    std::mt19937 generator(os_seed());
    std::uniform_int_distribution<int> distribution(0, kMaxValue);
    if (!values.empty())
      std::generate(values.begin(), values.end(),
                    [&]() { return distribution(generator); });
    if (!queries.empty())
      std::generate(queries.begin(), queries.end(),
                    [&]() { return distribution(generator); });
  };

  auto Evaluate = [&](std::function<int()> f, const std::string& name) {
    const auto start = std::chrono::high_resolution_clock::now();
    const int res = f();
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    DEBUG std::cout << name << " | time: " << duration << " | res: " << res
                    << "\n";
    return duration;
  };

  auto Vector = [&]() {
    std::vector<int> a;
    for (const int v : values) a.push_back(v);

    std::sort(a.begin(), a.end());

    int res = 0;
    for (const int q : queries) {
      auto it = std::lower_bound(a.begin(), a.end(), q);
      res += it != a.end() && *it == q;
    }
    return res;
  };
  auto Set = [&]() {
    std::set<int> a(values.begin(), values.end());
    // for (const int v : values) a.insert(v);

    int res = 0;
    for (const int q : queries) {
      res += a.count(q) != 0;
    }
    return res;
  };
  auto HashSet = [&]() {
    std::unordered_set<int> a(values.begin(), values.end());
    // for (const int v : values) a.insert(v);

    int res = 0;
    for (const int q : queries) {
      res += a.count(q) != 0;
    }
    return res;
  };

  for (const auto [n, q, max_value] :
       std::vector<std::tuple<int, int, int>>{{(int)1e5, 0, (int)1e5},
                                              {(int)1e6, 0, (int)1e6},
                                              {(int)1e7, 0, (int)1e7},
                                              {(int)1e5, (int)1e5, (int)1e5},
                                              {(int)1e6, (int)1e6, (int)1e6},
                                              {(int)1e7, (int)1e7, (int)1e7}}) {
    kN = n, kQueries = q, kMaxValue = max_value;

    std::map<std::string, time_precision> average_by_type;
    for (int i = 0; i < kRepeats; ++i) {
      Reset();
      for (const auto& [f, name] :
           std::vector<std::pair<std::function<int()>, std::string>>{
               {Vector, "Vector "}, {Set, "Set    "}, {HashSet, "HashSet"}}) {
        const auto duration = Evaluate(f, name);
        average_by_type[name] += duration;
      }
    }
    std::cout << "------------\n";
    std::cout << std::setprecision(0) << std::scientific << "N: " << (double)kN
              << ", Queries: " << (double)kQueries
              << ", MaxValue: " << (double)kMaxValue
              << " | Repeats: " << kRepeats << "\n";
    for (auto& [name, total] : average_by_type) {
      total /= kRepeats;
      std::cout << name << " | average time: " << total << "\n";
    }
    std::fflush(stdout);
  }

  return 0;
}
