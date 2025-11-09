#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Program {
  std::vector<std::pair<int, int>> instructions;
  Program() {}
  Program(const std::vector<std::pair<int, int>>& instructions)
      : instructions(instructions) {}
  friend std::ostream& operator<<(std::ostream& out, const Program& p) {
    for (const auto& [a, b] : p.instructions) std::cout << a << "," << b << "|";
    return out;
  }
};
struct Computer {
  // std::vector<lli> registers;
  // lli* A() { return &registers[0]; }
  // lli* B() { return &registers[1]; }
  // lli* C() { return &registers[2]; }
  lli A, B, C;
  Program program;
  int pc;

  lli EvaluateComboOperand(const int literal) {
    switch (literal) {
      case 4:
        return A;
      case 5:
        return B;
      case 6:
        return C;
      case 7:
        assert(false);
        return -1;
      default:
        return literal;
    }
  }

  void Write(const lli value, std::ostringstream& sout) {
    if (!sout.str().empty()) sout << ",";
    sout << value;
  }

  Computer() {}
  Computer(const std::vector<lli>& registers, const Program& program)
      : A(registers[0]), B(registers[1]), C(registers[2]), program(program) {}
  friend std::ostream& operator<<(std::ostream& out, const Computer& c) {
    // for (int i = 0; i < c.registers.size(); ++i)
    //   out << "Register " << (char)('A' + i) << ": " << c.registers[i] <<
    //   "\n";
    out << "Register A: " << c.A << "\n";
    out << "Register B: " << c.B << "\n";
    out << "Register C: " << c.C << "\n";
    out << "Program: " << c.program << "\n";
    return out;
  }

  std::string ExecuteProgram() {
    pc = 0;
    std::ostringstream sout;

    while (pc < program.instructions.size()) {
      const auto [op, literal] = program.instructions[pc];
      const lli combo = EvaluateComboOperand(literal);
      // kInstructionTable[op](literal, combo, sout);
      switch (op) {
        case 0:
          A = A / (1 << combo), ++pc;
          break;
        case 1:
          B = B ^ literal, ++pc;
          break;
        case 2:
          B = combo % 8, ++pc;
          break;
        case 3:
          if (A == 0)
            ++pc;
          else
            pc = literal;
          break;
        case 4:
          B = B ^ C, ++pc;
          break;
        case 5:
          Write(combo % 8, sout), ++pc;
          break;
        case 6:
          B = A / (1 << combo), ++pc;
          break;
        case 7:
        default:
          C = A / (1 << combo), ++pc;
          break;
      }
      std::cout << "pc: " << pc << " | " << op << " " << literal << " " << combo
                << " | " << sout.str() << "\n";
    }

    return sout.str();
  }
};

struct Problem {
  Computer computer;
  void ReadComputer() {
    std::vector<lli> registers;
    auto ReadRegister = [&]() {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
      std::cin >> registers.emplace_back();
    };
    for (int i = 0; i < 3; ++i) ReadRegister();

    std::vector<std::pair<int, int>> instructions;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    auto ReadInstruction = [&]() {
      std::pair<int, int> instruction;
      if (!(std::cin >> instruction.first)) return false;

      std::cin.ignore(1);
      std::cin >> instruction.second;
      std::cin.ignore(1);

      instructions.push_back(instruction);
      return true;
    };
    while (ReadInstruction());

    computer = Computer(registers, Program(instructions));
  }

  void Solve() {
    ReadComputer();
    std::cout << computer << "\n";

    const std::string output = computer.ExecuteProgram();
    std::cout << computer << "\n";
    std::cout << "output: " << output << "\n";
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
