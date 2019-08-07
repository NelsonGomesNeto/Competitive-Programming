#include <bits/stdc++.h>
using namespace std;

const int maxSeconds = 24*60*60;
int in[maxSeconds + 1], out[maxSeconds + 1];

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    int h1, m1, s1, h2, m2, s2, seconds1, seconds2;
    scanf("%d:%d:%d %d:%d:%d", &h1, &m1, &s1, &h2, &m2, &s2);
    seconds1 = h1*60*60 + m1*60 + s1;
    seconds2 = h2*60*60 + m2*60 + s2;
    in[seconds1] ++, out[seconds2] ++;
  }

  int ans = 0, now = 0;
  for (int i = 0; i <= maxSeconds; i ++)
  {
    now += in[i];
    ans = max(ans, now);
    now -= out[i];
  }
  printf("%d\n", ans);

  return(0);
}