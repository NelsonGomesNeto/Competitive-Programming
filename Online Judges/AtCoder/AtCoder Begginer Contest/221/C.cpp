#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli cut(vector<int> &d, int i)
{
  if (d[0] == i || d.back() == 0) return 0;

  lli a = 0;
  for (int j = i; j >= 0; j--)
    a = a*10 + d[j];
  lli b = 0;
  for (int j = d.size() - 1; j > i; j--)
    b = b*10 + d[j];

  return a * b;
}

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    vector<int> digits;
    int aux = n;
    while (aux)
    {
      digits.push_back(aux % 10);
      aux /= 10;
    }

    sort(digits.begin(), digits.end());

    lli ans = 0;
    do
    {
      for (int i = 0; i + 1 < digits.size(); i++)
        ans = max(ans, cut(digits, i));
    }
    while (next_permutation(digits.begin(), digits.end()));

    printf("%lld\n", ans);
  }
  return 0;
}