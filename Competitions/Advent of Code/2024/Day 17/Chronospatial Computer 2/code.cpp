#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

/*
This day as scary as well hahaha.

I built an "interpreter" for part one and IIRC I tried using it for brute force
the answer. But it was way too slow and I barely found a combination that
yielded the first two digits of the "program".

After A LOT of exploration, I perfected the interpreter and tried to read the
program. Turns out it is a simple 3 liner:
  C = ((A & 0b111) ^ 0b10)
  B = C ^ (A >> C) ^ 0b11
  output(B & 0b111)
I suspect there is a way to compress this even more and even make some tables
into how to output values.

But, without digging further, I found that it processes at most a byte (8
bits) at a time to output 2 (or more) values.
So, I do a "Dijkstra" to find the combination of bytes that matches:
  while !q.empty():
    curr = q[0]
    for b in all bytes:
      nxt = concat(b, curr)
      if not Good(nxt): continue
      q.push(nxt)
With some pruning, this runs in ~64ms! \o/

First solution:
I coded that search in Python (scripting really is best in python hahaha). With
pruning, it runs on ~1s on `pypy3`. But I was desperate and forgot to prune, so
I just got the best solution up to 20s and luckily it was the best hahahaha.
*/

struct Program {
  std::vector<std::pair<int, int>> instructions;
  std::string raw_instructions;
  std::vector<int> raw_instructions_ints;
  Program() {}
  Program(const std::vector<std::pair<int, int>>& instructions)
      : instructions(instructions) {
    raw_instructions_ints.clear();
    std::ostringstream sout;
    for (const auto [a, b] : instructions) {
      if (!sout.str().empty()) sout << ",";
      sout << a << "," << b;
      raw_instructions_ints.push_back(a);
      raw_instructions_ints.push_back(b);
    }
    raw_instructions = sout.str();
  }
  friend std::ostream& operator<<(std::ostream& out, const Program& p) {
    for (const auto& [a, b] : p.instructions) out << a << "," << b << "|";
    out << "\n";
    for (const auto& [a, literal] : p.instructions) {
      char combo;
      if (literal >= 4)
        combo = 'A' + (literal - 4);
      else
        combo = '0' + literal;

      const std::string parsed_instruction = [&]() -> std::string {
        switch (a) {
          case 0:
            return std::format("A /= 1LL << {};", combo);
          case 1:
            return std::format("B ^= {};", literal);
          case 2:
            return std::format("B = {} & 0b111;", combo);
          case 3:
            return std::format("if (A) pc = {};", literal);
          case 4:
            return std::format("B ^= C;");
          case 5:
            return std::format("out << ({} & 0b111);", combo);
          case 6:
            return std::format("B = A / (1LL << {});", combo);
          case 7:
          default:
            return std::format("C = A / (1LL << {});", combo);
        }
      }();
      out << "\t" << parsed_instruction << "\n";
    }
    return out;
  }
};
struct Computer {
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

  Computer() {}
  Computer(const std::vector<lli>& registers, const Program& program)
      : A(registers[0]), B(registers[1]), C(registers[2]), program(program) {}
  friend std::ostream& operator<<(std::ostream& out, const Computer& c) {
    out << "Register A: " << c.A << "\n";
    out << "Register B: " << c.B << "\n";
    out << "Register C: " << c.C << "\n";
    out << "Program: " << c.program << "\n";
    out << "RawInstructions: " << c.program.raw_instructions << "\n";
    return out;
  }

  std::string ExecuteProgram() {
    pc = 0;
    std::ostringstream sout;

    while (pc < program.instructions.size()) {
      const auto [op, literal] = program.instructions[pc];
      const lli combo = EvaluateComboOperand(literal);
      switch (op) {
        case 0:
          A = A / (1LL << combo), ++pc;
          break;
        case 1:
          B = B ^ literal, ++pc;
          break;
        case 2:
          B = combo & 0b111, ++pc;
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
          if (!sout.str().empty()) sout << ",";
          sout << (combo & 0b111), ++pc;
          break;
        case 6:
          B = A / (1 << combo), ++pc;
          break;
        case 7:
        default:
          C = A / (1 << combo), ++pc;
          break;
      }
      DEBUG std::cout << "pc: " << pc << " | " << op << " " << literal << " "
                      << combo << " | " << sout.str() << "\n";
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

  std::string ExecuteCompiledProgram(lli A) {
    std::ostringstream out;
    lli B = 0, C = 0;
    do {
      DEBUG2 std::cout << "\t" << A << " " << B << " " << C << "\n";
      DEBUG2 std::cout << "\t" << std::format("{:b} {:b} {:b}", A, B, C)
                       << "\n";

      // B = (A & 0b111);
      // B ^= 0b10;

      // B = (A & 0b111) ^ 0b10;
      // B = A & 0b101;
      // B ^= 0b10;
      // C = A / (1LL << B);

      // B ^= 3;
      // B ^= C;
      // ((A^ 0b10 & 0b101))
      /*
              A | C
        0 0b000 | 2 0b010
        1 0b001 | 3 0b011
        2 0b010 | 0 0b000
        3 0b011 | 1 0b001
        4 0b100 | 6 0b110
        5 0b101 | 7 0b111
        6 0b110 | 4 0b100
        7 0b111 | 5 0b101
      */
      C = ((A & 0b111) ^ 0b10);
      B = C ^ (A >> C) ^ 0b11;

      if (!out.str().empty()) out << ",";
      const int output = (B & 0b111);
      out << output;

      // A /= 1LL << 3;
      A >>= 3;

      DEBUG2 std::cout << "\t\t" << A << " " << B << " " << C << "\n";
      DEBUG2 std::cout << "\t\t" << std::format("{:b} {:b} {:b}", A, B, C)
                       << "\n";
    } while (A);
    return out.str();
  }

  // Highly specialized search leveraging that we know the program reads up
  // to 9 bits for each output pair.
  // I wonder how generic we can make these searches.
  /*
    C = ((A & 0b111) ^ 0b10)
    B = C ^ (A >> C) ^ 0b11
    B = B & 0b111
  */
  const int kBitsPerWrite = 9;
  const int kMaxMaskPerWrite = 1 << kBitsPerWrite;
  struct State {
    lli curr;
    int i;
    // Maximize position then minimize `A` value.
    bool operator<(const State& other) const {
      return i < other.i || (i == other.i && curr > other.curr);
    }
  };
  int MsbIndex(lli x) {
    int ans = 0;
    while (x >>= 1) ++ans;
    return ans;
  }
  // Returns x |+| y (binary concatenation)
  lli BinaryConcat(const lli x, const lli y) {
    return x | (y << (MsbIndex(x) + 1));
  }
  bool OutputMatches(lli A, const int target_size) {
    int i = 0;
    lli B = 0, C = 0;
    do {
      C = ((A & 0b111) ^ 0b10);
      B = C ^ (A >> C) ^ 0b11;
      if (computer.program.raw_instructions_ints[i++] != (B & 0b111))
        return false;
      A >>= 3;
    } while (A && i < target_size);
    return i >= target_size;
  }
  lli FindA() {
    std::unordered_set<lli> visited;
    lli best = std::numeric_limits<lli>::max();
    std::priority_queue<State> pq;
    pq.emplace(0, 0);
    while (!pq.empty()) {
      const State s = pq.top();
      pq.pop();
      const auto [curr, i] = s;

      if (i == computer.program.raw_instructions_ints.size()) {
        best = std::min(best, curr);
        continue;
      }

      const auto [_, inserted] = visited.emplace(curr);
      if (!inserted) continue;

      for (int mask = 0; mask < kMaxMaskPerWrite; ++mask) {
        const lli nxt = i == 0 ? mask : BinaryConcat(curr, mask);
        if (!OutputMatches(nxt, i + 2)) continue;
        pq.emplace(nxt, i + 2);
      }
    }
    return best;
  }

  void Solve() {
    ReadComputer();
    std::cout << computer << "\n";

    const lli a = FindA();
    computer.A = a;
    const std::string output = computer.ExecuteProgram();
    const std::string output2 = ExecuteCompiledProgram(a);
    assert(output == output2);
    std::cout << std::format("A={} | {:b} | {}\n", a, a, output2);

    const lli ans = a;
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
