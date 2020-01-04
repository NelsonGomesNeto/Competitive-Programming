#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100 + 1; int ns, nt;
char s[maxN], t[maxN];
int tcnt[256], cnt[256];

bool valid()
{
  for (int i = 0; i < 256; i ++)
    if (tcnt[i] != cnt[i])
      return false;
  return true;
}

bool dfs(int u = 0)
{
  if (u >= ns) return false;
  cnt[s[u]] ++;
  if (valid())
    return true;
  if (dfs(2*u + 1))
    return true;
  if (dfs(2*u + 2))
    return true;
  cnt[s[u]] --;
  return false;
}

int main()
{
  while (scanf("%d", &ns) != EOF)
  {
    scanf(" %s", s);
    scanf("%d", &nt);
    scanf(" %s", t);
    memset(tcnt, 0, sizeof(tcnt));
    for (int i = 0; i < nt; i ++)
      tcnt[t[i]] ++;

    memset(cnt, 0, sizeof(cnt));
    printf("%s\n", dfs() ? "Sim" : "Nao");
  }
  return(0);
}