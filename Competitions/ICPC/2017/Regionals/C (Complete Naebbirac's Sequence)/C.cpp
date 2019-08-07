#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int k, n; scanf("%d %d", &k, &n);
  int freq[k + 1]; memset(freq, 0, sizeof(freq));
  for (int i = 0, s; i < n; i ++)
  {
    scanf("%d", &s);
    freq[s] ++;
  }
  vector<pair<int, int>> frequency;
  for (int i = 1; i <= k; i ++) frequency.push_back({freq[i], i});
  sort(frequency.begin(), frequency.end());

  DEBUG for (int i = 0; i < k; i ++)
    printf("%d %d\n", frequency[i].first, frequency[i].second);

  int add, rem; add = rem = -1;
  if (frequency[0].first + 2 == frequency[k - 1].first)
    frequency[0].first ++, frequency[k - 1].first --, add = frequency[0].second, rem = frequency[k - 1].second;
  else if (frequency[0].first == frequency[1].first)
    frequency[k - 1].first --, rem = frequency[k - 1].second;
  else if (frequency[k - 1].first == frequency[k - 2].first)
    frequency[0].first ++, add = frequency[0].second;
  sort(frequency.begin(), frequency.end());
  if (frequency[0].first != frequency[k - 1].first) printf("*\n");
  else
  {
    if (add == -1) printf("-%d\n", rem);
    else if (rem == -1) printf("+%d\n", add);
    else printf("-%d +%d\n", rem, add);
  }
  return(0);
}
