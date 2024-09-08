#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n; char initial;
char ss[maxN + 1];
string s;
int acc[maxN];

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d %c", &n, &initial);
    scanf(" %s", ss);
    s = string(ss);
    s += s;
    int wait = 0;
    for (int i = s.size() - 1; i >= 0; --i)
    {
      if (s[i] == 'g')
        wait = 0;
      if (i < n)
        acc[i] = wait;
      ++wait;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
      if (s[i] == initial)
        ans = max(ans, acc[i]);
    printf("%d\n", ans);
  }

  return 0;
}
