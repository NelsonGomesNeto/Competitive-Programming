#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
char ss[maxN + 1];
int cnt[256];
string s;

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);
    sort(s.begin(), s.end(), greater<char>());
    memset(cnt, 0, sizeof(cnt));
    for (char c: s) cnt[c]++;

    string ans = "";
    for (char i = 'a'; i < 'z'; i++)
    {
      cnt[i + 1] += cnt[i] >> 1;
      cnt[i] = cnt[i] & 1;
    }
    for (char i = 'z'; i >= 'a'; i--)
      while (cnt[i])
      {
        ans += i;
        cnt[i]--;
      }
    printf("%s\n", ans.c_str());
  }
  return 0;
}