#include <bits/stcd++.h>
using namespace std;
#define lli long long int

class Solution
{
public:
  int numTriplets(vector<int> &nums1, vector<int> &nums2)
  {
    vector<vector<int>> nums = {nums1, nums2};
    map<lli, int> cnt[2];
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < nums[i].size(); j++)
        for (int k = j + 1; k < nums[i].size(); k++)
        {
          lli res = (lli)nums[i][j] * nums[i][k];
          if (!cnt[i].count(res))
            cnt[i][res] = 0;
          cnt[i][res]++;
        }

    lli ans = 0;
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < nums[i].size(); j++)
        ans += cnt[1 - i][(lli)nums[i][j] * nums[i][j]];
    return ans;
  }
};