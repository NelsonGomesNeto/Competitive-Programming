#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Part {
  std::map<char, int> vars;

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
      p.vars[name] = value;
      DEBUG std::cout << "\tvar: |" << name << op << value << "|\n";
    }

    return stream;
  }

  int Sum() {
    int ans = 0;
    for (auto [var, value] : vars) {
      ans += value;
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
    auto it = p.vars.find(var);
    assert(it != p.vars.end());
    const int curr = it->second;
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
};
Program program;

int main() {
  std::cin >> program;

  int ans = 0;
  for (Part p; std::cin >> p;) {
    if (program.Accepts(p)) {
      ans += p.Sum();
    }
  }
  std::cout << ans << "\n";

  return 0;
}
