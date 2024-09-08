#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    vector<int> even, odd;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]);
      if (a[i] & 1) odd.push_back(i);
      else even.push_back(i);
    }

    if (!even.empty())
      printf("1\n%d\n", even[0] + 1);
    else if (odd.size() >= 2)
      printf("2\n%d %d\n", odd[0] + 1, odd[1] + 1);
    else
      printf("-1\n");
  }
  return 0;
}
