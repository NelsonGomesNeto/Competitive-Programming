#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    char str[n + 1]; scanf(" %s", str);
    int s = 0, op = 0, cl = 0;
    bool can = true;
    for (int i = 0; i < n; i ++)
    {
      if (str[i] == '(') s ++, op ++;
      if (str[i] == ')') s --, cl ++;
      if (s < -1) can = false;
    }
    if (s > 1) can = false;
    if (op != cl) can = false;
    printf("%s\n", can ? "Yes" : "No");
  }
  return(0);
}
