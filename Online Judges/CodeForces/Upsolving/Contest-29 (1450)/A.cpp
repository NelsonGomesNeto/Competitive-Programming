#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    char s[n + 1]; scanf(" %s", s);

    map<char, int> cnt;
    for (int i = 0; i < n; i++)
    {
      if (!cnt.count(s[i]))
        cnt[s[i]] = 0;
      cnt[s[i]]++;
    }

    string ans = "";
    for (char l = 'a'; l <= 'z'; l++)
      if (cnt.count(l))
        for (int i = 0; i < cnt[l]; i++)
          ans += l;
    printf("%s\n", ans.c_str());
  }
  return 0;
}
