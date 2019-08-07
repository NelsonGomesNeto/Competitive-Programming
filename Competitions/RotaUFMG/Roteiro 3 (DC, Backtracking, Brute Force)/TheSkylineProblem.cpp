#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

void printAns(int ans[], int last)
{
  DEBUG for (int i = 1; i <= last; i ++)
    printf("%d%c", ans[i], i < last ? ' ' : '\n');
  int i = 1, k = 0, prev;
  while (!k)
  {
    if (i == last) k = 1;
    printf("%s%d %d", i > 1 ? " " : "\0", i, ans[i]);
    prev = ans[i];
    while (i < last && ans[i] == prev) i ++;
  }
  printf("\n");
}

int main()
{
  int triple[(int) 1e4][3], t = 0;
  while (scanf("%d %d %d", &triple[t][0], &triple[t][1], &triple[t][2]) != EOF) t ++;

  int ans[(int) 1e4 + 1], last = 0; memset(ans, 0, sizeof(ans));
  for (int i = 0; i < t; i ++)
  {
    for (int j = triple[i][0]; j < triple[i][2]; j ++)
      ans[j] = max(ans[j], triple[i][1]);
    last = max(last, triple[i][2]);
  }

  printAns(ans, last);

  return(0);
}