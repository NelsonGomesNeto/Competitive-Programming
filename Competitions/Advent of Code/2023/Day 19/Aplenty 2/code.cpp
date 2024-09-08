#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

lli Sum(const std::vector<std::pair<int, int>>& ranges) {
  lli ans = 1;
  for (const auto [lo, hi] : ranges) {
    assert(lo <= hi);
    assert(lo >= 1);
    assert(hi <= 4000);
    ans *= hi - lo + 1;
  }
  return ans;
}

const std::vector<char> variables = {'x', 'm', 'a', 's'};
int pos_by_var[256];

struct Part {
  std::vector<int> values = std::vector<int>(4, 1);

  friend std::istream& operator>>(std::istream& stream, Part& p) {
    stream.ignore(1);
    std::string line;
    std::getline(stream, line);
    std::istringstream sin(line);

    for (std::string var; std::getline(sin, var, ',');) {
      if (var.back() == '}') {
        var.pop_back();
      }
      std::istringstream sin(var);
      char name, op;
      int value;
      sin >> name >> op >> value;
      p.values[pos_by_var[name]] = value;
      DEBUG std::cout << "\tvar: |" << name << op << value << "|\n";
    }

    return stream;
  }

  int Sum() {
    int ans = 0;
    for (const int v : values) {
      ans += v;
    }
    return ans;
  }
};

struct Rule {
  char var;
  char op;
  int value;
  std::string dest;

  Rule() {}
  Rule(const std::string& rule) {
    std::istringstream sin(rule);
    sin >> var >> op >> value;
    sin.ignore(1) >> dest;
  }

  bool Matches(const Part& p) const {
    const int curr = p.values[pos_by_var[var]];
    return op == '>' ? curr > value : curr < value;
  }
};
struct Workflow {
  std::vector<Rule> rules;
  std::string default_dest;

  Workflow() {}
  Workflow(const std::string& workflow) {
    std::istringstream sin(workflow);
    for (std::string rule; std::getline(sin, rule, ',');) {
      if (sin.eof()) {
        DEBUG std::cout << "\t\tFinished: " << rule << "\n";
        default_dest = rule;
        break;
      } else {
        rules.emplace_back(rule);
        DEBUG std::cout << "\t" << rule << "\n";
      }
    }
  }

  std::string Compute(const Part& p) const {
    for (const Rule& r : rules) {
      if (r.Matches(p)) {
        return r.dest;
      }
    }
    return default_dest;
  }
};
struct Program {
  std::map<std::string, Workflow> workflow_by_name;

  friend std::istream& operator>>(std::istream& stream, Program& p) {
    for (std::string line; std::getline(stream, line);) {
      if (line.empty()) break;
      int pos = line.find('{');
      std::string name = line.substr(0, pos),
                  workflow = line.substr(pos + 1, line.size() - pos - 2);
      p.workflow_by_name[name] = Workflow(workflow);
      DEBUG std::cout << name << " " << workflow << "\n";
    }

    return stream;
  }

  bool Accepts(const Part& p) const {
    std::string curr = "in";
    while (curr != "A" && curr != "R") {
      auto it = workflow_by_name.find(curr);
      assert(it != workflow_by_name.end());
      const Workflow& w = it->second;
      curr = w.Compute(p);
    }

    return curr == "A";
  }

  lli Solve(
      std::string curr = "in", int i = 0,
      std::vector<std::pair<int, int>> ranges =
          std::vector<std::pair<int, int>>(4, std::make_pair(1, 4000))) const {
    if (curr == "A") return Sum(ranges);
    if (curr == "R") return 0;

    lli ans = 0;

    auto it = workflow_by_name.find(curr);
    assert(it != workflow_by_name.end());
    const Workflow& w = it->second;

    if (i == w.rules.size()) {
      ans += Solve(w.default_dest, 0, ranges);
    } else {
      const Rule& r = w.rules[i];
      const int j = pos_by_var[r.var];
      auto& [lo, hi] = ranges[j];

      if (r.op == '>') {
        int prv = lo;
        if (r.value < 4000 && lo <= r.value) {
          lo = std::max(lo, r.value + 1);
          ans += Solve(r.dest, 0, ranges);
        }

        lo = prv;
        hi = std::min(hi, r.value);
      } else {
        int prv = hi;
        if (r.value > 1 && hi >= r.value) {
          hi = std::min(hi, r.value - 1);
          ans += Solve(r.dest, 0, ranges);
        }

        hi = prv;
        lo = std::max(lo, r.value);
      }
      ans += Solve(curr, i + 1, ranges);
    }

    return ans;
  }
};
Program program;

int main() {
  for (int i = 0; i < variables.size(); ++i) {
    pos_by_var[variables[i]] = i;
  }

  std::cin >> program;

  lli ans = program.Solve();
  std::cout << ans << "\n";

  return 0;
}
