#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int solve(vector<int> &a, int i = 0, int sum = 0)
{
  if (i == a.size()) return ~sum & 1;
  return solve(a, i + 1, sum) + solve(a, i + 1, sum + a[i]);
}

int main()
{
  int a, b, c; scanf("%d %d %d", &a, &b, &c);
  vector<int> all = {a, b, c};

  int ans = solve(all);
  printf("%d\n", ans);

  return 0;
}