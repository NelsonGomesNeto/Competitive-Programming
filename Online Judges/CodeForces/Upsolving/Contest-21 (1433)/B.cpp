#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
int a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    vector<int> pos;
    for (int i = 0; i < n; i++)
      if (a[i] == 1)
        pos.push_back(i);

    int ans = 0;
    for (int i = 1; i < pos.size(); i++)
      ans += pos[i] - pos[i - 1] - 1;
    printf("%d\n", ans);
  }
  return 0;
}
