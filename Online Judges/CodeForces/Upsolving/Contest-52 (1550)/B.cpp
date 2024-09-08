#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, a, b;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &a, &b);
    scanf(" %s", s);

    int ans = 0;
    int zeros = 0, ones = 0;
    int sepZeros = 0, sepOnes = 0;
    int groups = 0, zeroGroups = 0, oneGroups = 0;
    bool hasOne = false, hasZero = false;
    for (int i = 0; i < n; i++)
    {
      hasOne |= s[i] == '1';
      hasZero |= s[i] == '0';

      int j = i;
      while (j + 1 < n && s[i] == s[j + 1])
        j++;

      int sz = j - i + 1;
      int value = sz * a + max(b, sz * b);
      if (s[i] == '0') zeros += sz, sepZeros += value;
      else ones += sz, sepOnes += value;

      i = j;
      groups++;
      if (i != 0 && j != n - 1)
        zeroGroups += s[i] == '0', oneGroups += s[i] == '1';
    }
    ans = max(
      zeros * a + max(b, zeros * b) + sepOnes,
      ones * a + max(b, ones * b) + sepZeros
    );
    ans = n * a + max({
      n * b,
      (groups - 1) * b,
      max(1, zeroGroups) * b + (hasOne) * b,
      max(1, oneGroups) * b + (hasZero) * b
    });
    printf("%d\n", ans);
  }
  return 0;
}
