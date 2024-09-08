#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

struct Component {
  const std::string name;
  const int id;
  std::vector<std::reference_wrapper<const Component>> connections;

  Component(const std::string& name_, const int id_) : name(name_), id(id_) {}

  void Add(const Component& v) { connections.push_back(v); }

  ~Component() { DEBUG2 std::cout << "\tDestroying " << name << "\n"; }

  std::string ToString() const {
    std::ostringstream sout;
    sout << name << " ->";
    for (const Component& c : connections) {
      sout << " " << c.name;
    }
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Component& c) {
    return out << c.ToString();
  }
};
struct Apparatus {
  const std::vector<Component> components;
  const std::vector<std::pair<int, int>> edges;

  Apparatus(const std::map<std::string, std::vector<std::string>>& graph_,
            const std::set<std::string>& nodes_)
      : components([&]() {
          std::vector<Component> cs;
          cs.reserve(nodes_.size());
          std::map<std::string, int> pos;
          for (const std::string& u : nodes_) {
            const int position = cs.size();
            pos[u] = position;
            cs.emplace_back(u, position);
          }

          for (const auto& [u, vs] : graph_) {
            const int u_pos = pos[u];
            for (const std::string& v : vs) {
              const int v_pos = pos[v];
              cs[u_pos].Add(cs[v_pos]);
              cs[v_pos].Add(cs[u_pos]);
            }
          }
          return cs;
        }()),
        edges([&]() {
          std::vector<std::pair<int, int>> es;
          for (const Component& u : components) {
            for (const Component& v : u.connections) {
              if (u.id > v.id) continue;
              es.emplace_back(u.id, v.id);
            }
          }
          return es;
        }()) {}
  static Apparatus Read() {
    std::set<std::string> nodes;
    std::map<std::string, std::vector<std::string>> graph;
    for (std::string line; std::getline(std::cin, line);) {
      std::string u;
      std::istringstream line_in(line);
      std::getline(line_in, u, ':');
      nodes.insert(u);
      line_in.ignore(1);
      for (std::string v; std::getline(line_in, v, ' ');) {
        graph[u].push_back(v), graph[v].push_back(u);
        nodes.insert(v);
      }
    }
    return Apparatus(graph, nodes);
  }

  ~Apparatus() { DEBUG2 std::cout << "Destroying Apparatus\n"; }

  std::string ToString() const {
    std::ostringstream sout;
    for (const Component& c : components) {
      sout << c << "\n";
    }
    return sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Apparatus& a) {
    return out << a.ToString();
  }

  std::vector<int> GetComponentsSizes(
      const std::vector<std::pair<int, int>>& blocked_edges) const {
    std::vector<int> visited(components.size(), 0);
    auto is_blocked_edge = [&](const int u, const int v) {
      for (const auto [i, j] : blocked_edges) {
        if ((u == i && v == j) || (u == j && v == i)) return true;
      }
      return false;
    };
    auto bfs = [&](const int start, const int color) {
      std::queue<int> q;
      q.push(start);
      while (!q.empty()) {
        const int i = q.front();
        q.pop();

        if (visited[i]) continue;
        visited[i] = color;
        const Component& u = components[i];

        for (const Component& v : u.connections) {
          if (is_blocked_edge(u.id, v.id)) continue;
          q.push(v.id);
        }
      }
    };

    std::vector<int> components_sizes;
    for (int i = 0; i < components.size(); ++i) {
      if (visited[i]) continue;
      components_sizes.push_back(0);
      bfs(i, components_sizes.size());
    }
    for (const int group : visited) {
      ++components_sizes[group - 1];
    }
    return components_sizes;
  }
  std::vector<std::tuple<int, int, int>> FindHotEdges() const {
    std::vector<std::vector<int>> edge_visits(
        components.size(), std::vector<int>(components.size(), 0));
    std::vector<bool> visited(components.size(), false);
    std::vector<int> previous(components.size(), -1);
    auto bfs = [&](const Component& start) {
      std::fill(visited.begin(), visited.end(), false);
      std::fill(previous.begin(), previous.end(), -1);

      std::queue<std::pair<int, int>> q;
      q.emplace(start.id, -1);
      while (!q.empty()) {
        const auto [i, prv] = q.front();
        q.pop();
        if (previous[i] == -1) previous[i] = prv;

        if (visited[i]) continue;
        visited[i] = true;
        const Component& u = components[i];

        for (const Component& v : u.connections) {
          q.emplace(v.id, u.id);
        }
      }

      for (const Component& end : components) {
        for (int u = end.id; u != start.id; u = previous[u]) {
          assert(previous[u] != -1);
          ++edge_visits[previous[u]][u];
        }
      }
    };
    for (const Component& u : components) bfs(u);

    std::vector<std::tuple<int, int, int>> hot_edges;
    for (int i = 0; i < components.size(); ++i) {
      bool first = true;
      for (int j = i + 1; j < components.size(); ++j) {
        if (!edge_visits[i][j]) continue;
        hot_edges.emplace_back(edge_visits[i][j], i, j);
      }
    }
    std::sort(hot_edges.begin(), hot_edges.end());
    std::reverse(hot_edges.begin(), hot_edges.end());
    DEBUG for (const auto [cnt, u, v] : hot_edges) {
      std::cout << components[u].name << "," << components[v].name << "=" << cnt
                << "\n";
    }
    return hot_edges;
  }
  lli Solve() const {
    std::vector<std::tuple<int, int, int>> hot_edges = FindHotEdges();

    for (int i = 0; i < hot_edges.size(); ++i) {
      const auto [_, iu, iv] = hot_edges[i];
      for (int j = i + 1; j < hot_edges.size(); ++j) {
        const auto [_, ju, jv] = hot_edges[j];
        for (int k = j + 1; k < hot_edges.size(); ++k) {
          const auto [_, ku, kv] = hot_edges[k];
          std::vector<int> components_sizes =
              GetComponentsSizes({{iu, iv}, {ju, jv}, {ku, kv}});
          if (components_sizes.size() <= 1) continue;
          assert(components_sizes.size() == 2);
          return (lli)components_sizes[0] * components_sizes[1];
        }
      }
    }

    return -1;
  }
};

int main() {
  Apparatus a = Apparatus::Read();

  DEBUG std::cout << a << "\n";

  const lli ans = a.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}
