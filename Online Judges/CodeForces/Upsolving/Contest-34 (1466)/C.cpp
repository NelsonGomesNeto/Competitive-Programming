#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tricks with Prefix Function:
  Biggest Palindrome in Prefix: a + '#' + rev(a)
*/

const int maxN = 1e6 + 1;
char ss[maxN];
string s;

pair<vector<int>, vector<int>> manacher(string &str)
{
  int n = str.size();
  vector<int> d1(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < n && str[i - k] == str[i + k]) {
      k++;
    }
    d1[i] = k--;
    if (i + k > r) {
      l = i - k;
      r = i + k;
    }
  }
  vector<int> d2(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n && str[i - k - 1] == str[i + k]) {
      k++;
    }
    d2[i] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k ;
    }
  }
  return make_pair(d1, d2);
}

vector<int> in, out;
map<int, int> memo[maxN];
int solve(int i = 0, int curr = 0)
{
  if (i == s.size()) return 0;
  if (memo[i].count(curr)) return memo[i][curr];

  int ans = 1e6;
  curr += in[i];
  if (curr)
    ans = min(ans, solve(i + 1, 0) + 1);
  if (curr < out[i] || out[i] == 0)
    ans = min(ans, solve(i + 1, curr));
  return memo[i][curr] = ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", ss);
    s = string(ss);

    auto d12 = manacher(s);
    vector<int> d1 = d12.first, d2 = d12.second;

    vector<pair<int, int>> palindromes;
    for (int i = 0; i < s.size(); i++)
    {
      if (d1[i] > 1)
        palindromes.push_back({i - (d1[i] - 1), (d1[i] << 1) - 1});
      if (d2[i] >= 1)
        palindromes.push_back({i - d2[i], d2[i] << 1});
    }

    // palindromes.clear();
    for (int i = 0; i < s.size(); i++)
    {
      // pair
      if (i + 1 < s.size() && s[i] == s[i + 1])
        palindromes.push_back({i, 2});
      // triple
      if (i + 2 < s.size() && s[i] == s[i + 2])
        palindromes.push_back({i, 3});
    }

    in = vector<int>(s.size(), 0), out = vector<int>(s.size(), 0);
    for (auto &[i, sz]: palindromes)
      in[i]++, out[i + sz - 1]++;

    DEBUG {
      printf("%s\n", s.c_str());

      for (int i = 0; i < s.size(); i++)
        printf("%3d%c", i, i < s.size() - 1 ? ' ' : '\n');
      for (int i = 0; i < s.size(); i++)
        printf("%3d%c", d1[i], i < s.size() - 1 ? ' ' : '\n');
      for (int i = 0; i < s.size(); i++)
        printf("%3d%c", d2[i], i < s.size() - 1 ? ' ' : '\n');

      printf("palindromes (%d):\n", (int)palindromes.size());
      for (auto &[i, sz]: palindromes)
        printf("\t%5s (%d, %d)\n", s.substr(i, sz).c_str(), i, sz);

      vector<int> lol(s.size(), 0);
      for (auto &[i, sz]: palindromes)
        for (int lo = i, hi = i + sz - 1; lo <= hi; lo++)
          lol[lo]++;
      for (int i = 0; i < s.size(); i++)
        printf("%3d%c", lol[i], i < s.size() - 1 ? ' ' : '\n');

      printf("-------------\n");
    }

    for (int i = 0; i < s.size(); i++) memo[i].clear();
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
