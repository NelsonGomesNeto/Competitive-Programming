#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define DEBUG if (0)
using namespace std;

const string kActions = ".+-><";
string magic_phrase;

struct State {
  vector<int> runes = vector<int>(3, 26);
  string curr = "";
  int ri = 0, pos = 0;

  int dist() const {
    if (pos == magic_phrase.size()) return 0;
    if (runes[ri] == 26) return magic_phrase[pos] - 'A' + 1;
    return abs(magic_phrase[pos] - ('A' + runes[ri]));
  }
  bool operator<(const State& other) const {
    // return pos < other.pos ||
    //        (pos == other.pos && curr.size() > other.curr.size()) ||
    //        (pos == other.pos && curr.size() == other.curr.size() &&
    //         dist() > other.dist());
    return pos < other.pos || (pos == other.pos && dist() > other.dist()) ||
           (pos == other.pos && dist() == other.dist() &&
            curr.size() > other.curr.size());
  }

  friend ostream& operator<<(ostream& out, const State& s) {
    string runes_string = "";
    for (const int r : s.runes) {
      if (r == 26) {
        runes_string += '_';
        continue;
      }
      runes_string += 'A' + r;
    }

    out << runes_string << " " << s.ri << " | " << s.pos << " | " << s.curr;
    return out;
  }

  bool Possible(const char a) {
    switch (a) {
      case '.':
        return runes[ri] + 'A' == magic_phrase[pos] ||
               (magic_phrase[pos] == ' ' && runes[ri] == 26);
      case '+':
      case '-':
        return true;
      case '<':
        return ri > 0;
      case '>':
        return ri < 2;
      default:
        return false;
    }
    return false;
  }

  State Act(const char a) {
    State s = *this;
    switch (a) {
      case '.':
        ++s.pos;
        break;
      case '+':
        ++s.runes[ri];
        if (s.runes[ri] == 27) s.runes[ri] = 0;
        break;
      case '-':
        --s.runes[ri];
        if (s.runes[ri] == -1) s.runes[ri] = 26;
        break;
      case '<':
        --s.ri;
        break;
      case '>':
        ++s.ri;
        break;
      default:
        break;
    }
    s.curr += a;
    return s;
  }
};
string Astar() {
  priority_queue<State> pq;
  pq.push(State{});
  while (!pq.empty()) {
    State s = pq.top();
    pq.pop();
    DEBUG cout << s << "\n";

    if (s.pos == magic_phrase.size()) {
      return s.curr;
    }

    for (const char a : kActions) {
      if (!s.Possible(a)) continue;
      pq.push(s.Act(a));
    }
  }
  return "";
}

int main() {
  for (; getline(cin, magic_phrase);) {
    DEBUG cout << "Magic Phrase: " << magic_phrase << "\n";

    string ans = Astar();
    cout << ans << "\n";
  }
  return 0;
}
