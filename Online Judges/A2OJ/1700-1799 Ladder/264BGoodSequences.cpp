#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;
 
const int maxN = 1e5 + 1; int n;
vector<int> divisors[maxN];
int a[maxN], memo[maxN];
 
int main()
{
  for (int i = 2; i < maxN; i ++)
    for (int j = 1; j*i < maxN; j ++)
      divisors[j*i].push_back(i);
  DEBUG for (int i = 1; i < 10; i ++)
  {
    printf("%d - %d divisors:\n\t", i, (int) divisors[i].size());
    for (int j: divisors[i]) printf("%d ", j);
    printf("\n");
  }
 
  while (scanf("%d", &n) != EOF)
  {
    memset(memo, 0, sizeof(memo));
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
 
    for (int i = 0; i < n; i ++)
    {
      int maximum = 0;
      for (int d: divisors[a[i]])
        maximum = max(maximum, ++ memo[d]);
      for (int d: divisors[a[i]])
        memo[d] = maximum;
    }
 
    printf("%d\n", max(1, *max_element(memo, memo+maxN)));
  }
 
  return 0;
}