#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  Make a 100 queries
  There will be a segment of size 200 where c[i] != k
    < k on the left
    > k on the right
  It will take 500 queries to find the segment some one from this segment
  The segment will also grow for each of this query

  There are 400 queries left
*/

const int maxN = 1e5; int n, sqn; lli k;
int queries;

lli query(int pos)
{
  queries++;
  assert(queries <= 1e3);
  printf("? %d\n", pos + 1); fflush(stdout);
  lli res; scanf("%lld", &res);
  return res;
}

int main()
{
  while (~scanf("%d %lld", &n, &k))
  {
    queries = 0;
    sqn = sqrt(n);
    if (n < 10)
    {
      for (int i = 0; i < 100; i++)
        query(0);
      int ans = -1;
      for (int i = 0; i < n; i++)
      {
        lli value = query(i);
        if (value < k)
        {
          int j = i;
          while ((j + 1) % n != i && query((j + 1) % n) <= k)
            j = (j + 1) % n;
          ans = j;
          break;
        }
      }
      // if (ans == -1)
      // {
      //   for (int i = 0; i < n; i++)
      // }
      printf("! %d\n", ans + 1); fflush(stdout);
      continue;
    }

    int bugAt = -1;
    if (n < 100)
      for (int i = 0; i < 100; i++)
        query(0);

    for (int t = 0; t < 2 && bugAt == -1; t++)
      for (int i = t; i < n; i += sqn)
      {
        lli value = query(i);
        if (value < k)
        {
          bugAt = i;
          break;
        }
      }
    assert(bugAt != -1);

    int ans = -1;
    while (true)
    {
      if (bugAt == n) bugAt = 0;
      lli value = query(bugAt);
      if (value >= k)
      {
        ans = bugAt;
        break;
      }
      bugAt++;
    }

    printf("! %d\n", ans + 1); fflush(stdout);
    // break;
  }


  return 0;
}
