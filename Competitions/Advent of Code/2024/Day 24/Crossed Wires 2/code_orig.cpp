#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

/*
Oh wow, I suffered A LOT but I also had a blast hahahaha.
I had to manually find 2 swaps and brute force the other 2 hahaha.

But... Is it possible to find ALL swaps in programatically?
*/

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
  bool ReadWire(const int i) { return wires[i]; }
  void SetWire(const int i, const bool value) { wires[i] = value; }

  std::vector<bool> wires;
  std::vector<int> requirements;
  std::vector<std::vector<Gate>> graph;
  std::vector<Gate> rev_graph;

  std::string GateString(const Gate& g) {
    std::ostringstream sout;
    if (g.out == -1)
      sout << "nil";
    else
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
    for (const auto& [i, raw_gate] : std::views::enumerate(raw_gates)) {
      const auto& [a, op, b, out] = raw_gate;
      std::cout << std::format("\t{} | {} {} {} -> {}\n", i, a, op, b, out);
    }
  }

  void BuildGraph() {
    if (graph.empty())
      graph.resize(wires.size(), {});
    else {
      for (auto& list : graph) list.clear();
    }
    if (rev_graph.empty())
      rev_graph.resize(wires.size(), kNil);
    else {
      for (auto& g : rev_graph) g = kNil;
    }
    for (const auto& [a, op, b, out] : raw_gates) {
      const int ai = WireIndex(a), bi = WireIndex(b), outi = WireIndex(out);
      const Gate gate{ai, GetOperation(op), bi, outi},
          b_gate{bi, GetOperation(op), ai, outi};
      graph[ai].push_back(gate);
      graph[bi].push_back(b_gate);
      rev_graph[outi] = gate;
    }
  }
  void TopologicalEval() {
    DEBUG std::cout << "topological_sort:\n";
    std::queue<int> q;
    if (requirements.empty()) requirements.resize(wires.size(), 0);
    for (const auto& g : rev_graph) {
      if (g.out == -1)
        requirements[g.out] = 0;
      else
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
      const auto& hehe = rev_graph[u];
      if (hehe.out != -1) {
        SetWire(hehe.out, Eval(ReadWire(hehe.a), hehe.op, ReadWire(hehe.b)));
      }

      for (const auto& g : graph[u]) {
        DEBUG std::cout << "\t" << raw_wires[u].first << " | " << GateString(g)
                        << " | " << (g.out == -1 ? -1 : requirements[g.out])
                        << "\n";
        std::fflush(stdout);

        if (g.out == -1 || --requirements[g.out] > 0) continue;
        q.push(g.out);
      }
    }
  }

  void PrintGraph() {
    std::cout << "\tPrintGraph:\n";
    auto Bfs = [&](const int start) {
      std::vector<bool> visited(wires.size(), false);
      int visits = 0;
      std::queue<std::pair<int, int>> q;
      q.emplace(start, 0);
      while (!q.empty()) {
        const auto [u, depth] = q.front();
        q.pop();
        if (visited[u]) continue;
        visited[u] = true;
        const Gate& g = rev_graph[u];
        if (g.a == -1) continue;
        ++visits;

        DEBUG2 std::cout << std::format("{}{} | {}\n", std::string(depth, ' '),
                                        raw_wires[u].first, GateString(g));
        q.emplace(g.a, depth + 1);
        q.emplace(g.b, depth + 1);
      }
      return visits;
    };
    for (const auto& [wire, value] : std::views::reverse(raw_wires)) {
      if (wire[0] != 'z') continue;
      // if (!std::set<std::string>{"z23", "z24"}.count(wire)) continue;
      const int visits = Bfs(WireIndex(wire));
      std::cout << std::format("{}: {}\n", wire, visits);
    }
  }

  lli ReadNumberFromWires(const char prefix) {
    lli res = 0;
    for (const auto& [wire, value] : std::views::reverse(raw_wires)) {
      if (wire[0] != prefix) continue;
      res <<= 1;
      if (ReadWire(WireIndex(wire))) res |= 0b1;
    }
    return res;
  }

  lli RunCircuit(const bool verbose = false, const bool build_graph = true) {
    if (build_graph) BuildGraph();
    if (verbose) PrintGraph();
    TopologicalEval();
    return ReadNumberFromWires('z');
  }

  int TestXY(const lli x, const lli y) {
    const lli correct_ans = x + y;
    std::vector<bool> prv_wires = wires;
    for (int j = 0; j < 45; ++j) {
      wires[WireIndex(std::format("x{:02d}", j))] = (x >> j) & 1;
      wires[WireIndex(std::format("y{:02d}", j))] = (y >> j) & 1;
    }
    int res = std::__popcount(
        correct_ans ^ RunCircuit(/*verbose=*/false, /*build_graph=*/false));
    wires = prv_wires;
    return res;
  }
  int TestCircuit() {
    int misses = TestXY(21127838400205LL, 28371358894105LL);
    for (int i = 44; i < 45; i += 10) {
      lli x = 1LL << i;
      lli y = x;
      lli correct_ans = x + y;
      misses += TestXY(x, y);

      x = (1LL << (i + 1)) - 1;
      y = x;
      correct_ans = x + y;
      misses += TestXY(x, y);

      x = 1LL << i;
      y = (1LL << (i + 1)) - 1;
      correct_ans = x + y;
      misses += TestXY(x, y);
    }
    return misses;
  }

  void MakeSwap(const int a, const int b) {
    std::swap(std::get<3>(raw_gates[a]), std::get<3>(raw_gates[b]));
  }

  void OldSearch() {
    int best = TestCircuit();
    std::vector<std::pair<int, int>> valid_swaps;

    MakeSwap(33, 88);
    MakeSwap(136, 186);
    std::unordered_set<int> done{33, 88, 136, 186};

    int new_best = best;
    for (int i = 0; i < raw_gates.size(); ++i) {
      if (done.count(i)) continue;
      for (int j = i + 1; j < raw_gates.size(); ++j) {
        if (done.count(j)) continue;
        ;
        MakeSwap(i, j);
        BuildGraph();
        const int res = TestCircuit();
        if (res < best) {
          new_best = std::min(new_best, res);
          valid_swaps.emplace_back(i, j);
          // std::cout << "\t" << std::get<3>(raw_gates[i]) << " "
          //           << std::get<3>(raw_gates[j]) << "\n";
        }
        MakeSwap(i, j);
      }
    }
    std::cout << "valid_swaps: " << (int)valid_swaps.size() << "\n";

    std::vector<std::tuple<int, int, int, int>> valid_swaps_pairs;
    for (int i = 0; i < valid_swaps.size(); ++i) {
      for (int j = i + 1; j < valid_swaps.size(); ++j) {
        const auto [a, b] = valid_swaps[i];
        const auto [c, d] = valid_swaps[j];
        if (a == c || a == d || b == c || b == d) continue;
        MakeSwap(a, b);
        MakeSwap(c, d);
        BuildGraph();
        if (TestCircuit() < best) {
          valid_swaps_pairs.emplace_back(a, b, c, d);
        }
        MakeSwap(a, b);
        MakeSwap(c, d);
      }
    }
    std::cout << "valid_swaps_pairs: " << (int)valid_swaps_pairs.size() << "\n";

    std::vector<std::vector<int>> swaps_four;
    for (int i = 0; i < valid_swaps_pairs.size(); ++i) {
      for (int j = i + 1; j < valid_swaps_pairs.size(); ++j) {
        const auto [a, b, c, d] = valid_swaps_pairs[i];
        const auto [e, f, g, h] = valid_swaps_pairs[j];
        if ((std::set<int>{a, b, c, d, e, f, g, h}.size()) < 8) continue;
        MakeSwap(a, b);
        MakeSwap(c, d);
        MakeSwap(e, f);
        MakeSwap(g, h);
        BuildGraph();
        if (TestCircuit() == 0) {
          swaps_four.push_back({a, b, c, d, e, f, g, h});
          std::cout << std::get<3>(raw_gates[a]) << " "
                    << std::get<3>(raw_gates[b]) << " "
                    << std::get<3>(raw_gates[c]) << " "
                    << std::get<3>(raw_gates[d]) << " "
                    << std::get<3>(raw_gates[e]) << " "
                    << std::get<3>(raw_gates[f]) << " "
                    << std::get<3>(raw_gates[g]) << " "
                    << std::get<3>(raw_gates[h]) << "\n";
          std::fflush(stdout);
          return;
        }
        MakeSwap(a, b);
        MakeSwap(c, d);
        MakeSwap(e, f);
        MakeSwap(g, h);
      }
    }
    std::cout << "swaps_four: " << (int)swaps_four.size() << "\n";
  }

  void FindSwaps() {
    std::cout << "find_swaps:\n";
    std::unordered_set<int> done{79, 124, 88, 33, 136, 186};
    // pbv,z16
    MakeSwap(79, 124);
    // z23,qqp
    MakeSwap(88, 33);
    // qff,qnw
    MakeSwap(136, 186);

    for (int i = 0; i < raw_gates.size(); ++i) {
      if (done.count(i)) continue;
      for (int j = i + 1; j < raw_gates.size(); ++j) {
        if (done.count(j)) continue;
        MakeSwap(i, j);
        BuildGraph();
        if (TestCircuit() == 0) {
          std::vector<int> candidates(done.begin(), done.end());
          candidates.push_back(i), candidates.push_back(j);
          std::vector<std::string> candidates_str;
          for (const int c : candidates)
            candidates_str.push_back(std::get<3>(raw_gates[c]));
          std::ranges::sort(candidates_str);
          std::ostringstream sout;
          for (const auto& c : candidates_str) {
            if (!sout.str().empty()) sout << ",";
            sout << c;
          }
          std::println("\t{}", sout.str());
          std::fflush(stdout);
        }
        MakeSwap(i, j);
      }
    }
  }

  void Solve() {
    Read();
    RunCircuit(/*verbose=*/true);

    const lli x = ReadNumberFromWires('x');
    const lli y = ReadNumberFromWires('y');
    std::cout << std::format("x: {} |  {:b}\n", x, x);
    std::cout << std::format("y: {} |  {:b}\n", y, y);
    const lli correct_ans = x + y;
    std::cout << std::format("t: {} | {:b}\n", correct_ans, correct_ans);
    const lli ans = ReadNumberFromWires('z');
    std::cout << std::format("a: {} | {:b}\n", ans, ans);

    const lli incorrect_bits = correct_ans ^ ans;
    const int incorrect_bits_count = std::__popcount(incorrect_bits);
    std::cout << std::format("i:{}{:b} | {}\n", std::string(23, ' '),
                             incorrect_bits, incorrect_bits_count);
    std::println("ans: {}", ans);

    FindSwaps();

    // MakeSwap(33, 88);
    // MakeSwap(136, 186);
    // MakeSwap(141, 36);
    // MakeSwap(124, 79);
    // BuildGraph();
    // std::cout << "misses: " << TestCircuit() << "\n";
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
