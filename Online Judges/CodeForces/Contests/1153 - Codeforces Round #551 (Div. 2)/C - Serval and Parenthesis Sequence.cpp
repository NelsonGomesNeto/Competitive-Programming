#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e5; int n;
char s[maxN + 1]; int sSize;

int main()
{
  scanf("%d", &n);
  scanf(" %s", s); sSize = strlen(s);
  int missing = 0, op = 0, cl = 0;
  for (int i = 0; s[i]; i ++) missing += s[i] == '?', op += s[i] == '(', cl += s[i] == ')';
  if (s[0] == ')' || (s[0] == '(' && s[1] == ')') || sSize & 1) printf(":(\n");
  else
  {
    int toBalance = abs(op - cl);
    int rest = missing - toBalance;
    if (rest < 0 || rest & 1) printf(":(\n");
    else
    {
      if (op < cl)
      {
        for (int i = 0, a = toBalance; s[i] && a; i ++) if (s[i] == '?') s[i] = '(', a --;
      }
      else
      {
        for (int i = sSize - 1, a = toBalance; i >= 0 && a; i --) if (s[i] == '?') s[i] = ')', a --;
      }
      for (int i = 0, a = rest >> 1; s[i] && a; i ++) if (s[i] == '?') s[i] = '(', a --;
      for (int i = 0, a = rest >> 1; s[i] && a; i ++) if (s[i] == '?') s[i] = ')', a --;

      bool valid = true; int op = 0;
      for (int i = 0; s[i]; i ++)
      {
        op += s[i] == '(' ? 1 : -1;
        if (i < sSize - 1 && op <= 0) valid = false;
      }
      if (op != 0) valid = false;

      if (!valid) printf(":(\n");
      else printf("%s\n", s);
    }
  }
  return(0);
}