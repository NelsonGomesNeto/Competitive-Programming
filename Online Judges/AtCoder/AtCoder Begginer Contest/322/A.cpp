#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n;
char s[kMaxN + 1];

int main() {
  while (~scanf("%d", &n)) {
    scanf(" %s", s);
    string t = string(s);
    int ans = t.find("ABC");
    if (ans == -1) ans = -2;
    printf("%d\n", ans + 1);
  }
  return 0;
}
