#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 2e5;
int n;
char ss[kMaxN + 1];
list<char> s;

bool IsAbc(list<char>::iterator& it) {
  if (it == s.begin() || prev(it) == s.begin()) {
    return false;
  }
  return *prev(it, 2) == 'A' && *prev(it) == 'B' && *it == 'C';
}

void RemoveAbc(list<char>::iterator& it) {
  it = prev(it, 2);
  it = s.erase(it);
  it = s.erase(it);
  it = s.erase(it);
  if (it != s.begin()) --it;
}

int main() {
  while (~scanf(" %s", ss)) {
    n = strlen(ss);
    s.clear();
    for (int i = 0; i < n; ++i)
      s.push_back(ss[i]);

    for (auto it = next(s.begin(), 2); it != s.end(); ++it) {
      if (IsAbc(it)) {
        RemoveAbc(it);
      }
    }
    string ans;
    for (char c : s) ans += c;
    printf("%s\n", ans.c_str());
  }
  return 0;
}
