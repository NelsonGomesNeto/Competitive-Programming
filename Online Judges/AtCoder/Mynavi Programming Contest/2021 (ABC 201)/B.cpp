#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 15;
char ss[maxS + 1];

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    vector<pair<int, string>> m;
    for (int i = 0; i < n; i++)
    {
      int t;
      scanf(" %s %d", ss, &t);
      m.push_back({t, string(ss)});
    }

    sort(m.begin(), m.end());

    printf("%s\n", m[n - 2].second.c_str());
  }
  return 0;
}