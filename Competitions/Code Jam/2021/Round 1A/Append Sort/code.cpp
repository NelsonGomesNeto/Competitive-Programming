#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
lli x[maxN];
string a[maxN];

int comp(string aa, string bb)
{
  if (aa.size() > bb.size()) return 1;
  else if (aa.size() < bb.size()) return -1;
  else
  {
    for (int i = 0; i < aa.size(); i++)
    {
      if (aa[i] > bb[i])
        return 1;
      else if (aa[i] < bb[i])
        return -1;
    }
    return 0;
  }
}

void addOne(string &num)
{
  int i = num.size() - 1;
  while (i >= 0 && num[i] == '9')
    num[i--] = '0';
  if (i < 0)
    num = '1' + num;
  else
    num[i]++;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &x[i]);
      a[i] = to_string(x[i]);
      DEBUG printf("\t\t%s\n", a[i].c_str());
    }

    int ans = 0;
    for (int i = 1; i < n; i++)
      if (comp(a[i - 1], a[i]) >= 0)
      {
        if (comp(a[i - 1], a[i]) == 0 || a[i - 1].size() == a[i].size())
          a[i] += '0', ans++;
        else
        {
          if (comp(a[i - 1].substr(0, a[i].size()), a[i]) < 0)
          {
            while (comp(a[i - 1], a[i]) >= 0)
              a[i] += '0', ans++;
          }
          else if (comp(a[i - 1].substr(0, a[i].size()), a[i]) == 0)
          {
            string original = a[i];
            int originalSize = a[i].size();
            ans += a[i - 1].size() - a[i].size();
            a[i] += a[i - 1].substr(a[i].size(), a[i - 1].size() - a[i].size());

            // bool done = false;
            // for (int j = a[i].size() - 1; j >= originalSize && !done; j--)
            //   if (a[i][j] < '9')
            //     a[i][j]++, done = true;
            // if (!done)
            // {
            //   for (int j = a[i].size() - 1; j >= originalSize && !done; j--)
            //     a[i][j] = '0';
            //   a[i] += '0', ans++;
            // }
            string prv = a[i];
            addOne(a[i]);
            if (prv.substr(0, originalSize) != a[i].substr(0, originalSize))
            {
              a[i] = original;
              while (comp(a[i - 1], a[i]) >= 0)
                a[i] += '0';
              ans++;
            }
            else
              ans += a[i].size() - prv.size();

            assert(comp(a[i - 1], a[i]) < 0);
          }
          else
          {
            while (comp(a[i - 1], a[i]) >= 0)
              a[i] += '0', ans++;
          }
        }
      }
    for (int i = 1; i < n; i++)
      assert(comp(a[i - 1], a[i]) < 0);
    DEBUG
      for (int i = 0; i < n; i++)
        printf("\t%s\n", a[i].c_str());
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}