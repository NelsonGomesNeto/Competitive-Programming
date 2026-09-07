#include <bits/stdc++.h>

enum Op { kHlf = 0, kTpl = 1, kInc = 2, kJmp = 3, kJie = 4, kJio = 5 };
const std::array<std::string, 6> kNameByOp = {"hlf", "tpl", "inc",
                                              "jmp", "jie", "jio"};
const std::map<std::string, Op> kOpByName = []() {
  std::map<std::string, Op> op_from_name;
  for (const auto [i, name] : kNameByOp | std::views::enumerate) {
    op_from_name[name] = Op(i);
  }
  return op_from_name;
}();
struct Instruction {
  const Op op;
  int* reg;
  int offset;
  Instruction(int& a, int& b, std::istringstream&& sin)
      : op([&]() {
          std::string s;
          sin >> s;
          return kOpByName.at(s);
        }()),
        reg([&]() -> int* {
          if (op == Op::kJmp) return nullptr;
          std::string s;
          sin >> s;
          if (s.back() == ',') s.pop_back();
          return s == "a" ? &a : &b;
        }()),
        offset([&]() {
          if (op == Op::kHlf || op == Op::kTpl || op == Op::kInc) return 0;
          sin.ignore(1);  // skip space
          char signal;
          int o;
          sin >> signal >> o;
          return signal == '+' ? o : -o;
        }()) {}
  Instruction(int& a, int& b, const std::string& str)
      : Instruction(a, b, std::istringstream(str)) {}
};
template <>
struct std::formatter<Instruction> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Instruction& i, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{} {} {}", kNameByOp[(int)i.op],
                          static_cast<const void*>(i.reg), i.offset);
  }
};

struct Program {
  const std::vector<Instruction> instructions;
  int a, b;
  Program(std::istringstream&& sin)
      : instructions([&]() {
          std::vector<Instruction> is;
          for (std::string line; std::getline(sin, line);) {
            is.emplace_back(a, b, line);
          }
          return is;
        }()) {}
  Program(const std::string& str) : Program(std::istringstream(str)) {}

  void Reset() { a = b = 0; }
  void Execute() {
    Reset();
    const auto JumpValue = [](const int offset) { return offset - 1; };
    for (int p = 0; p < (int)instructions.size(); ++p) {
      const Instruction& instruction = instructions[p];
      switch (instruction.op) {
        case Op::kHlf:
          *instruction.reg >>= 1;
          break;
        case Op::kTpl:
          *instruction.reg *= 3;
          break;
        case Op::kInc:
          *instruction.reg += 1;
          break;
        case Op::kJmp:
          p += JumpValue(instruction.offset);
          break;
        case Op::kJie:
          if (~(*instruction.reg) & 1) p += JumpValue(instruction.offset);
          break;
        case Op::kJio:
          if ((*instruction.reg) == 1) p += JumpValue(instruction.offset);
          break;
        default:
          assert(false);
      }
    }
  }
};
template <>
struct std::formatter<Program> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Program& p, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "a: {:p}\nb: {}\ninstructions:\n{}",
        static_cast<const void*>(&p.a), static_cast<const void*>(&p.b),
        p.instructions | std::views::transform([](const Instruction& i) {
          return std::format("\t{}", i);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  const std::string input(std::istreambuf_iterator<char>(std::cin), {});
  Program program(input);

  std::println("program:\n{}", program);

  program.Execute();
  std::println("a: {}", program.a);
  std::println("b: {}", program.b);

  const int ans = program.b;
  std::println("ans: {}", ans);

  return 0;
}
