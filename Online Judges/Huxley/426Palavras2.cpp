#include <bits/stdc++.h>
using namespace std;

const int maxN = 20, maxS = 40 + 1, maxRes = 20*40 + 1;
int n1, n2;
int size1[maxN], size2[maxN];
char strings1[maxN][maxS], strings2[maxN][maxS];
set<string> memo;

int matchBegin(char now1[], char now2[], int start)
{
  for (int i = start; now1[i] && now2[i]; i ++)
    if (now1[i] != now2[i])
      return(0);
  return(1);
}

string getDiff(char now1[], char now2[], int s1, int s2)
{
  string diff = s1 >= s2 ? "2" : "3";
  if (s1 >= s2)
    for (int i = s2; i < s1; i ++)
      diff += now1[i];
  else
    for (int i = s1; i < s2; i ++)
      diff += now2[i];
  return diff;
}

int solve(char now1[], char now2[], int s1, int s2)
{
  if (!matchBegin(now1, now2, 0)) return(0);
  if (s1 && s1 == s2) return(1);

  string diff = getDiff(now1, now2, s1, s2);
  if (memo.count(diff)) return 0;
  memo.insert(diff);

  if (s1 <= s2)
    for (int i = 0; i < n1; i ++)
    {
      if (s1 + size1[i] >= maxRes) continue;
      strcat(now1+s1, strings1[i]);
      if (solve(now1, now2, s1 + size1[i], s2))
        return(1);
      now1[s1] = '\0';
    }
  else
    for (int i = 0; i < n2; i ++)
    {
      if (s2 + size2[i] >= maxRes) continue;
      strcat(now2+s2, strings2[i]);
      if (solve(now1, now2, s1, s2 + size2[i]))
        return(1);
      now2[s2] = '\0';
    }

  return(0);
}

int main()
{
  while (scanf("%d %d", &n1, &n2) != EOF)
  {
    memo.clear();

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

    char now1[maxRes] = "", now2[maxRes] = "";
    int ans = solve(now1, now2, 0, 0);
    printf("%s\n", ans ? "S" : "N");
  }

  return(0);
}