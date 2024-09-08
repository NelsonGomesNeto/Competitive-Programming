#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n;
char s[kMaxN + 1];

int main() {
  while (~scanf(" %s", s)) {
    n = strlen(s);
    for (int i = 0; i < n; ++i) {
      printf("%c%c", s[i], i + 1 < n ? ' ' : '\n');
    }
  }
  return 0;
}
