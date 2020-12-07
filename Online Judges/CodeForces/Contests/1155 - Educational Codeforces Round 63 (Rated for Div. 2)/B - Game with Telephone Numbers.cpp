#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  char s[n + 1]; scanf(" %s", s);
  int moves = (n - 11) >> 1;
  for (int i = 0; i < n && moves; i ++)
    if (s[i] == '8')
      s[i] = 'a', moves --;
  moves = (n - 11) >> 1;
  for (int i = 0; i < n && moves; i ++)
    if (s[i] != '8' && s[i] != 'a')
      s[i] = 'a', moves --;
  bool isEight;
  for (int i = 0; i < n; i ++)
  {
    if (s[i] == 'a') continue;
    isEight = s[i] == '8';
    break;
  }
  printf("%s\n", isEight ? "YES" : "NO");
  return(0);
}