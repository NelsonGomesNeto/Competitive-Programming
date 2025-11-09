#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

/*
Oh wow, I suffered A LOT but I also had a blast hahahaha.
I had to manually find 2 swaps and brute force the other 2 hahaha.
  My code was severely unoptimized haha.

But... Is it possible to find ALL swaps in programatically?

ABSOLUTELY, the key is to have a good test suite so that all inputs are
evaluated individually (including the carry):
  For every bit:
    test x = 1LL << bit, y = 0
    test x = 0, y = 1LL << bit
    test x = 1LL << bit, y = 1LL bit
  We have 45 bits, so this leads to 135 test cases.

For every gate output swap:
  Run the circuit over the whole test suite
  Then, pick the swap which minimizes the error on the tests

Running the circuit for every test is expensive, but I managed to get ~20s! \o/
BUT, you can evaluate all tests cases in a single circuit run! (500ms!) \o/
  Just make it so every "bit" ("wire" or "input/output" from gates) holds a
  bitmask as value instead of a bool. Then, you can encode the whole test suite
  an compute everything at once since the circuit topology doesn't change over
  the tests, only on swaps.

This was WILD, but is definitely one of my favorite problems so far.
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
using BitValue = std::bitset<45 * 3 + 1>;
BitValue Eval(const BitValue& a, const Operation op, const BitValue& b) {
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
struct Bit {
  std::string name;
  BitValue value;
  bool undefined;
  // This bit can be used by more than one gate.
  std::vector<int> input_gate_indexes;
  auto operator<=>(const Bit& other) const { return name <=> other.name; }
  bool operator==(const Bit& other) const { return name == other.name; };
};
struct Problem {
  std::vector<std::pair<std::string, int>> raw_bits;
  std::vector<std::tuple<std::string, std::string, std::string, std::string>>
      raw_gates;
  std::vector<Bit> bits;
  std::vector<std::reference_wrapper<Bit>> input_bits, not_input_bits,
      output_bits;
  std::vector<Gate> gates;
  std::vector<std::reference_wrapper<Gate>> input_gates;
  int BitIndex(const std::string& s) {
    return std::ranges::lower_bound(bits, Bit{.name = s}) - bits.begin();
  }
  bool IsGateReady(const Gate& gate) {
    return !bits[gate.a].undefined && !bits[gate.b].undefined;
  };
  std::string GateString(const Gate& g) {
    std::ostringstream sout;
    std::print(sout, "{} ({}) ", bits[g.a].name, (bool)bits[g.a].value[0]);
    sout << g.op;
    std::print(sout, " {} ({}) -> {} ({})", bits[g.b].name,
               (bool)bits[g.b].value[0], bits[g.out].name,
               (bool)bits[g.out].value[0]);
    return sout.str();
  }

  void Read() {
    std::set<std::string> bit_names_done;
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      auto& [name, value] = raw_bits.emplace_back();
      std::getline(sin, name, ':');
      sin >> value;
      bit_names_done.insert(name);
    }
    for (std::string line; std::getline(std::cin, line) && !line.empty();) {
      std::istringstream sin(line);
      auto& [a, op, b, out] = raw_gates.emplace_back();
      std::getline(sin, a, ' ');
      std::getline(sin, op, ' ');
      std::getline(sin, b, ' ');
      sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
      sin >> out;
      auto InsertIfNotDone = [&bit_names_done,
                              &raw_bits = raw_bits](const std::string& name) {
        if (bit_names_done.count(name)) return;
        raw_bits.emplace_back(name, -1), bit_names_done.insert(name);
      };
      InsertIfNotDone(a), InsertIfNotDone(b), InsertIfNotDone(out);
    }
    std::ranges::sort(raw_bits);

    std::cout << "raw_inputs:\n";
    bits.resize(raw_bits.size());
    for (const auto& [i, bit] : std::views::enumerate(raw_bits)) {
      const auto& [name, value] = bit;
      std::cout << std::format("\t{}: {}\n", name, value);
      bits[i] = Bit{.name = name,
                    .value = value > 0 ? BitValue(1) : BitValue(0),
                    .undefined = value == -1};
    }
    std::cout << "raw_gates:\n";
    gates.resize(raw_gates.size());
    for (const auto& [i, raw_gate] : std::views::enumerate(raw_gates)) {
      const auto& [a, op, b, out] = raw_gate;
      const int ai = BitIndex(a), bi = BitIndex(b), outi = BitIndex(out);
      std::cout << std::format("\t{} | {} {} {} -> {}\n", i, a, op, b, out);
      gates[i] = Gate{.a = ai, .op = GetOperation(op), .b = bi, .out = outi};
      bits[ai].input_gate_indexes.push_back(i),
          bits[bi].input_gate_indexes.push_back(i);
    }

    auto IsInput = [](const Bit& bit) {
      return bit.name[0] == 'x' || bit.name[0] == 'y';
    };
    for (auto& bit : bits) {
      if (IsInput(bit))
        input_bits.emplace_back(bit);
      else
        not_input_bits.emplace_back(bit);
      if (bit.name[0] == 'z') output_bits.emplace_back(bit);
    }
    for (auto& gate : gates) {
      if (!IsInput(bits[gate.a]) || !IsInput(bits[gate.b])) continue;
      input_gates.emplace_back(gate);
    }
  }

  void TopologicalEval() {
    std::vector<std::pair<std::reference_wrapper<Gate>, int>> q;
    q.reserve(gates.size());
    for (auto& gate : input_gates) {
      q.emplace_back(gate, 0);
    }
    for (int qi = 0; qi < q.size(); ++qi) {
      const Gate& gate = q[qi].first;
      const int depth = q[qi].second;
      const auto& [a, op, b, out] = gate;
      bits[out].value = Eval(bits[a].value, op, bits[b].value);
      bits[out].undefined = false;
      DEBUG {
        std::println("{}{}", depth == 0 ? "" : std::string(depth, '\t'),
                     GateString(gate));
        std::fflush(stdout);
      }

      for (const int ni : bits[out].input_gate_indexes) {
        DEBUG {
          std::println("\t{}", GateString(gates[ni]));
          std::fflush(stdout);
        }
        if (!IsGateReady(gates[ni]) || !bits[gates[ni].out].undefined) continue;
        q.emplace_back(gates[ni], depth + 1);
      }
    }
  }

  lli ReadNumberFromBits(const char prefix) {
    const auto& bits_to_read =
        prefix == 'x' || prefix == 'y' ? input_bits : output_bits;
    lli res = 0;
    for (const Bit& bit : std::views::reverse(bits_to_read)) {
      if (bit.name[0] != prefix) continue;
      res <<= 1;
      if (!bit.undefined && bit.value[0]) res |= 0b1;
    }
    return res;
  }

  lli RunCircuit(const bool verbose = false) {
    TopologicalEval();
    return ReadNumberFromBits('z');
  }

  // O(max(|input_bits|, |gates|)) = O(|gates|)
  int TestXY(const lli x, const lli y) {
    const lli correct_ans = x + y;
    int xi = 0, yi = 0;
    // O(|input_bits|)
    for (Bit& bit : input_bits) {
      if (bit.name[0] == 'x') {
        bit.value = (x >> xi) & 1, bit.undefined = false;
        ++xi;
      }
      if (bit.name[0] == 'y') {
        bit.value = (y >> yi) & 1, bit.undefined = false;
        ++yi;
      }
    }
    for (Bit& bit : not_input_bits) bit.undefined = true;
    // O(|gates|)
    int res = std::__popcount(correct_ans ^ RunCircuit(/*verbose=*/false));
    return res;
  }
  // O(135 * |gates|)
  int TestCircuit() {
    // O(|gates| * 135)
    int misses = TestXY(21127838400205LL, 28371358894105LL);
    for (int i = 0; i < 45; ++i) {
      lli x = 1LL << i;
      lli y = 1LL << i;
      misses += TestXY(x, y);

      x = 1LL << i;
      y = 0;
      misses += TestXY(x, y);

      x = 0;
      y = 1LL << i;
      misses += TestXY(x, y);
    }
    return misses;
  }

  std::vector<std::pair<lli, lli>> numbers_to_test;
  // O(max(|gates|, |tests|*|output_bits|)) = O(|tests|*|output_bits|)
  int TestCircuit2() {
    if (numbers_to_test.empty()) {
      numbers_to_test.reserve(45 * 3 + 1);
      numbers_to_test.emplace_back(21127838400205LL, 28371358894105LL);
      for (int i = 0; i < 45; ++i) {
        lli x = 1LL << i;
        lli y = 1LL << i;
        numbers_to_test.emplace_back(x, y);

        x = 1LL << i;
        y = 0;
        numbers_to_test.emplace_back(x, y);

        x = 0;
        y = 1LL << i;
        numbers_to_test.emplace_back(x, y);
      }
      for (const auto& [i, xy] : std::views::enumerate(numbers_to_test)) {
        const auto& [x, y] = xy;
        int xi = 0, yi = 0;
        for (Bit& bit : input_bits) {
          if (bit.name[0] == 'x') {
            bit.value[i] = (x >> xi) & 1, bit.undefined = false;
            ++xi;
          }
          if (bit.name[0] == 'y') {
            bit.value[i] = (y >> yi) & 1, bit.undefined = false;
            ++yi;
          }
        }
      }
    }
    // O(|bits|)
    for (Bit& bit : not_input_bits) bit.undefined = true;

    // O(|gates|)
    TopologicalEval();

    // O(|tests|*|output_bits|)
    int misses = 0;
    for (const auto& [i, xy] : std::views::enumerate(numbers_to_test)) {
      const auto& [x, y] = xy;
      const lli correct_ans = x + y;
      lli res = 0;
      for (const Bit& bit : std::views::reverse(output_bits)) {
        res <<= 1;
        if (!bit.undefined && bit.value[i]) res |= 0b1;
        if (bit.undefined) ++misses;
      }
      misses += std::__popcount(correct_ans ^ res);
    }
    return misses;
  }
  void MakeSwap(const int i, const int j) {
    std::swap(gates[i].out, gates[j].out);
  }

  struct State {
    std::vector<std::pair<int, int>> swaps;
    int misses;
    bool operator<(const State& other) const { return misses > other.misses; }
  };
  std::vector<std::pair<int, int>> FindSwaps() {
    std::cout << "find_swaps:\n";
    std::priority_queue<State> pq;
    std::vector<Gate> gates_copy = gates;
    pq.emplace(std::vector<std::pair<int, int>>{}, 0);
    while (!pq.empty()) {
      auto [swaps, misses] = pq.top();
      pq.pop();

      std::println("\tcurr: {} {}", swaps.size(), misses);

      if (swaps.size() == 4) {
        return swaps;
      }

      gates = gates_copy;
      for (const auto& [i, j] : swaps) MakeSwap(i, j);

      for (int i = 0; i < gates.size(); ++i) {
        for (int j = i + 1; j < gates.size(); ++j) {
          MakeSwap(i, j);
          swaps.emplace_back(i, j);
          pq.emplace(swaps, TestCircuit2());
          swaps.pop_back();
          MakeSwap(i, j);
        }
      }
    }
    return {};
  }

  // O(|gates|^2 * |tests|*|output_bits|);
  // Assuming the test is perfect and few swaps yield the same number of misses.
  // Otherwise: O((|gates|^2 * |test|*|output_bits|)^4)
  std::vector<std::pair<int, int>> best_swaps, find_swaps;
  bool FindSwapsRecInternal(std::vector<std::pair<int, int>>& find_swaps,
                            const int misses) {
    std::println("\tcurr: {} {}", find_swaps.size(), misses);
    std::fflush(stdout);
    if (find_swaps.size() == 4) {
      if (misses != 0) return false;
      best_swaps = find_swaps;
      return true;
      // return misses == 0 ? swaps : std::vector<std::pair<int, int>>{};
    }

    std::vector<std::pair<int, std::pair<int, int>>> best;
    best.reserve(gates.size() * ((int)gates.size() - 1) >> 1);
    // O(|gates|^2)
    for (int i = 0; i < gates.size(); ++i) {
      for (int j = i + 1; j < gates.size(); ++j) {
        MakeSwap(i, j);
        find_swaps.emplace_back(i, j);
        // O(|test|*|output_bits|)
        best.emplace_back(TestCircuit2(), std::pair<int, int>{i, j});
        find_swaps.pop_back();
        MakeSwap(i, j);
      }
    }
    std::ranges::sort(best);
    for (const auto& [misses, swap] : best) {
      MakeSwap(swap.first, swap.second);
      find_swaps.push_back(swap);
      if (FindSwapsRecInternal(find_swaps, misses)) return true;
      find_swaps.pop_back();
      MakeSwap(swap.first, swap.second);
    }
    return false;
  }
  std::vector<std::pair<int, int>> FindSwapsRec() {
    find_swaps.clear();
    FindSwapsRecInternal(find_swaps, 0);
    return best_swaps;
  }

  void Solve() {
    Read();
    RunCircuit(/*verbose=*/true);

    const lli x = ReadNumberFromBits('x');
    const lli y = ReadNumberFromBits('y');
    std::cout << std::format("x: {} |  {:b}\n", x, x);
    std::cout << std::format("y: {} |  {:b}\n", y, y);
    const lli correct_ans = x + y;
    std::cout << std::format("t: {} | {:b}\n", correct_ans, correct_ans);
    const lli ans = ReadNumberFromBits('z');
    std::cout << std::format("a: {} | {:b}\n", ans, ans);

    // MakeSwap(0, 2);
    // TestXY(x, y);

    // const auto& swaps = FindSwaps();
    const auto& swaps = FindSwapsRec();
    std::println("raw_ans:");
    std::vector<std::string> res;
    for (const auto& [i, j] : swaps) {
      std::println("\t{}, {} | {} {}", i, j, bits[gates[i].out].name,
                   bits[gates[j].out].name);
      res.push_back(bits[gates[i].out].name);
      res.push_back(bits[gates[j].out].name);
    }
    std::ranges::sort(res);
    std::ostringstream sout;
    for (const auto& o : res) {
      if (!sout.str().empty()) sout << ",";
      sout << o;
    }
    std::println("ans: {}", sout.str());
  }
};
Problem problem;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
