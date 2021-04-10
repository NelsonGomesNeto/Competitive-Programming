#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int n;
struct Problem
{
  int p, tag; int s;
};
Problem problems[maxN];
int getScore(int i, int j)
{
  return abs(problems[i].s - problems[j].s);
}

lli memo[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      problems[i].p = i;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &problems[i].tag);
      problems[i].tag--;
    }
    for (int i = 0; i < n; i++)
      scanf("%d", &problems[i].s);

    for (int i = 0; i < n; i++)
      memo[i] = 0;
    for (int i = 0; i < n; i++)
      for (int j = i - 1; j >= 0; j--)
        if (problems[i].tag != problems[j].tag)
        {
          lli bestToI = memo[i], bestToJ = memo[j], score = getScore(i, j);
          memo[i] = max(memo[i], bestToJ + score);
          memo[j] = max(memo[j], bestToI + score);
        }
    printf("%lld\n", *max_element(memo, memo+n));
  }
  return 0;
}
