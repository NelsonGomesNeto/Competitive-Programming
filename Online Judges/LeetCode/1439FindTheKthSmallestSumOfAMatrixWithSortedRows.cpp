#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40;

struct Node
{
  int sum; vector<int> cols;
  bool operator<(const Node &other) const
  {
    return sum > other.sum;
  }
};

int kthSmallest(vector<vector<int>>& mat, int k)
{
  int n = mat.size(), m = mat[0].size();
  set<vector<int>> done;
  priority_queue<Node> pq;
  Node source = Node{0, vector<int>(n, 0)};
  for (int i = 0; i < n; i++) source.sum += mat[i][0];
  pq.push(source);

  while (!pq.empty())
  {
    Node u = pq.top(); pq.pop();
    if (done.count(u.cols)) continue;
    if (--k == 0) return u.sum;
    done.insert(u.cols);

    for (int i = 0; i < n; i++)
      if (u.cols[i] + 1 < m)
      {
        u.sum -= mat[i][u.cols[i]++];
        u.sum += mat[i][u.cols[i]];
        pq.push(u);
        u.sum -= mat[i][u.cols[i]--];
        u.sum += mat[i][u.cols[i]];
      }
  }
  return -1;
}

int main()
{
  int n, m, k;
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        scanf("%d", &mat[i][j]);
    printf("%d\n", kthSmallest(mat, k));
  }
  return 0;
}