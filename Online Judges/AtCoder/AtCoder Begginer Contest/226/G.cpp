#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<lli> a(6), b(6);

int solve(int i = 5)
{
  if (i == 0) return *max_element(a.begin()+1, a.begin()+6) == 0;
  if (b[i] < a[i]) return false;

  vector<lli> aux = a, hehe = b;

  b[i] -= a[i];
  a[i] = 0;

  if (solve(i - 1)) return true;

  vector<lli> aux2 = a;
  vector<lli> auxb = b;
  vector<int> p;
  for (int k = 1; k < i; k++) p.push_back(k);
  // reverse(p.begin(), p.end());

  do
  {
    a = aux2;
    b = auxb;
    for (int j = 0; j < p.size(); j++)
      if (a[p[j]])
      {
        lli mult = i / p[j];
        while (mult >= 1)
        {
          lli rem = min(mult*b[i], a[p[j]]);
          lli used = p[j]*rem / i + (p[j]*rem % i != 0);
          a[p[j]] -= rem;
          b[i] -= used;
          b[p[j]*rem % i]++;
          mult--;
        }
      }
    if (solve(i - 1)) return true;
  }
  while (next_permutation(p.begin(), p.end()));

  a = aux;
  b = hehe;

  return false;
}

int main()
{
  int t;
  while (~scanf("%d", &t))
  {
    for (int i = 0; i < t; i++)
    {
      for (int j = 1; j <= 5; j++) scanf("%lld", &a[j]);
      for (int j = 1; j <= 5; j++) scanf("%lld", &b[j]);

      int ans = solve();
      printf("%s\n", ans ? "Yes" : "No");
    }
  }
  return 0;
}