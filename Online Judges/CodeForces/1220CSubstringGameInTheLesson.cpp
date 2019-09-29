#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 5e5; int n;
char s[maxN + 1];
int minPos[256];

bool noLess(char at, int i)
{
  for (char j = 'a'; j < at; j ++)
    if (minPos[j] < i)
      return false;
  return true;
}

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar(); n = strlen(s);
    for (int i = 0; i < 256; i ++) minPos[i] = n;
    for (int i = n - 1; i >= 0; i --) minPos[s[i]] = i;

    for (int i = 0; i < n; i ++)
    {
      if (s[i] == 'a' || noLess(s[i], i))
        printf("Mike\n");
      else
        printf("Ann\n");
    }
  }
  return(0);
}
