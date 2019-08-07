#include <bits/stdc++.h>
using namespace std;
int n1, n2;
int size1[20], size2[20];
char strings1[20][41], strings2[20][41];

int matchBegin(char now1[], char now2[], int start)
{
  for (int i = start; now1[i] && now2[i]; i ++)
    if (now1[i] != now2[i]) return(0);
  return(1);
}

int solve(char now1[], char now2[], int s1, int s2)
{
  if (!matchBegin(now1, now2, 0)) return(0);
  if (s1 && s1 == s2 && !strcmp(now1, now2)) return(1);

  char aux[41];
  if (s1 <= s2)
    for (int i = 0; i < n1; i ++)
    {
      if (s1 + size1[i] > 40) continue;
      strcpy(aux, now1);
      strcat(now1, strings1[i]);
      if (solve(now1, now2, s1 + size1[i], s2)) return(1);
      strcpy(now1, aux);
    }
  else
    for (int i = 0; i < n2; i ++)
    {
      if (s2 + size2[i] > 40) continue;
      strcpy(aux, now2);
      strcat(now2, strings2[i]);
      if (solve(now1, now2, s1, s2 + size2[i]))
        return(1);
      strcpy(now2, aux);
    }

  return(0);
}

int main()
{
  while (scanf("%d %d", &n1, &n2) != EOF)
  {
    for (int i = 0; i < n1; i ++)
    {
      scanf("\n%s", strings1[i]);
      size1[i] = strlen(strings1[i]);
    }
    for (int i = 0; i < n2; i ++)
    {
      scanf("\n%s", strings2[i]);
      size2[i] = strlen(strings2[i]);
    }

    char now1[41] = "", now2[41] = "";
    int ans = solve(now1, now2, 0, 0);
    printf("%s\n", ans ? "S" : "N");
  }

  return(0);
}