#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int p[maxN];
set<int> nums;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    nums.clear();
    for (int i = 0; i <= n; i++)
      nums.insert(i);
    for (int i = 0; i < n; i++)
      scanf("%d", &p[i]);

    for (int i = 0; i < n; i++)
    {
      if (nums.count(p[i]))
        nums.erase(p[i]);
      printf("%d\n", *nums.begin());
    }
  }
  return 0;
}