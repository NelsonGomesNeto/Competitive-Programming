#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 1e6;
const int maxN = 15; int n, k;
char ss[maxS + 1];
int cnt[256];
string s[maxN];
bool has[maxN][256];
vector<char> letters;

int main()
{
  for (int i = 'a'; i <= 'z'; ++i) letters.push_back(i);
  for (int i = 'A'; i <= 'Z'; ++i) letters.push_back(i);

  while (~scanf("%d %d", &n, &k))
  {
    memset(has, false, sizeof(has));
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      s[i] = string(ss);
      for (char c : s[i])
        has[i][c] = true;
    }

    int ans = 0;
    for (int mask = 0, end = 1 << n; mask < end; ++mask)
    {
      int lettersCount = 0;
      for (char c : letters)
      {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
          if (mask & (1 << i))
            cnt += has[i][c];

        if (cnt == k)
          ++lettersCount;
      }
      DEBUG printf("\t%d %d\n", mask, lettersCount);
      ans = max(ans, lettersCount);
    }
    printf("%d\n", ans);
  }
  return 0;
}
