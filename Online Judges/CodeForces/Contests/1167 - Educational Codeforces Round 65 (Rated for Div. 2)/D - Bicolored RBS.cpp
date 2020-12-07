#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  The idea is very simple: You just need to keep an int to store the current
  open parenthesis, if it's even: ans[i] = '0', if it's odd: ans[i] = '1'.
  Think about it, you will be evenly distributing the nested depths.
  The if order isn't obvious at first, but look at my code.
*/

const int maxN = 2e5; int n;
char s[maxN + 1], ans[maxN + 1];

int main()
{
  scanf("%d", &n);
  scanf(" %s", s);

  int op = 0;
  for (int i = 0; i < n; i ++)
  {
    if (s[i] == ')') op --;
    ans[i] = '0' + (op & 1);
    if (s[i] == '(') op ++;
  }
  printf("%s\n", ans);

  return(0);
}