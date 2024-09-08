#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 10000;
char ss[kMaxN + 1];
string s;
int color_map[256];

void SplitAndProcess(const string& input, const char separator, function<void(const string&)> process) {
  int prv = 0;
  for (int p = input.find(separator); p != input.npos; p = input.find(separator, prv)) {
    process(input.substr(prv, p - prv));
    prv = p + 2;
  }
  process(input.substr(prv));
}

struct Subset {
  int rgb[3] = {0, 0, 0};

  void ReadColor(const string& color) {
    int cnt;
    char color_name;
    sscanf(color.c_str(), "%d %c", &cnt, &color_name);
    rgb[color_map[color_name]] = cnt;
  }

  static Subset Read(const string& input) {
    Subset subset;
    SplitAndProcess(input, ',', [&subset](const string& piece) {
      subset.ReadColor(piece);
    });
    return subset;
  }

  bool Possible(const Subset& other) const {
    for (int i = 0; i < 3; ++i) {
      if (rgb[i] > other.rgb[i]) {
        return false;
      }
    }
    return true;
  }
};
Subset required{12, 13, 14};

vector<Subset> ReadAll(const string& input) {
  vector<Subset> subsets;
  SplitAndProcess(input, ';', [&subsets](const string& piece) {
    subsets.push_back(Subset::Read(piece));
  });
  return subsets;
}

int Solve() {
  int id;
  sscanf(s.c_str(), "Game %d", &id);
  s = s.substr(8 + (int)log10(id));

  vector<Subset> subsets = ReadAll(s);
  for (const Subset& subset : subsets) {
    if (!subset.Possible(required)) {
      return 0;
    }
  }

  return id;
}

int main() {
  color_map['r'] = 0, color_map['g'] = 1, color_map['b'] = 2;

  int ans = 0;
  while (~scanf(" %[^\n]", ss)) {
    s = string(ss);
    ans += Solve();
  }
  printf("%d\n", ans);

  return 0;
}
