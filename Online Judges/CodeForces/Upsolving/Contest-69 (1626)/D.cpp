#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
vector<int> aa;
int acc[maxN + 1];

vector<int> pots;
int calcExtra(int x)
{
  int minimum = 1e9;
  for (int p: pots)
    if (x <= p)
      minimum = min(minimum, p - x);
  return minimum;
}

int main()
{
  for (int pot = 1; pot <= 2*maxN; pot *= 2)
    pots.push_back(pot);

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    sort(a, a+n);

    aa.clear();
    for (int i = 0; i < n; i++)
    {
      int j = i;
      while (j + 1 < n && a[j + 1] == a[i])
        j++;
      aa.push_back(j - i + 1);
      i = j;
    }

    for (int i = 0; i < aa.size(); i++)
      acc[i + 1] = acc[i] + aa[i];

    int ans = 1e9;
    for (int i = 0; i < aa.size(); i++)
    {
      // x = i, y > x

      for (int p: pots) // powers of two
      {
        int lo = i + 1, hi = aa.size();
        while (lo < hi)
        {
          int mid = (lo + hi + 1) >> 1;
          if (acc[mid] - acc[i + 1] <= p) lo = mid;
          else hi = mid - 1;
        }

        if (acc[lo] - acc[i + 1] <= p)
        {
          int lightWeight = calcExtra(acc[i + 1]);
          int midWeight = calcExtra(acc[lo] - acc[i + 1]);
          int heavyWeight = calcExtra(acc[aa.size()] - acc[lo]);
          DEBUG printf("\t%d - %d %d - %d %d %d\n", i, p, lo, lightWeight, midWeight, heavyWeight);
          ans = min(ans, lightWeight + midWeight + heavyWeight);
        }
      }

      ans = min(ans, calcExtra(acc[i + 1]) + calcExtra(0) + calcExtra(acc[aa.size()] - acc[i + 1]));
    }
    printf("%d\n", ans);
  }
  return 0;
}