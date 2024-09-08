#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n, m;
string s, t;
char ss[kMaxN];
string ReadString() {
  scanf(" %s", ss);
  return string(ss);
}

int main() {
  while (~scanf("%d %d", &n, &m)) {
    s = ReadString();
    t = ReadString();

    int lo = t.find(s);
    reverse(t.begin(), t.end());
    reverse(s.begin(), s.end());
    int hi = t.find(s);
    bool prefix = lo == 0;
    bool suffix = hi == 0;
    DEBUG printf("\t%d %d\n", lo, hi);

    int ans;
    if (prefix && suffix) ans = 0;
    else if (prefix) ans = 1;
    else if (suffix) ans = 2;
    else ans = 3;
    printf("%d\n", ans);
  }
  return 0;
}
