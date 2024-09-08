#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, maxC = 60; int n, requiredFriends, m, p;
char s[maxN][maxC + 1];
int cnt[maxC];
vector<int> coinPos;
vector<vector<int>> friends;

int initialPos;

string bin(lli num)
{
  string b = "";
  // for (int i = 0; i < m; i++)
  for (int i = m - 1; i >= 0; i--)
    if (num & (1LL << i))
      b += '1';
    else
      b += '0';
  return b;
}

int best; lli bestMask;
void solve(int ci = 0, int lo = 0, int hi = n - 1, lli nowMask = 0, int now = 0)
{
  if (hi - lo + 1 >= requiredFriends)
  {
    if (now > best)
      best = now, bestMask = nowMask;
  }
  else
    return;
  if (ci == coinPos.size())
    return;

  int i = coinPos[ci];

  int pos = hi + 1;
  if (ci)
  {
    for (int j = lo, l = lo, r = hi; j <= hi; j++)
    {
      int at = friends[ci - 1][j];
      if (s[at][i] == '1') friends[ci][r--] = at, pos--;
      else friends[ci][l++] = at;
    }
  }
  else
    pos = initialPos;

  if (pos == hi + 1) // all zeroes
    solve(ci + 1, lo, hi, nowMask, now);
  else if (pos == lo) // all ones
    solve(ci + 1, lo, hi, nowMask | (1LL << i), now + 1);
  else
  {
    solve(ci + 1, lo, hi, nowMask, now);
    solve(ci + 1, pos, hi, nowMask | (1LL << i), now + 1);
  }
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &p))
  {
    requiredFriends = ((n + 1) >> 1);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s[i]);
      for (int j = 0; j < m; j++)
        cnt[j] += s[i][j] == '1';
    }

    vector<pair<int, int>> rp;
    for (int i = 0; i < m; i++)
      rp.push_back({cnt[i], i});
    sort(rp.begin(), rp.end(), less<pair<int, int>>());

    coinPos.clear(), friends.clear();
    for (int i = 0; i < m; i++)
      if (cnt[rp[i].second] >= requiredFriends)
      {
        coinPos.push_back(rp[i].second);
        friends.push_back(vector<int>(n));
      }
    if (!coinPos.empty())
    {
      initialPos = n;
      for (int i = 0, l = 0, r = n - 1; i < n; i++)
      {
        int p = s[i][coinPos[0]] == '1' ? r-- : l++;
        if (s[i][coinPos[0]] == '1') initialPos--;

        friends[0][p] = i;
      }
    }

    best = -1;
    solve();
    string res = bin(bestMask);
    reverse(res.begin(), res.end());
    printf("%s\n", res.c_str());
  }
  return 0;
}