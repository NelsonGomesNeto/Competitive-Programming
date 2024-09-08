#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

struct History {
  std::vector<std::vector<int>> h;

  int Predict() {
    h.back().push_back(0);
    for (int i = h.size() - 2; i >= 0; --i) {
      h[i].push_back(h[i].back() + h[i + 1].back());
    }

    return h[0].back();
  }

  void Build() {
    for (int i = 0;
         i < h.size() && !std::all_of(h[i].begin(), h[i].end(),
                                      [](const int a) { return a == 0; });
         ++i) {
      h.push_back({});
      for (int j = 1; j < h[i].size(); ++j) {
        h.back().push_back(h[i][j] - h[i][j - 1]);
      }
    }
  }

  friend std::istream& operator>>(std::istream& stream, History& h) {
    std::string line;
    std::getline(stream, line);
    if (line.empty()) return stream;

    std::istringstream lin(line);

    h.h.clear();
    h.h.push_back({});
    int a;
    while (lin >> a) {
      h.h[0].push_back(a);
    }
    h.Build();
    return stream;
  }
};
std::vector<History> histories;

int main() {
  History h;
  while (cin >> h) {
    histories.push_back(h);
  }

  int ans = 0;
  for (auto& h : histories) {
    ans += h.Predict();
  }
  std::cout << ans << std::endl;

  return 0;
}
