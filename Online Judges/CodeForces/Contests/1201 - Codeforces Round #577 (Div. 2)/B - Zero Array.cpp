#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN], sum, biggest;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    sum = biggest = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      sum += a[i], biggest = max(biggest, a[i]);
    }
    printf("%s\n", (!(sum & 1) && biggest <= (sum >> 1)) ? "YES" : "NO");
  }

  return(0);
}