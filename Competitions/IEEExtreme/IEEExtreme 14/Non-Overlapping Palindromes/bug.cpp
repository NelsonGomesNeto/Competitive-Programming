#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<string, int>
#define pii pair<pair<double, double>, double>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 5001
#define mod 1000000007

vector<int> d1;
vector<int> d2;

void manacher(string s)
{
  d1.resize(s.size());
  d2.resize(s.size());
  int l = 0, r = -1;
  for (int i = 0; i < s.size(); i++)
  {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < s.size() && s[i - k] == s[i + k])
      k++;
    d1[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k, r = i + k;
  }
  l = 0, r = -1;
  for (int i = 0; i < s.size(); i++)
  {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < s.size() && s[i - k - 1] == s[i + k])
      k++;
    d2[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k - 1, r = i + k;
  }
}
bool is_palindrome(string s)
{
  string t = s;
  reverse(t.begin(), t.end());
  for (int i = 0; i < s.size(); i++)
    if (s[i] != t[i])
      return false;
  return true;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    string s;
    cin >> s;
    manacher(s);
    if (is_palindrome(s))
    {
      cout << s.size() - 1 << endl;
      continue;
    }
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
      for (int j = 0; j < s.size(); j++)
      {
        int k = d1[i] - 1, kk = d1[j] - 1;
        int l = i - k, r = i + k;
        int ll = j - kk, rr = j + kk;
        if (k >= 0 && kk >= 0)
        {
          if (r < ll)
          {
            int curr = (r - l) + 1;
            curr += (rr - ll) + 1;
            ans = max(ans, curr);
          }
        }
        k = d1[i] - 1, kk = d2[j] - 1;
        if (k >= 0 && kk >= 0)
        {
          l = i - k, r = i + k;
          ll = j - kk - 1, rr = j + kk;
          if (r < ll)
          {
            int curr = (r - l) + 1;
            curr += (rr - ll) + 1;
            ans = max(ans, curr);
          }
        }
        k = d2[i] - 1, kk = d2[j] - 1;
        if (k >= 0 && kk >= 0)
        {
          l = i - k - 1, r = i + k;
          ll = j - kk - 1, rr = j + kk;
          if (r < ll)
          {
            int curr = (r - l) + 1;
            curr += (rr - ll) + 1;
            ans = max(ans, curr);
          }
        }
        k = d2[i] - 1, kk = d1[j] - 1;
        if (k >= 0 && kk >= 0)
        {
          l = i - k - 1, r = i + k;
          ll = j - kk, rr = j + kk;
          if (r < ll)
          {
            int curr = (r - l) + 1;
            curr += (rr - ll) + 1;
            ans = max(ans, curr);
          }
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
