#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 102
#define mod 998244353

void ans(int n)
{
  cout << n << endl;
  fflush(stdout);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, n, b, p;
  cin >> t >> n >> b >> p;
  while (t--)
  {
    vector<int> v(n, 0);
    for (int i = 0; i < n * b; i++)
    {
      int k;
      cin >> k;
      if (k == 9)
      {
        bool ok = false;
        for (int j = 0; j < v.size(); j++)
        {
          if (v[j] == b - 1)
          {
            v[j]++;
            ok = true;
            ans(j + 1);
            break;
          }
        }
        if (!ok)
        {
          int choose = -1;
          for (int j = 0; j < v.size(); j++)
          {
            if (v[j] == b)
              continue;
            if (choose == -1 || v[j] > v[choose])
              choose = j;
          }
          v[choose]++;
          ans(choose + 1);
        }
      }
      else if (k == 8)
      {
        bool ok = false;
        for (int j = 0; j < v.size(); j++)
        {
          if (v[j] == b - 2)
          {
            v[j]++;
            ok = true;
            ans(j + 1);
            break;
          }
        }
        if (!ok)
        {
          int choose = -1;
          for (int j = 0; j < v.size(); j++)
          {
            if (v[j] >= b - 1)
              continue;
            if (choose == -1 || v[j] > v[choose])
              choose = j;
          }
          if (choose != -1)
          {
            v[choose]++;
            ans(choose + 1);
            ok = true;
          }
        }
        if (!ok)
        {
          int choose = -1;
          for (int j = 0; j < v.size(); j++)
          {
            if (v[j] == b)
              continue;
            if (choose == -1 || v[j] > v[choose])
              choose = j;
          }
          if (choose != -1)
          {
            v[choose]++;
            ans(choose + 1);
            ok = true;
          }
        }
      }
      else
      {
        bool ok = false;
        for (int j = 0; j < v.size(); j++)
        {
          if (v[j] < b - 2)
          {
            v[j]++;
            ok = true;
            ans(j + 1);
            break;
          }
        }
        if (!ok)
        {
          for (int j = 0; j < v.size(); j++)
          {
            if (v[j] < b - 1)
            {
              v[j]++;
              ok = true;
              ans(j + 1);
              break;
            }
          }
        }
        if (!ok)
        {
          for (int j = 0; j < v.size(); j++)
          {
            if (v[j] < b)
            {
              v[j]++;
              ans(j + 1);
              break;
            }
          }
        }
      }
    }
  }
  return 0;
}