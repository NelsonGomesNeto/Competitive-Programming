#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
bool possible[maxN + 1];
list<int> ans;

void can(int l, int r, int a, int b)
{
  int games = a + b;
  for (int wl = 0; wl <= l && wl <= a; wl++)
  {
    int k = l - wl;
    k += a - wl;
    if (k <= games) possible[k] = true;
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int a, b; scanf("%d %d", &a, &b);
    if (a > b) swap(a, b);
    int games = a + b;
    for (int i = 0; i <= games; i++) possible[i] = false;

    int l = games >> 1, r = (games + 1) >> 1;
    can(l, r, a, b);
    can(r, l, a, b);

    ans.clear();
    for (int i = 0; i <= games; i++)
      if (possible[i])
        ans.push_back(i);
    printf("%d\n", (int)ans.size());
    for (int i: ans)
      printf("%d ", i);
    printf("\n");
  }
  return 0;
}
