#include <bits/stdc++.h>
using namespace std;

unordered_map<deque<char>, int> activities[(int) 26e5];
int dp[(int) 26e5];

int main()
{
  int t, lastBig = 0; scanf("%d", &t);
  while (t --)
  {
    int n, k; scanf("%d %d", &n, &k); getchar();
    for (int i = 0; i < lastBig; i ++) activities[i].clear();
    deque<char> s; char aux; int sum = 0;
    for (int i = 0; i < k; i ++)
    {
      scanf("%c", &aux);
      s.push_back(aux); sum += aux - 'a';
    }
    activities[sum][s] = 1; lastBig = sum;

    int total = 1;
    for (int i = k; i < n; i ++)
    {
      sum -= s.front() - 'a'; s.pop_front();
      scanf("%c", &aux);
      sum += aux - 'a'; s.push_back(aux);
      int prevSize = activities[sum].size();
      activities[sum][s] = 1; lastBig = max(lastBig, sum);
      if (activities[sum].size() > prevSize) total ++;
    }

    printf("%d\n", total);
  }
  return(0);
}
