#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, x;
int a[maxN];
bool visited[maxN];

int main()
{
  while (~scanf("%d %d", &n, &x))
  {
    fill(visited, visited+n, false);
    x--;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    int sz = 0, at = x;
    while (!visited[at])
    {
      visited[at] = true;
      at = a[at], sz++;
    }
    printf("%d\n", sz);
  }
  return 0;
}