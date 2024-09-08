#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
char s[kMaxN + 1];

int ReadNumber() {
  vector<int> digits;
  for (int i = 0; s[i]; ++i) {
    if (s[i] >= '0' && s[i] <= '9')
      digits.push_back(s[i] - '0');
  }
  assert(!digits.empty());
  return digits[0] * 10 + digits.back();
}

int main() {
  int ans = 0;
  while (~scanf(" %s", s)) {
    ans += ReadNumber();
  }
  printf("%d\n", ans);

  return 0;
}
