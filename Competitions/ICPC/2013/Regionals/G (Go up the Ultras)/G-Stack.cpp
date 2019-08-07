#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
int h[maxN], prominence[maxN];
struct Peek { int highest, lowest; };
stack<Peek> stk;

void process(int i)
{
  while (!stk.empty() && h[i] >= stk.top().highest)
  {
    int lowest = stk.top().lowest; stk.pop();
    if (!stk.empty())
      stk.top().lowest = min(stk.top().lowest, lowest);
  }
  if (!stk.empty())
    prominence[i] = min(prominence[i], h[i] - stk.top().lowest);
  stk.push({h[i], h[i]});
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    while (!stk.empty()) stk.pop();
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &h[i]);
      prominence[i] = h[i];
    }

    for (int i = 0; i < n; i ++) process(i);
    while (!stk.empty()) stk.pop();
    for (int i = n - 1; i >= 0; i --) process(i);

    for (int i = 0, done = 0; i < n; i ++)
      if (prominence[i] >= 150000)
      {
        if (done ++) printf(" ");
        printf("%d", i + 1);
      }
    printf("\n");
  }
  return(0);
}