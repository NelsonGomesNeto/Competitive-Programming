#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5;
lli mod = 1e9 + 7;
int n; lli p;

int cnt(int number)
{
  int total = 0;
  while (number)
  {
    total += number / p;
    number /= p;
  }
  return(total);
}

int main()
{
  scanf("%d %lld", &n, &p);

  int ans = 0;
  for (int i = 0; i < n; i ++)
  {
    int a = i + 1, b = (i + 1) >> 1;
    ans += (cnt(a) > cnt(b) + cnt(a - b));
  }
  printf("%d\n", ans);
  return(0);
}