#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n;
char s[maxN];
int a[maxN];

int main()
{
  scanf("%s", s);

  n = strlen(s);
  for (int i = n - 1; i >= 0; i --)
  {
    if (s[i] == '>')
    {
      a[i + 1] = 0;
      int j = i, v = 1;
      while (j - 1 >= 0 && s[j - 1] == '>')
        a[j --] = v ++;
      a[j --] = v;
      i = j + 1;
    }
  }
  for (int i = 0; i < n; i ++)
  {
    if (s[i] == '<')
    {
      int j = i;
      while (j + 1 < n && s[j + 1] == '<')
        j ++;
      j ++;
      int k = j;
      int v = max(a[j], j - i);
      while (j != i)
        a[j --] = v --;
      a[j] = v;
      i = k - 1;
    }
  }
  if (s[0] == '<')
  {
    int j = 0;
    while (j + 1 < n && s[j + 1] == '<') j ++;
    for (int i = 0; i <= j; i ++)
      a[i] = i;
  }
  if (s[n - 1] == '>')
  {
    int j = n - 1;
    while (j - 1 >= 0 && s[j - 1] == '>') j --;
    for (int i = n, v = 0; i > j; i --)
      a[i] = v ++;
  }
  for (int i = 0; i < n - 1; i ++)
  {
    if (s[i] == '>' && s[i + 1] == '<')
    {
      int j = i + 1;
      while (j + 1 < n && s[j + 1] == '<') j ++;
      for (int k = i + 1, v = 0; k <= j; k ++)
        a[k] = v ++;
      i = j;
    }
  }
  DEBUG {
    for (int i = 0; i <= n; i ++)
      printf("%d %c ", a[i], i < n ? s[i] : '\n');
    bool valid = true;
    for (int i = 0; i < n; i ++)
      if ((s[i] == '>' && a[i] <= a[i + 1]) || (s[i] == '<' && a[i] >= a[i + 1]))
      {
        printf("Wrong at %d %c\n", i, s[i]);
        valid = false;
      }
    printf("valid: %d\n", valid);
  }

  lli ans = 0;
  for (int i = 0; i <= n; i ++)
    ans += a[i];
  printf("%lld\n", ans);

  return 0;
}