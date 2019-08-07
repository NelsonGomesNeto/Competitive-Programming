#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  char p[n]; int fTicket = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf(" %c", &p[i]);
    if (p[i] == 'd')
      fTicket ++;
  }
  if (fTicket >= 20)
    printf("%d\n", -1);
  else
  {
    int last = 0;
    for (int i = 0; i < n && fTicket < 20; i ++)
    {
      if (p[i] == 'd') continue;
      last = i;
      fTicket ++;
    }
    printf("%d\n", last);
  }

  return(0);
}
