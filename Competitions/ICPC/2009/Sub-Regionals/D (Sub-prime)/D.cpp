#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4, maxX = 1e5; int n, m;
int a[maxN], b[maxN], aCnt[maxX + 1], bCnt[maxX + 1];

int main()
{
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    memset(aCnt, 0, sizeof(aCnt)), memset(bCnt, 0, sizeof(bCnt));
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      aCnt[a[i]] ++;
    }
    for (int i = 0; i < m; i ++)
    {
      scanf("%d", &b[i]);
      bCnt[b[i]] ++;
    }

    int aa = 0, bb = 0;
    for (int i = 1; i <= maxX; i ++)
      aa += aCnt[i] && !bCnt[i], bb += bCnt[i] && !aCnt[i];
    printf("%d\n", min(aa, bb));
  }
  return(0);
}