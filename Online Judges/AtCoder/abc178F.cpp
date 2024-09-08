#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN], b[maxN];
int ans[maxN];

multiset<int> lol, neg;
bool can = true;
void reset()
{
  lol.clear(), neg.clear();
  for (int i = n - 1; i >= 0; i--)
    lol.insert(b[i]), neg.insert(-b[i]);
  memset(ans, -1, sizeof(ans));
  can = true;
}

void fix2()
{
  if (lol.size() > 1000) return;

  for (int i = 0; i < n; i++)
    if (ans[i] == -1)
      for (int j = 0; j < n; j++)
        if (i != j && ans[j] != a[i])
        {
          bool done = false;
          if (lol.lower_bound(a[j] + 1) != lol.end())
          {
            ans[i] = ans[j];
            ans[j] = *lol.lower_bound(a[j] + 1);
            done = true;
          }
          if (!done && neg.lower_bound(-(a[j] - 1)) != neg.end())
          {
            ans[i] = ans[j];
            ans[j] = -(*neg.lower_bound(-(a[j] - 1)));
            done = true;
          }

          if (done)
          {
            lol.erase(lol.find(ans[j]));
            neg.erase(neg.find(-ans[j]));
            break;
          }
        }

  can = true;
  for (int i = 0; i < n; i++)
    if (ans[i] == -1)
      can = false;
}
void fix()
{
  multiset<int> was, nwas;
  for (int i: lol) was.insert(i);
  for (int i: neg) nwas.insert(i);

  for (int i = 0; i < n; i++)
    if (ans[i] == -1)
    {
      if (was.lower_bound(a[i] + 1) != was.end())
      {
        int v = *was.lower_bound(a[i] + 1);
        if (v != a[i])
          ans[i] = v;
      }
      if (ans[i] == -1 && nwas.lower_bound(-(a[i] - 1)) != nwas.end())
      {
        int v = -(*nwas.lower_bound(-(a[i] - 1)));
        if (v != a[i])
          ans[i] = v;
      }

      if (ans[i] != -1)
      {
        was.erase(was.find(ans[i])), nwas.erase(nwas.find(-ans[i]));
        lol.erase(lol.find(ans[i])), neg.erase(neg.find(-ans[i]));
      }
    }

  can = true;
  for (int i = 0; i < n; i++)
    if (ans[i] == -1)
      can = false;
  if (!can) fix2();
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%d", &b[i]);

    reset();
    for (int i = n - 1; i >= 0 && can; i--)
    {
      if (*lol.begin() != a[i])
        ans[i] = *lol.begin();
      else if (lol.lower_bound(a[i] + 1) != lol.end())
        ans[i] = *lol.lower_bound(a[i] + 1);
      else if (*lol.rbegin() != a[i])
        ans[i] = *lol.rbegin();
      else
        can = false;

      if (can)
        lol.erase(lol.find(ans[i])), neg.erase(neg.find(-ans[i]));
    }
    if (!can) fix();

    if (!can)
    {
      reset();
      for (int i = 0; i < n && can; i++)
      {
        if (*lol.rbegin() != a[i])
          ans[i] = *lol.rbegin();
        else if (neg.lower_bound(-(a[i] - 1)) != neg.end())
          ans[i] = -(*neg.lower_bound(-(a[i] - 1)));
        else if (*lol.begin() != a[i])
          ans[i] = *lol.begin();
        else
          can = false;

        if (can)
          lol.erase(lol.find(ans[i])), neg.erase(neg.find(-ans[i]));
      }
    }
    if (!can) fix();

    if (!can)
    {
      reset();
      for (int i = n - 1; i >= 0 && can; i--)
      {
        if (lol.lower_bound(a[i] + 1) != lol.end())
          ans[i] = *lol.lower_bound(a[i] + 1);
        else if (*lol.begin() != a[i])
          ans[i] = *lol.begin();
        else if (*lol.rbegin() != a[i])
          ans[i] = *lol.rbegin();
        else
          can = false;

        if (can)
          lol.erase(lol.find(ans[i])), neg.erase(neg.find(-ans[i]));
      }
    }
    if (!can) fix();

    if (!can)
    {
      reset();
      for (int i = 0; i < n && can; i++)
      {
        if (neg.lower_bound(-(a[i] - 1)) != neg.end())
          ans[i] = -(*neg.lower_bound(-(a[i] - 1)));
        else if (*lol.rbegin() != a[i])
          ans[i] = *lol.rbegin();
        else if (*lol.begin() != a[i])
          ans[i] = *lol.begin();
        else
          can = false;

        if (can)
          lol.erase(lol.find(ans[i])), neg.erase(neg.find(-ans[i]));
      }
    }
    if (!can) fix();

    printf("%s\n", can ? "Yes" : "No");
    if (can)
      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
