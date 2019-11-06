#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
char s[maxN]; lli n, k;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lld %lld", &n, &k);
    scanf(" %s", s);
    vector<int> zeros;
    int start = 0;
    while (start < n && s[start] == '0') start ++;
    for (int i = start; i < n; i ++)
    {
      if (s[i] == '0')
        zeros.push_back(i);
    }
    for (int i = 0; i < zeros.size() && k; i ++, start ++)
    {
      if (zeros[i] - start <= k)
        k -= zeros[i] - start, swap(s[zeros[i]], s[start]);
      else
      {
        swap(s[zeros[i]], s[zeros[i] - k]);
        k = 0;
      }
    }
    printf("%s\n", s);
  }
  return 0;
}
