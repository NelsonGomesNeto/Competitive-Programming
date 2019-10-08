#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Find all divisors of every number

  What if you knew the latest position in which occurred a number divisible by x
  If we had that, for each query:
    ans = divisors[x].size()
    for d in divisors[x]:
      ans -= i - pos[d] <= y

  But how can we known the latest position in which occurred a number divisible
  by x? Just update that position while you're iterating through the divisors
  of the current query:
    for d in divisors[x]:
      pos[d] = i
*/

const int maxN = 1e5 + 1; int n;
int pos[maxN];
vector<int> divisors[maxN];
 
int main()
{
  for (int i = 1; i < maxN; i ++)
    for (int j = 1; j*i < maxN; j ++)
      divisors[j*i].push_back(i);
  memset(pos, -1, sizeof(pos));
 
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int x, y; scanf("%d %d", &x, &y);
    int ans = divisors[x].size();
    for (int j: divisors[x])
    {
      ans -= i - pos[j] <= y;
      pos[j] = i;
    }
    printf("%d\n", ans);
  }
 
  return 0;
}