#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
#define Mat vector<vector<lli>>
using namespace std;

/*
rotate(a) = {{cos(a), -sin(a), 0, 0},
             {sin(a),  cos(a), 0, 0}
             {     0,       0, 1, 0}
             {     0,       0, 0, 1}}
translate(dx, dy) = {{ 1, 0, 0, dx},
                     { 0, 1, 0, dy}
                     { 0, 0, 1,  0}
                     { 0, 0, 0,  1}}

cos(pi/2) = 0
sin(pi/2) = 1

cos(-pi/2) = 0
sin(-pi/2) = -1

cos(pi) = -1
sin(pi) = 0
*/

const int maxN = 2e5 + 1; int n, m, q;
struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  Mat getVector()
  {
    return {{x},
            {y},
            {1}};
  }
};
Point points[maxN];
Mat after[maxN];

Mat matMult(Mat &a, Mat &b)
{
  Mat ans(a.size(), vector<lli>(b[0].size(), 0LL));
  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < b[0].size(); j++)
      for (int k = 0; k < a[0].size(); k++)
        ans[i][j] += a[i][k] * b[k][j];
  return ans;
}

int main()
{
  while (~scanf("%d", &n))
  {
    after[0] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    for (int i = 0; i < n; i++)
      points[i].read();

    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
      int op; scanf("%d", &op);
      Mat opMat;
      if (op >= 3)
      {
        lli p; scanf("%lld", &p);
        DEBUG printf("\ttranslating %d %lld\n", op, p);
        Mat rotate3 = {{-1,  0, 2*p},
                       { 0,  1,   0},
                       { 0,  0,   1}};
        Mat rotate4 = {{ 1,  0,   0},
                       { 0, -1, 2*p},
                       { 0,  0,   1}};
        opMat = op == 3 ? rotate3 : rotate4;
      }
      else
      {
        DEBUG printf("\trotating %d\n", op);
        Mat rotate1 = {{ 0, 1, 0},
                       {-1, 0, 0},
                       { 0, 0, 1}};
        Mat rotate2 = {{0, -1, 0},
                       {1,  0, 0},
                       {0,  0, 1}};
        opMat = op == 1 ? rotate1 : rotate2;
      }
      after[i] = matMult(opMat, after[i - 1]);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
      int a, b; scanf("%d %d", &a, &b); b--;
      Mat curr = points[b].getVector();
      Mat ans = matMult(after[a], curr);
      printf("%lld %lld\n", ans[0][0], ans[1][0]);
    }
  }
  return 0;
}