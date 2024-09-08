#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 16;
char s[kMaxN + 1];

int main() {
  while (~scanf(" %s", s)) {
    bool ans = true;
    for (int i = 1; i < kMaxN; i += 2)
      ans &= s[i] == '0';
    printf("%s\n", ans ? "Yes" : "No");
  }

  return 0;
}
