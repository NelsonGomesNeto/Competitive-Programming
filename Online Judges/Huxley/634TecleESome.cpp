#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli s; int d;
vector<deque<string>> ans;
deque<string> a;
bool visited[10];
string digitString[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
vector<int> reachable[10] = {
  {7, 8, 9}, // 0
  {2, 4, 5}, // 1
  {1, 3, 4, 5, 6}, // 2
  {2, 5, 6}, // 3
  {1, 2, 5, 7, 8}, // 4
  {1, 2, 3, 4, 6, 7, 8, 9}, // 5
  {2, 3, 5, 8, 9}, // 6
  {0, 4, 5, 8}, // 7
  {0, 4, 5, 6, 7, 9}, // 8
  {0, 5, 6, 8} // 9
};

void bruteForce(int u, int amount, string currentString, lli currentNumber, lli currentSum, deque<string> &current)
{
  if (u == -1)
  {
    if (currentSum == s) ans.push_back(current);
    return;
  }

  visited[u] = true;

  if (amount < d)
    for (int v: reachable[u])
      if (!visited[v])
        bruteForce(v, amount + 1, currentString + digitString[v], currentNumber*10 + v, currentSum, current);

  current.push_back(currentString);
  bruteForce(-1, 0, "", 0, currentSum + currentNumber, current);

  if (amount == d)
    for (int v: reachable[u])
      if (!visited[v])
        bruteForce(v, 1, digitString[v], v, currentSum + currentNumber, current);

  current.pop_back();

  visited[u] = false;
}

int main()
{
  int t = 1;
  while (scanf("%lld %d", &s, &d) && !(s == -1 && d == -1))
  {
    ans.clear();
    for (int i = 0; i < 10; i ++)
    {
      a.clear(), memset(visited, false, sizeof(visited));
      bruteForce(i, 1, digitString[i], i, 0, a);
    }
    printf("#%d\n", t ++);
    if (ans.empty()) printf("impossivel\n");
    else
      for (int i = 0; i < ans.size(); i ++)
        for (int j = 0; j < ans[i].size(); j ++)
          printf("%s%c", ans[i][j].c_str(), j < ans[i].size() - 1 ? ' ' : '\n');
  }
  return(0);
}
