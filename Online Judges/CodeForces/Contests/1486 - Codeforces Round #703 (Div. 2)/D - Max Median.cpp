#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
int a[maxN];

int b[maxN];
int acc[maxN + 1];
int pos[2*(maxN + 1)];
bool can(int x)
{
  for (int i = 0; i < n; i++)
  {
    b[i] = a[i] >= x ? 1 : -1;
    acc[i + 1] = acc[i] + b[i];
  }

  /*
  1 2 3 2  1
  -1 1 1 1 -1
  0 -1 0 1 2 1
  */

  memset(pos, -1, sizeof(pos));
  for (int i = n; i >= 0; i--)
    pos[acc[i] + n] = max(pos[acc[i] + n], i - 1);
  for (int i = 2*n; i >= 0; i--)
    pos[i] = max(pos[i], pos[i + 1]);

  DEBUG {
    printf("\t%d\n", n);
    for (int i = 0; i <= 2*n; i++)
      printf("%3d%c", i - n, i < 2*n ? ' ' : '\n');
    for (int i = 0; i <= 2*n; i++)
      printf("%3d%c", pos[i], i < 2*n ? ' ' : '\n');
  }

  for (int i = 0; i < n; i++)
  {
    // x
    // y - x >= 1
    // y >= 1 + x
    int curr = acc[i] + 1;
    int j = pos[curr + n];

    DEBUG printf("\t%d %d %d\n", x, curr, j);

    int size = j - i + 1;
    if (size >= k)
      return true;
  }
  return false;
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int lo = 1, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if (can(mid)) lo = mid;
      else hi = mid - 1;
    }
    printf("%d\n", lo);


    // printf("%d\n", can(2));
    // printf("-----------\n");
  }
  return 0;
}
