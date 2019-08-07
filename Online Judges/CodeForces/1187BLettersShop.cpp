#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, m, tsize;
char s[maxN + 1], t[maxN + 1];
int accSum[26][maxN + 1], accT[26][maxN + 1];

bool can(int x)
{
  for (int j = 0; j < 26; j ++)
    if (accSum[j][x] < accT[j][tsize])
      return(false);
  return(true);
}

int binarySearch(int lo = 0, int hi = n)
{
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return(lo);
}

int main()
{
  scanf("%d", &n);
  scanf(" %s", s);
  for (int i = 0; i < n; i ++)
  {
    for (int j = 0; j < 26; j ++)
      accSum[j][i + 1] = accSum[j][i];
    accSum[s[i] - 'a'][i + 1] ++;
  }

  scanf("%d", &m);
  while (m --)
  {
    scanf(" %s", t);
    tsize = strlen(t);
    for (int i = 0; t[i]; i ++)
    {
      for (int j = 0; j < 26; j ++)
        accT[j][i + 1] = accT[j][i];
      accT[t[i] - 'a'][i + 1] ++;
    }
    printf("%d\n", binarySearch());
  }
  return(0);
}
