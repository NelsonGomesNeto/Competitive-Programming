#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
char s[maxN + 1];
int cnt[256];

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));
    for (n = 0; s[n]; n++)
      cnt[s[n]]++;

    int even = 0, odd = 0;
    for (char c = 'a'; c <= 'z'; c++)
      even += !(cnt[c] & 1), odd += cnt[c] & 1;

    bool first = true;
    while (odd > 1)
    {
      bool done = false;
      for (char c = 'a'; c <= 'z'; c++)
        if (cnt[c] && !(cnt[c] & 1))
        {
          odd++, even--, done = true;
          cnt[c]--;
          break;
        }
      if (!done)
        for (char c = 'a'; c <= 'z'; c++)
          if (cnt[c] && (cnt[c] & 1))
          {
            cnt[c]--, odd--, even++;
            break;
          }
      first = !first;
    }
    printf("%s\n", first ? "First" : "Second");
  }
  return 0;
}