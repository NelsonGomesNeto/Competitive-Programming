#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5000; int n, m;
bool has[10];

bool valid(int number)
{
  memset(has, false, sizeof(has));
  while (number)
  {
    if (has[number % 10]) return(false);
    has[number % 10] = true;
    number /= 10;
  }
  return(true);
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    int ans = 0;
    for (int i = n; i <= m; i ++)
      ans += valid(i);
    printf("%d\n", ans);
  }
  return(0);
}