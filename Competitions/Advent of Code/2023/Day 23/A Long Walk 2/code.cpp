#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// D, R, U, L
const int di[4] = {1, 0, -1, 0};
const int dj[4] = {0, 1, 0, -1};
struct Pos {
  int i, j;
  bool operator<(const Pos& other) const {
    return i < other.i || (i == other.i && j < other.j);
  }
  bool operator==(const Pos& other) const {
    return i == other.i && j == other.j;
  }
  friend std::ostream& operator<<(std::ostream& out, const Pos& p) {
    out << "(" << p.i << ", " << p.j << ")";
    return out;
  }
  Pos NextDir(const int d) const { return Pos{i + di[d], j + dj[d]}; }
  int Dist(const Pos& other) const {
    return abs(i - other.i) + abs(j - other.j);
  }
};
constexpr Pos kStartPos{0, 1};

struct HikingTrails {
  std::vector<std::string> map;
  int n, m;
  Pos end_pos;
  std::set<Pos> nodes;
  std::vector<std::vector<int>> nodes_id;
  std::vector<std::vector<std::vector<std::pair<Pos, int>>>> graph;

  HikingTrails(const std::vector<std::string>& map_)
      : map(map_),
        n(map.size()),
        m(map.empty() ? 0 : map[0].size()),
        end_pos({n - 1, m - 2}),
        nodes_id(n, std::vector<int>(m, -1)),
        graph(n, std::vector<std::vector<std::pair<Pos, int>>>(
                     m, std::vector<std::pair<Pos, int>>{})) {
    if (n == 0 || m == 0) return;

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        const Pos p{i, j};
        if (!ValidPos(p)) continue;

        int next_cnt = 0;
        for (int d = 0; d < 4; ++d) next_cnt += ValidPos(p.NextDir(d));
        if (next_cnt == 1 || next_cnt > 2) {
          nodes_id[p.i][p.j] = nodes.size();
          nodes.insert(p);
        }
      }

    auto add_edge = [&](const Pos& u, const Pos& v, int d) {
      graph[u.i][u.j].emplace_back(v, d);
      graph[v.i][v.j].emplace_back(u, d);
    };
    for (const Pos& u : nodes) {
      std::set<Pos> visited;
      std::queue<std::pair<Pos, int>> q;
      q.emplace(u, 0);
      while (!q.empty()) {
        const auto [v, dist] = q.front();
        q.pop();
        if (visited.count(v)) continue;
        visited.insert(v);

        if (!(u == v) && nodes.count(v)) {
          add_edge(u, v, dist);
          continue;
        }

        for (int d = 0; d < 4; ++d) {
          const Pos next_pos = v.NextDir(d);
          if (!ValidPos(next_pos)) continue;
          q.emplace(next_pos, dist + 1);
        }
      }
    }
  }
  HikingTrails() : HikingTrails(std::vector<std::string>{}) {}
  HikingTrails(const HikingTrails& h) : HikingTrails(h.map) {}

  friend std::istream& operator>>(std::istream& in, HikingTrails& h) {
    std::vector<std::string> map;
    for (std::string line; std::getline(in, line);) map.push_back(line);
    h = HikingTrails(map);
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const HikingTrails& h) {
    out << "n x m: " << h.n << " " << h.m << " | end_pos: " << h.end_pos
        << " | nodes: " << h.nodes.size() << "\n";

    const int log_n = std::ceil(std::log10(h.n));
    for (int j = 0; j < h.m; ++j) out << (j % 10);
    out << "\n";
    for (int i = 0; i < h.n; ++i) {
      for (int j = 0; j < h.m; ++j) {
        if (h.nodes.count(Pos{i, j}))
          out << 'O';
        else
          out << (h.map[i][j] == '#' ? '#' : '.');
      }
      out << std::setfill(' ') << std::setw(log_n) << i << "\n";
    }
    for (const Pos u : h.nodes) {
      out << u << " ->";
      for (const auto [v, d] : h.graph[u.i][u.j]) out << " " << v << "," << d;
      out << "\n";
    }
    return out;
  }

  bool ValidPos(const Pos& pos) {
    const int i = pos.i, j = pos.j;
    return i >= 0 && j >= 0 && i < n && j < m && map[i][j] != '#';
  }

  void PrintPath(const std::set<Pos>& visited) const {
    std::ostringstream sout;
    sout << "visited: " << visited.size() << "\n";

    const int log_n = std::ceil(std::log10(n));
    for (int j = 0; j < m; ++j) sout << (j % 10);
    sout << "\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        const Pos p{i, j};
        if (visited.count(p))
          sout << 'X';
        else if (nodes.count(p))
          sout << 'O';
        else
          sout << (map[i][j] == '#' ? '#' : '.');
      }
      sout << std::setfill(' ') << std::setw(log_n) << i << "\n";
    }
    std::cout << sout.str();
  }

  struct State {
    Pos pos;
    lli visited_mask;
    int dist;

    bool operator<(const State& other) const {
      return dist < other.dist ||
             (dist == other.dist && visited_mask < other.visited_mask);
    }
  };
  lli NodeMask(const Pos& p) const { return 1LL << nodes_id[p.i][p.j]; }
  void Visit(const Pos& p, lli& visited_mask) const {
    visited_mask |= NodeMask(p);
  }
  bool Visited(const Pos& p, const lli& visited_mask) const {
    return (visited_mask & NodeMask(p)) != 0;
  }
  void Visit(const Pos& p, State& s) const { Visit(p, s.visited_mask); }
  bool Visited(const Pos& p, const State& s) const {
    return Visited(p, s.visited_mask);
  }

  bool EndReachable(const State& state) {
    lli visited_mask = state.visited_mask;
    std::queue<Pos> q;
    q.push(state.pos);
    while (!q.empty()) {
      const Pos p = q.front();
      q.pop();

      if (p == end_pos) return true;

      if (Visited(p, visited_mask)) continue;
      Visit(p, visited_mask);

      for (const auto& [next_pos, _] : graph[p.i][p.j]) {
        if (Visited(next_pos, visited_mask)) continue;
        q.emplace(next_pos);
      }
    }
    return false;
  }

  int Solve() {
    std::set<State> pq;
    pq.emplace(kStartPos, 0, 0);
    int reaches = 0;
    int res = 0;
    while (!pq.empty()) {
      const auto state = *pq.begin();
      pq.erase(pq.begin());

      if (state.pos == end_pos) {
        if (state.dist > res) {
          std::cout << "curr: " << state.dist << " | " << reaches << "\n";
          std::fflush(stdout);
        }
        res = std::max(res, state.dist);
        // PrintPath(state.visited);
        continue;
      }

      for (const auto& [next_pos, dist] : graph[state.pos.i][state.pos.j]) {
        if (Visited(next_pos, state)) continue;
        State next_state{next_pos, state.visited_mask, state.dist + dist};
        if (!EndReachable(next_state)) continue;
        Visit(next_pos, next_state);
        pq.emplace(next_state);
      }
    }
    return res;
  }
};
HikingTrails hiking_trails;

int main() {
  std::cin >> hiking_trails;

  std::cout << hiking_trails;

  const int ans = hiking_trails.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}