#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, k;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    scanf(" %s", s);

    pair<int, int> canPos[2];
    for (int i = 0; i < 2; i++) canPos[i] = {n + 1, -1};

    for (int i = 0; i < n; i++)
    {
      int minIdx = 0, maxIdx = min(k - 1, i);
      if (i + k - 1 >= n)
        minIdx = (i + k - 1) - n + 1;
      printf("\t\t%d %c - %d %d\n", i, s[i], minIdx, maxIdx);

      if (s[i] == '0')
        canPos[0] = {min(canPos[0].first, minIdx), max(canPos[0].second, maxIdx)};
      else
        canPos[1] = {min(canPos[1].first, minIdx), max(canPos[1].second, maxIdx)};
    }

    printf("\t%d %d | %d %d\n", canPos[0].first, canPos[0].second, canPos[1].first, canPos[1].second);
  }
  return 0;
}
