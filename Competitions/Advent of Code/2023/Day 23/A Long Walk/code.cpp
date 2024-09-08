#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// D, R, U, L
const int di[4] = {1, 0, -1, 0};
const int dj[4] = {0, 1, 0, -1};
int GetDir(const char dir) {
  switch (dir) {
    case 'v':
      return 0;
    case '>':
      return 1;
    case '^':
      return 2;
    case '<':
    default:
      return 3;
  }
}
struct Pos {
  int i, j;
  bool operator<(const Pos& other) const {
    return i < other.i || (i == other.i && j < other.j);
  }
  bool operator==(const Pos& other) const {
    return i == other.i && j == other.j;
  }
  friend std::ostream& operator<<(std::ostream& out, const Pos& p) {
    out << "(" << p.i << " " << p.j << ")";
    return out;
  }
  Pos NextDir(const int d) { return Pos{i + di[d], j + dj[d]}; }
};
constexpr Pos kStartPos{0, 1};

struct HikingTrails {
  std::vector<std::string> map;
  int n, m;
  Pos end_pos;
  HikingTrails(const std::vector<std::string>& map_)
      : map(map_),
        n(map.size()),
        m(map.empty() ? 0 : map[0].size()),
        end_pos({n - 1, m - 2}) {}
  HikingTrails() : HikingTrails(std::vector<std::string>{}) {}
  HikingTrails(const HikingTrails& h) : HikingTrails(h.map) {}
  HikingTrails& operator=(const HikingTrails& other) {
    map = other.map, n = other.n, m = other.m, end_pos = other.end_pos;
    return *this;
  }

  friend std::istream& operator>>(std::istream& in, HikingTrails& h) {
    std::vector<std::string> map;
    for (std::string line; std::getline(in, line);) {
      map.push_back(line);
    }
    // TODO: Investigate this copy constructor.
    h = HikingTrails(map);
    // h.map = map;
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const HikingTrails& h) {
    out << h.n << " " << h.m << " | " << h.end_pos << "\n";
    for (const std::string& line : h.map) {
      out << line << "\n";
    }
    return out;
  }

  struct State {
    Pos pos;
    std::set<Pos> visited;
  };

  bool ValidPos(const State& state, const Pos& next_pos) {
    const int i = next_pos.i, j = next_pos.j;
    return i >= 0 && j >= 0 && i < n && j < m && map[i][j] != '#' &&
           !state.visited.count(next_pos);
  }

  void PrintPath(const std::set<Pos>& visited) const {
    std::ostringstream sout;
    sout << "visited: " << visited.size() << "\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (visited.count(Pos{i, j}))
          sout << 'O';
        else
          sout << map[i][j];
      }
      sout << "\n";
    }
    std::cout << sout.str();
  }

  int Solve() {
    std::vector<std::vector<int>> memo(n, std::vector<int>(m, -1));
    std::queue<State> q;
    q.emplace(kStartPos);
    int res = 0;
    while (!q.empty()) {
      auto state = q.front();
      q.pop();
      state.visited.insert(state.pos);
      // if (state.visited.size() < memo[state.pos.i][state.pos.j]) {
      //   continue;
      // }
      if (state.pos == end_pos) {
        res = std::max(res, (int)state.visited.size());
        // PrintPath(state.visited);
        continue;
      }

      if (map[state.pos.i][state.pos.j] != '.') {
        const Pos next_pos =
            state.pos.NextDir(GetDir(map[state.pos.i][state.pos.j]));
        if (ValidPos(state, next_pos)) q.emplace(next_pos, state.visited);
        continue;
      }

      for (int d = 0; d < 4; ++d) {
        const Pos next_pos = state.pos.NextDir(d);
        if (!ValidPos(state, next_pos)) continue;
        // int& best = memo[next_pos.i][next_pos.j];
        // if (best == -1 || state.visited.size() + 1 > best) {
        //   best = state.visited.size() + 1;
        // } else {
        //   continue;
        // }
        q.emplace(next_pos, state.visited);
      }
    }
    return res - 1;
  }
};
HikingTrails hiking_trails;

int main() {
  std::cin >> hiking_trails;

  std::cout << hiking_trails;

  int ans = hiking_trails.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}