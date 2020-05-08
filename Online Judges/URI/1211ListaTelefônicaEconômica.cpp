#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxLen = 201; int n;
char ss[maxLen];
string numbers[maxN];

int solve(int at = 0, int lo = 0, int hi = n - 1)
{
  if (at == numbers[0].size()) return 0;

  int ans = 0;
  for (int i = lo; i <= hi; i++)
  {
    int j = i;
    while (j + 1 <= hi && numbers[j + 1][at] == numbers[i][at]) j++;
    ans += 1 + solve(at + 1, i, j);
    i = j;
  }
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      numbers[i] = string(ss);
    }
    sort(numbers, numbers+n);

    int ans = numbers[0].size()*n - solve();
    printf("%d\n", ans);
  }
  return 0;
}