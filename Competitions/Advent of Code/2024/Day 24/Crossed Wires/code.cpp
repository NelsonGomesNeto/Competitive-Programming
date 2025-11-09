#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

enum class Operation { kAnd, kOr, kXor };
std::vector<std::string> kOperationName = {"AND", "OR", "XOR"};
Operation GetOperation(const std::string& s) {
  if (s == "AND") return Operation::kAnd;
  if (s == "OR") return Operation::kOr;
  return Operation::kXor;
}
std::ostream& operator<<(std::ostream& out, const Operation o) {
  return out << kOperationName[(int)o];
}
bool Eval(const bool a, const Operation op, const bool b) {
  switch (op) {
    case Operation::kAnd:
      return a & b;
    case Operation::kOr:
      return a | b;
    case Operation::kXor:
    default:
      return a ^ b;
  }
}

struct Gate {
  int a;
  Operation op;
  int b, out;
  friend std::ostream& operator<<(std::ostream& out, const Gate& g) {
    return out << g.a << " " << g.op << " " << g.b << " -> " << g.out;
  }
};
const Gate kNil{-1, Operation::kAnd, -1, -1};
struct Problem {
  std::vector<std::pair<std::string, bool>> raw_wires;
  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      raw_gates;
  int WireIndex(const std::string& s) {
    return std::ranges::lower_bound(raw_wires, std::make_pair(s, false)) -
           raw_wires.begin();
  }

  std::vector<bool> wires;
  std::vector<int> requirements;
  std::vector<std::vector<Gate>> graph;
  std::vector<Gate> rev_graph;

  std::string GateString(const Gate& g) {
    std::ostringstream sout;
    sout << raw_wires[g.a].first << " " << g.op << " " << raw_wires[g.b].first
         << " -> " << raw_wires[g.out].first;
    return sout.str();
  }

  void Read() {
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      auto& [wire, value] = raw_wires.emplace_back();
      std::getline(sin, wire, ':');
      sin >> value;
    }
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      auto& [a, op, b, out] = raw_gates.emplace_back();
      std::getline(sin, a, ' ');
      std::getline(sin, op, ' ');
      std::getline(sin, b, ' ');
      sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
      sin >> out;
      auto Has = [&](const std::string& x) {
        return [&](const std::pair<std::string, bool>& wire) {
          return wire.first == x;
        };
      };
      if (std::ranges::find_if(raw_wires, Has(a)) == raw_wires.end())
        raw_wires.emplace_back(a, false);
      if (std::ranges::find_if(raw_wires, Has(b)) == raw_wires.end())
        raw_wires.emplace_back(b, false);
      if (std::ranges::find_if(raw_wires, Has(out)) == raw_wires.end())
        raw_wires.emplace_back(out, false);
    }
    std::ranges::sort(raw_wires);
    auto [l, r] = std::ranges::unique(raw_wires);
    raw_wires.erase(l, r);

    std::cout << "raw_inputs:\n";
    wires.resize(raw_wires.size());
    for (const auto& [i, wire_value] : std::views::enumerate(raw_wires)) {
      const auto& [wire, value] = wire_value;
      std::cout << std::format("\t{}: {}\n", wire, value);
      wires[i] = value;
    }
    std::cout << "raw_gates:\n";
    for (const auto& [a, op, b, out] : raw_gates) {
      std::cout << std::format("\t{} {} {} -> {}\n", a, op, b, out);
    }

    graph.resize(wires.size(), {});
    rev_graph.resize(wires.size(), kNil);
    for (const auto& [a, op, b, out] : raw_gates) {
      const int ai = WireIndex(a), bi = WireIndex(b), outi = WireIndex(out);
      const Gate gate{ai, GetOperation(op), bi, outi},
          b_gate{bi, GetOperation(op), ai, outi};
      graph[ai].push_back(gate);
      graph[bi].push_back(b_gate);
      rev_graph[outi] = gate;
    }
  }

  std::vector<int> TopologicalSort() {
    DEBUG std::cout << "topological_sort:\n";
    std::vector<int> ans;
    std::queue<int> q;
    requirements.clear();
    requirements.resize(wires.size(), 0);
    for (const auto& g : rev_graph) {
      if (g.out == -1) continue;
      requirements[g.out] = 2;
    }
    for (int i = 0; i < wires.size(); ++i) {
      DEBUG std::cout << std::format("\treq: {} {}\n", raw_wires[i].first,
                                     requirements[i]);
      if (requirements[i]) continue;
      q.push(i);
    }
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      if (rev_graph[u].out != -1) ans.push_back(u);

      for (const auto& g : graph[u]) {
        DEBUG std::cout << "\t" << raw_wires[u].first << " | " << GateString(g)
                        << " | " << (g.out == -1 ? -1 : requirements[g.out])
                        << "\n";
        std::fflush(stdout);

        if (g.out == -1 || --requirements[g.out] > 0) continue;
        q.push(g.out);
      }
    }
    return ans;
  }

  void Solve() {
    Read();

    const std::vector<int> eval_order = TopologicalSort();

    std::cout << "eval_order:\n";
    for (const int i : eval_order) {
      const std::string& name = raw_wires[i].first;
      std::cout << std::format("\t{} {}\n", name, i);
    }

    for (const int i : eval_order) {
      const Gate& g = rev_graph[i];
      wires[g.out] = Eval(wires[g.a], g.op, wires[g.b]);
    }

    lli res = 0;
    for (const auto& [wire, value] : std::views::reverse(raw_wires)) {
      if (wire[0] != 'z') continue;
      res <<= 1;
      if (wires[WireIndex(wire)]) res |= 0b1;
    }
    std::cout << std::format("ans: {} | {:b}\n", res, res);
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
