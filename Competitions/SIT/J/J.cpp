#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxM = 100, maxB = 4, maxN = 10; int m, n;
short memo[maxM][1 << 20];
int a[maxN], b[maxN];

short solve(int i = 0, int curr = 0)
{
  // printf("\t%d || %d ||", i, curr);
  // for (int j = 0; j < n; j++)
  // {
  //   int resting = (((curr>>(2*j)) & 1) << 1) + ((curr>>(2*j + 1)) & 1);
  //   printf(" %d", resting);
  // }
  // printf(" || %d\n", m);

  if (i >= m)
    return 0;
  short &ans = memo[i][curr];
  if (ans != -1)
    return ans;
  
  int afterRest = curr;
  for (int j = 0; j < n; j++)
  {
    int resting = (((afterRest>>(2*j)) & 1) << 1) + ((afterRest>>(2*j + 1)) & 1);
    if (resting) resting--;
    afterRest &= ~(1 << (2*j));
    afterRest &= ~(1 << (2*j + 1));
    afterRest |= ((resting >> 1) & 1) << (2*j);
    afterRest |= (resting & 1) << (2*j + 1);
  }

  ans = 1e4;
  for (int j = 0; j < n; j++)
  {
    int resting = (((curr>>(2*j)) & 1) << 1) + ((curr>>(2*j + 1)) & 1);
    if (resting == 0)
    {
      int unRest = afterRest;
      unRest &= ~(1 << (2*j));
      unRest &= ~(1 << (2*j + 1));
      printf("\t\t%d", unRest);
      unRest |= ((b[j] >> 1) & 1) << (2*j);
      unRest |= (b[j] & 1) << (2*j + 1);
      printf(" %d\n", unRest);
      short res = 1 + solve(i + a[j], unRest);
      ans = min(ans, res);
    }
  }
  if (afterRest != curr)
  {
    short res = 1 + solve(i, afterRest);
    ans = min(ans, res);
  }

  return ans;
}

int main()
{
  while (~scanf("%d %d", &m, &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d %d", &a[i], &b[i]);
      b[i]--;
    }

    memset(memo, -1, sizeof(memo));
    short ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}