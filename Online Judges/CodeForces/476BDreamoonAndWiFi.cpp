#include <bits/stdc++.h>

int canReach(int toReach, int qMark)
{
  if (qMark == 0) return(toReach == 0);
  return(canReach(toReach - 1, qMark - 1) + canReach(toReach + 1, qMark - 1));
}

int main()
{
  char s1[11], s2[11]; scanf("%s\n%s", s1, s2);
  int qMark = 0; for (int i = 0; s2[i]; i ++) qMark += s2[i] == '?';
  double total = pow(2, qMark);
  int ending = 0;
  for (int i = 0; s1[i]; i ++) ending += s1[i] == '+' ? 1 : -1;
  int at = 0;
  for (int i = 0; s2[i]; i ++) if (s2[i] != '?') at += s2[i] == '+' ? 1 : -1;

  if (abs(ending - at) > qMark) printf("0.000000000000\n");
  else if (qMark == 0 && ending == at) printf("1.000000000000\n");
  else printf("%.12lf\n", canReach(abs(ending - at), qMark) / total);

  return(0);
}
