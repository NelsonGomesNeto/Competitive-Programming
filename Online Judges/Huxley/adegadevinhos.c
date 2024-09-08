#include <stdio.h>
#include <string.h>
#define memCard pd[start - 1][end - 1]
#define vendeComeco dp(pd, w, ano + 1, start + 1, end) + (w[start] * ano)
#define vendeFim dp(pd, w, ano + 1, start, end - 1) + (w[end] * ano)

int vinhos;

int max(int a, int b)
{
  return(a > b ? a : b);
}

int dp(int pd[][vinhos], int w[], int ano, int start, int end)
{
  if (ano == vinhos)
    return(w[start] * ano);

  if (memCard == -1)
    memCard = max(vendeComeco, vendeFim);
    
  return(memCard);
}

int main()
{
  while (scanf("%d", &vinhos) != EOF)
  {
    int v[vinhos + 1], DP[vinhos][vinhos], i;
    for (i = 1; i <= vinhos; i ++)
    {
      scanf("%d", &v[i]);
      memset(DP[i - 1], -1, vinhos * sizeof(int));
    }
    int ans = dp(DP, v, 1, 1, vinhos);
    printf("%d\n", ans);
  }
  return(0);
}
