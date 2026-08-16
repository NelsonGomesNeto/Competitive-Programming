#include <bits/stdc++.h>
#define DEBUG if (1)

struct Wire {
  std::string name;
  int id;
  uint16_t value;
};
template <>
struct std::formatter<Wire> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Wire& w, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{} = {}", w.name, w.value);
  }
};

enum Op { kSet = 0, kAnd = 1, kOr = 2, kLShift = 3, kRShift = 4, kNot = 5 };
struct Instruction {
  std::string raw_instruction;
  Op op;
  std::string raw_op;
  std::string raw_a, raw_b, raw_out;
  std::shared_ptr<Wire> a = nullptr;
  std::shared_ptr<Wire> b = nullptr;
  std::shared_ptr<Wire> out = nullptr;
  void ParseRawInstruction() {
    if (raw_instruction.empty()) return;
    if (raw_instruction == "14146 -> b") {
      raw_instruction = "956 -> b";
    }
    std::istringstream sin(raw_instruction);
    std::string left;
    std::getline(sin, left, '>');
    left.erase((int)left.size() - 2);
    sin >> raw_out;
    std::istringstream lin(left);
    if (left.contains(' ')) {
      if (left[0] == 'N') {
        op = Op::kNot;
        raw_op = "NOT";
        lin.ignore(raw_op.size() + 1);
        lin >> raw_a;
      } else {
        lin >> raw_a;
        lin >> raw_op;
        if (raw_op.back() == 'T') {
          op = raw_op[0] == 'L' ? Op::kLShift : Op::kRShift;
          lin >> raw_b;
        } else {
          op = raw_op[0] == 'A' ? Op::kAnd : Op::kOr;
          lin >> raw_b;
        }
      }
    } else {
      op = Op::kSet;
      raw_op = "SET";
      lin >> raw_a;
    }
  }
  void Eval() { out->value = EvaluateOp(); }
  friend std::istream& operator>>(std::istream& sin, Instruction& i) {
    std::getline(sin, i.raw_instruction);
    i.ParseRawInstruction();
    return sin;
  }

 private:
  uint16_t EvaluateOp() {
    switch (op) {
      case kSet:
        return a->value;
      case kNot:
        return ~a->value;
      case kAnd:
        return a->value & b->value;
      case kOr:
        return a->value | b->value;
      case kLShift:
        return (uint16_t)(a->value << b->value);
      case kRShift:
        return (uint16_t)(a->value >> b->value);
      default:
        assert(false);
    }
  }
};
template <>
struct std::formatter<Instruction> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Instruction& i, FormatContext& ctx) const {
    switch (i.op) {
      case kSet:
        return std::format_to(ctx.out(), "{} -> {}", i.raw_a, i.raw_out);
      case kAnd:
      case kOr:
      case kLShift:
      case kRShift:
        return std::format_to(ctx.out(), "{} {} {} -> {}", i.raw_a, i.raw_op,
                              i.raw_b, i.raw_out);
      case kNot:
        return std::format_to(ctx.out(), "{} {} -> {}", i.raw_op, i.raw_a,
                              i.raw_out);
      default:
        assert(false);
    }
  }
};
// It's not actually a program. It's more of a circuit but oh well I realized a
// bit too late to change hahahaha.
struct Program {
  std::vector<Instruction> instructions;
  std::map<std::string, int> wire_map;
  std::vector<std::shared_ptr<Wire>> wires;

  void AddWire(const std::string& raw_wire, std::shared_ptr<Wire>& wire) {
    const auto [it, inserted] = wire_map.try_emplace(raw_wire, wire_map.size());
    const int id = it->second;
    if (inserted) {
      wire = std::make_shared<Wire>();
      wires.emplace_back(wire);
      *wire = Wire{.name = raw_wire, .id = id, .value = 0};
    } else {
      wire = wires[it->second];
    }
  }
  void Compile() {
    // Load all "wires" from the circuit.
    for (auto& i : instructions) {
      switch (i.op) {
        case kSet:
        case kNot:
          AddWire(i.raw_a, i.a);
          break;
        case kLShift:
        case kRShift:
        case kAnd:
        case kOr:
          AddWire(i.raw_a, i.a);
          AddWire(i.raw_b, i.b);
          break;
        default:
          assert(false);
      }
      AddWire(i.raw_out, i.out);
    }
    std::ranges::sort(wires, [](const std::shared_ptr<Wire>& a,
                                const std::shared_ptr<Wire>& b) {
      return a->name < b->name;
    });
    for (auto [i, wire] : wires | std::views::enumerate) {
      wire->id = (int)i;
      wire_map[wire->name] = (int)i;
    }

    // Topologically sort the instructions so sequential execution emulates the
    // circuit.
    DEBUG std::println("topological_sort:");
    std::vector<int> pendings_by_instruction(instructions.size(), 0);
    std::vector<std::vector<int>> instructions_by_output(wires.size(),
                                                         std::vector<int>{});
    std::vector<std::vector<int>> instructions_by_input(wires.size(),
                                                        std::vector<int>{});
    for (const auto& [i, instruction] : instructions | std::views::enumerate) {
      const int out_id = instruction.out->id;
      instructions_by_output[out_id].push_back((int)i);
      pendings_by_instruction[i] += [&]() {
        switch (instruction.op) {
          case kSet:
          case kNot:
            return 1;
          case kLShift:
          case kRShift:
          case kAnd:
          case kOr:
            return 2;
          default:
            assert(false);
        }
      }();
      switch (instruction.op) {
        case kSet:
        case kNot:
          instructions_by_input[instruction.a->id].push_back((int)i);
          break;
        case kLShift:
        case kRShift:
        case kAnd:
        case kOr:
          instructions_by_input[instruction.a->id].push_back((int)i);
          instructions_by_input[instruction.b->id].push_back((int)i);
          break;
        default:
          assert(false);
      }
    }
    std::queue<std::pair<int, int>> q;
    DEBUG {
      std::println("\tinstructions dependencies:");
      for (const auto& [i, instruction] :
           instructions | std::views::enumerate) {
        std::println("\t\t{} || dep_count: {}", instruction,
                     pendings_by_instruction[i]);
      }
    }
    DEBUG std::println("\twires dependencies:");
    for (const auto& wire : wires) {
      DEBUG std::println("\t\t{} || dep_count: {}", *wire,
                         instructions_by_output[wire->id].size());
      if (!instructions_by_output[wire->id].empty()) continue;
      for (const int i : instructions_by_input[wire->id]) {
        if (--pendings_by_instruction[i] > 0) continue;
        q.emplace(i, 0);
      }
    }
    std::vector<Instruction> topological_order;
    DEBUG std::println("\ttopological order:");
    while (!q.empty()) {
      const auto [curr_i, depth] = q.front();
      q.pop();
      const Instruction& curr = instructions[curr_i];
      DEBUG std::println("\t\t{}", curr);
      topological_order.push_back(curr);
      for (const int next_i : instructions_by_input[curr.out->id]) {
        if (--pendings_by_instruction[next_i] > 0) continue;
        q.emplace(next_i, depth + 1);
      }
    }
    assert(topological_order.size() == instructions.size());
    instructions = topological_order;

    // Print a graphviz of the circuit \o/
    std::ofstream ofs("graph.dot", std::ios_base::out);
    std::println(ofs, "digraph {{");
    std::println(ofs, "bgcolor=\"#000000\"");
    std::println(ofs,
                 "node [fontcolor=\"#ffffff\", color=\"#ffffff\", "
                 "fillcolor=\"#333333\", style=filled]");
    std::println(ofs, "edge [color=\"#ffffff\", fontcolor=\"#ffffff\"]");
    auto AddEdge = [&](const std::string& u, const std::string& v,
                       const bool force = false) {
      if (!force && std::isdigit(u[0])) return;
      std::println(ofs, "\"{}\" -> \"{}\"", u, v);
    };
    for (const auto& instruction : instructions) {
      switch (instruction.op) {
        case kSet:
          AddEdge(instruction.a->name, instruction.out->name, /*force=*/true);
          break;
        case kNot: {
          const std::string left = std::format("NOT {}", instruction.a->name);
          AddEdge(instruction.a->name, left);
          AddEdge(left, instruction.out->name, /*force=*/true);
          break;
        }
        case kLShift:
        case kRShift:
        case kAnd:
        case kOr: {
          const std::string left =
              std::format("{} {} {}", instruction.a->name, instruction.raw_op,
                          instruction.b->name);
          AddEdge(instruction.a->name, left);
          AddEdge(instruction.b->name, left);
          AddEdge(left, instruction.out->name, /*force=*/true);
          break;
        }
        default:
          assert(false);
      }
    }
    std::println(ofs, "}}");
  }

  void Execute() {
    // Reset wires.
    for (auto& wire : wires) {
      if (std::isdigit(wire->name[0]))
        wire->value = (uint16_t)std::stoi(wire->name);
      else
        wire->value = 0;
    }

    // Run circuit
    std::ofstream ofs("graph2.dot", std::ios_base::out);
    std::println(ofs, "digraph {{");
    std::println(ofs, "bgcolor=\"#000000\"");
    std::println(ofs,
                 "node [fontcolor=\"#ffffff\", color=\"#ffffff\", "
                 "fillcolor=\"#333333\", style=filled]");
    std::println(ofs, "edge [color=\"#ffffff\", fontcolor=\"#ffffff\"]");
    for (auto& i : instructions) {
      i.Eval();
      auto AddEdge = [&](const std::string& u, const std::string& v,
                         const bool force = false) {
        if (!force && std::isdigit(u[0])) return;
        std::println(ofs, "\"{}\" -> \"{}\"", u, v);
      };
      auto Hehe = [&](const std::string& u) {
        return std::format("{} = {}", u, wires[wire_map[u]]->value);
      };
      switch (i.op) {
        case kSet:
          AddEdge(Hehe(i.a->name), Hehe(i.out->name), /*force=*/true);
          break;
        case kNot: {
          const std::string left = std::format("NOT {}", Hehe(i.a->name));
          AddEdge(Hehe(i.a->name), left);
          AddEdge(left, Hehe(i.out->name), /*force=*/true);
          break;
        }
        case kLShift:
        case kRShift:
        case kAnd:
        case kOr: {
          const std::string left = std::format("{} {} {}", Hehe(i.a->name),
                                               i.raw_op, Hehe(i.b->name));
          AddEdge(Hehe(i.a->name), left);
          AddEdge(Hehe(i.b->name), left);
          AddEdge(left, Hehe(i.out->name), /*force=*/true);
          break;
        }
        default:
          assert(false);
      }
    }
    std::println(ofs, "}}");

    // Print all outputs
    std::println("output:");
    for (const auto& wire : wires) {
      std::println("\t{}", *wire);
    }
  }

  std::optional<uint16_t> GetValue(const std::string& wire_name) {
    auto it = wire_map.find(wire_name);
    if (it == wire_map.end()) return std::nullopt;
    return wires[it->second]->value;
  }

  friend std::istream& operator>>(std::istream& sin, Program& p) {
    while (true) {
      Instruction instruction;
      if (!(sin >> instruction)) break;
      p.instructions.push_back(instruction);
    }
    p.Compile();
    return sin;
  }
};
template <>
struct std::formatter<Program> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Program& p, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        p.instructions | std::views::transform([](const Instruction& i) {
          return std::format("\t{}", i);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  Program program;
  std::cin >> program;

  std::println("program:\n{}", program);

  program.Execute();

  const std::optional<uint16_t> ans = program.GetValue("a");
  if (!ans.has_value())
    std::println("ans: `a` wire doesn't exist");
  else
    std::println("ans: {}", *ans);

  return 0;
}
