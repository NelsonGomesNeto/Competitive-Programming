#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int kadane(vector<int> &arr)
{
  int ans = -1e9, sum = 0;
  for (int i = 0; i < arr.size(); i++)
  {
    ans = max(ans, arr[i]);
    sum += arr[i];
    if (sum < 0) sum = 0;
    else ans = max(ans, sum);
  }
  return ans;
}
int maxSubarraySumCircular2(vector<int> &arr) {
  int ans = kadane(arr), total = 0, minValue = -1e9;
  for (int i = 0; i < arr.size(); i++)
  {
    total += arr[i];
    minValue = max(minValue, arr[i]);
    arr[i] *= -1;
  }
  ans = max(ans, total + kadane(arr));
  if (minValue <= 0) ans = minValue;

  return ans;
}

int maxSubarraySumCircular(vector<int> &arr)
{
  int n = arr.size(), ans = -1e9;
  for (int i = 0; i < n; i++) ans = max(ans, arr[i]);

  int sum = 0, removed = 0;
  deque<pair<int, int>> curr;
  multiset<int> sums;
  map<int, int> posSum;
  for (int i = 0; i < 2*n; i++)
  {
    sum += arr[i % n];
    curr.push_back({arr[i % n], i});
    if (curr.size() == n + 1)
    {
      sum -= curr.front().first, removed += curr.front().first;
      sums.erase(posSum[curr.front().second]);
      curr.pop_front();
    }
    sums.insert(sum), posSum[i] = sum;

    if (sum <= 0) curr.clear(), sums.clear(), posSum.clear(), sum = 0;
    while (!curr.empty() && (curr.front().first <= 0 || *sums.begin() - removed <= 0))
    {
      sum -= curr.front().first, removed += curr.front().first;
      sums.erase(posSum[curr.front().second]);
      curr.pop_front();
      if (!curr.empty()) ans = max(ans, sum);
    }
    DEBUG printf("%d (%d) %d %d | %d\n", i, arr[i % n], sum, *sums.begin(), (int)curr.size());
    if (!curr.empty()) ans = max(ans, sum);
  }
  return ans;
}

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    printf("%d\n", maxSubarraySumCircular(arr));
  }

  return 0;
}