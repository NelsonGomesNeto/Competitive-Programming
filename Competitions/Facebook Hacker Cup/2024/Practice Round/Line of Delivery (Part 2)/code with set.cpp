#include <bits/stdc++.h>
#define DEBUG if (1)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, g;
  std::vector<int> stones;
  std::set<int> line;

  std::pair<int, int> Solve() {
    std::cin >> n >> g;
    stones.resize(n);
    for (int& s : stones) {
      int i = line.size();
      DEBUG2 {
        for (auto it = line.begin(); it != line.end(); ++it, --i) {
          std::cout << "\t" << i << " " << *it << "\n";
        }
        std::cout << "-----------\n";
      }

      std::cin >> s;

      if (line.empty() || *line.begin() > s) {
        DEBUG2 std::cout << "\t\tstart insert: " << s << "\n";
        line.insert(s);
        continue;
      }

      int wall = *line.begin();
      int destination = s + 1;
      auto it = ++line.insert(wall - 1).first;
      while (it != line.end()) {
        const int pos = *it;
        auto nit = std::next(it);
        if (nit == line.end()) {
          line.erase(it);
          DEBUG2 std::cout << "\t\tfinal insert: " << destination << "\n";
          line.insert(destination);
          break;
        }

        if (*nit == (*it) + 1) {
          it = nit;
          ++destination;
        } else if (destination < *nit) {
          line.erase(it);
          DEBUG2 std::cout << "\t\tmid insert: " << destination << "\n";
          line.insert(destination);
          break;
        } else {
          // Recursive insert
          wall = (*nit) - 1;
          ++destination;
          line.erase(it);
          DEBUG2 {
            std::cout << "\t\tdestination: " << destination << "\n";
            std::cout << "\t\trecursive insert: " << wall << "\n";
          }
          it = ++line.insert(wall).first;
        }
      }
    }

    DEBUG if (!(stones.size() == line.size())) {
      std::cout << "LOL!\n";
      std::fflush(stdout);
    }
    else {
      assert(stones.size() == line.size());
    }
    stones.clear();
    stones.reserve(line.size());
    for (int s : line) stones.push_back(s);

    int closest_dist = std::numeric_limits<int>::max(), closest = -1;
    for (int i = 0; i < stones.size(); ++i) {
      const int s = stones[i];
      DEBUG2 std::cout << "\t" << (stones.size() - i) << " " << s << "\n";

      int dist = std::abs(s - g);
      if (dist > closest_dist) continue;
      closest_dist = dist;
      closest = stones.size() - i;
    }

    return std::make_pair(closest, closest_dist);
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto [stone, dist] = test_case.Solve();
    std::cout << "Case #" << t << ": " << stone << " " << dist << "\n";
  }
  return 0;
}