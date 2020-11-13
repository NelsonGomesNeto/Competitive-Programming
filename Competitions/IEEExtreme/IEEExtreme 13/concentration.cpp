#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e3 + 1; int n;
bool done[2*maxN];
int cards[2*maxN], now = 0;
int cnt[maxN];

int main()
{
  scanf("%d", &n);
  while (now < n)
  {
    for (int i = 1; i <= n; i ++)
    {
      printf("%d %d\n", i, i + n); fflush(stdout);
      string s;
      if (s != "MATCH")
      {
        getline(cin, s);
        if (s.length() <= 1) getline(cin, s);
        int lo, hi;
        sscanf(s.c_str(), "%d %d", &lo, &hi);
        cards[lo] = i, cards[hi] = i + n;
        cnt[lo] ++, cnt[hi] ++;
      }
    }

    for (int i = 1; i <= 2*n; i ++)
    {
      if (cnt[i] < 2) continue;
      for (int j = i + 1; j <= 2*n; j ++)
        if (cards[i] == cards[j])
        {
          printf("%d %d\n", i, j); fflush(stdout);
          break;
        }
    }
  }
  printf("-1\n"); fflush(stdout);
  
  return 0;
}