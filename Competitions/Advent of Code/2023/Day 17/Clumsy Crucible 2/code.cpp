#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int inf = 1e9;
const int kMaxD = 4, kMinTurn = 4, kMaxMove = 10;
enum Dir { R, U, D, L };
const int di[4] = {0, -1, 1, 0};
const int dj[4] = {1, 0, 0, -1};
const Dir turn_left[4] = {Dir::U, Dir::L, Dir::R, Dir::D};
const Dir turn_right[4] = {Dir::D, Dir::R, Dir::L, Dir::U};

std::pair<int, int> NextPosition(const int i, const int j, const Dir d) {
  return std::make_pair(i + di[d], j + dj[d]);
}

struct Map {
  std::vector<std::string> map;
  int n, m;

  Map() {}
  Map(const std::vector<std::string>& m)
      : map(m), n(m.size()), m(m[0].size()) {}

  int Dijkstra() {
    std::vector<std::vector<std::vector<std::vector<int>>>> memo(
        n, std::vector<std::vector<std::vector<int>>>(
               m, std::vector<std::vector<int>>(
                      kMaxD, std::vector<int>(kMaxMove + 1, inf))));

    std::priority_queue<std::tuple<int, int, Dir, int, int>> pq;
    pq.emplace(0, 1, Dir::R, 0, 0);
    pq.emplace(0, 1, Dir::D, 0, 0);
    int res = inf;
    while (!pq.empty()) {
      auto [dist, cnt, d, i, j] = pq.top();
      pq.pop();

      dist = -dist;
      if (dist > memo[i][j][d][cnt]) continue;
      if (i == n - 1 && j == m - 1) res = std::min(res, dist);

      auto AddNextState = [&](const Dir nd) {
        const int ni = i + di[nd], nj = j + dj[nd];
        if (ni < 0 || nj < 0 || ni >= n || nj >= m) return;

        const int new_dist = dist + (map[ni][nj] - '0');
        const int new_cnt = nd == d ? cnt + 1 : 1;
        if (new_dist < memo[ni][nj][nd][new_cnt]) {
          pq.emplace(-(memo[ni][nj][nd][new_cnt] = new_dist), new_cnt, nd, ni,
                     nj);
        }
      };
      if (cnt < kMaxMove) {
        AddNextState(d);
      }
      if (cnt >= kMinTurn) {
        AddNextState(turn_left[d]);
        AddNextState(turn_right[d]);
      }
    }
    return res;
  }
};
Map map;

int main() {
  std::vector<std::string> m;
  for (std::string line; std::getline(std::cin, line);) {
    m.push_back(line);
  }
  map = Map(m);

  int ans = map.Dijkstra();
  std::cout << ans << std::endl;

  return 0;
}