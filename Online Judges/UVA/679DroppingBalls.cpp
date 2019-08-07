#include <bits/stdc++.h>
using namespace std;

bool nodes[(1 << 20) + 1]; int maxDepth;
int dp[21][1 << 19];

void printSpacing(int spaces) { while (spaces --) printf("   "); }
void printTree(int u, int depth)
{
  if (depth == maxDepth) return;
  printTree(2*u, depth + 1);
  printSpacing(depth); printf("%d\n", u);
  printTree(2*u + 1, depth + 1);
}

int reaches(int u, int depth)
{
  if (depth == 1) return(u);
  nodes[u] = !nodes[u];
  return(reaches(2*u + !nodes[u], depth - 1));
}

int main()
{
  for (int i = 1; i <= 20; i ++)
  {
    memset(nodes, false, sizeof(nodes));
    for (int j = 0, end = 1 << (i - 1); j < end; j ++)
      dp[i][j] = reaches(1, i);
  }

  int t;
  while (scanf("%d", &t) && t != -1)
    while (t --)
    {
      int ith; scanf("%d %d", &maxDepth, &ith);
      printf("%d\n", dp[maxDepth][(ith - 1) % (1 << (maxDepth - 1))]);
    }
  return(0);
}