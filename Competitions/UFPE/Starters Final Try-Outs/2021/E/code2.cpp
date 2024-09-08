#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const double eps = 1e-9;

lli kadane(vector<lli> &arr)
{
  lli max_so_far = 0, max_ending_here = 0;
  for (int i = 0; i < arr.size(); i++)
  {
    max_ending_here = max_ending_here + arr[i];
    max_ending_here = max(max_ending_here, 0ll);
    max_so_far = max(max_so_far, max_ending_here);
  }
  return max_so_far;
}
lli maxSubarraySumCircular(vector<lli> &arr)
{
  for (int i = 0; i < arr.size(); i++)
    arr[i] = -arr[i];
  lli neg_max_sum = kadane(arr);
  for (int i = 0; i < arr.size(); i++)
    arr[i] = -arr[i];
  lli opt1 = accumulate(arr.begin(), arr.end(), 0) + neg_max_sum;
  return max(kadane(arr), opt1);
}

const int maxN = 1e5; int n;
struct Point
{
  lli x, y, a, s, value, lolvalue; double angle; int idx;
  void read()
  {
    scanf("%lld %lld %lld %lld", &x, &y, &a, &s);
    value = a - s;
    // lolvalue = s - a;
    angle = atan2(y, x);
  }
  bool operator<(const Point &other) const
  {
    return angle < other.angle;
  }
  bool sameLine(const Point &other)
  {
    // return abs(angle - other.angle) <= eps;
    // if (x == other.x) return true;
    // if (y == other.y) return true;
    return y * other.x == other.y * x;
  }
};
vector<Point> points;

int main()
{
  while (~scanf("%d", &n))
  {
    points.clear(); points.resize(n);
    lli lol = 0;
    for (int i = 0; i < n; i++)
    {
      points[i].read();
      points[i].idx = i;
    }
    sort(points.begin(), points.end());

    // assert(!points[0].sameLine(points[n - 1]));

    int start = n - 1;
    while (start - 1 >= 0 && points[start].sameLine(points[start - 1]))
      start--;

    vector<Point> aux = points;
    for (int i = 0; i < n; i++)
      points[i] = aux[(start + i) % n];

    vector<lli> values;
    for (int i = 0; i < n; i++)
    {
      int j = i;
      lli total = points[i].value;
      while (j + 1 < n && points[i].sameLine(points[j + 1]))
      {
        total += points[j].value;
        j++;
      }

      values.push_back(total);
      i = j;
    }
    lli ans = maxSubarraySumCircular(values);

    printf("%lld\n", ans);
  }
  return 0;
}