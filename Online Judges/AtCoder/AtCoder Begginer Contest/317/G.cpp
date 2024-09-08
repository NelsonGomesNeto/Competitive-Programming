#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
source (0) -[1]> column -[1]> numbers of each column -[m]> general numbers -[1]> row
*/

const int maxN = 100, maxRep = 1000;
int n, m;
int mat[maxN][maxN];
int cnt[maxN][maxN];
bool has[maxN][maxN];
vector<pair<pair<int, int>, vector<int>>> lol;

void print_mat() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      printf("%d%c", mat[i][j] + 1, j + 1 < m ? ' ' : '\n');
}

int main()
{
  while (~scanf("%d %d", &n, &m)) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        scanf("%d", &mat[i][j]);
        --mat[i][j];
      }
    lol.clear();
    for (int i = 0; i < n; ++i) {
      set<int> hehe;
      vector<int> row;
      int equal = 0;
      for (int j = 0; j < m; ++j) {
        if (hehe.count(mat[i][j]))
          ++equal;
        hehe.insert(mat[i][j]);
        row.push_back(mat[i][j]);
      }
      lol.emplace_back(make_pair(equal, i), row);
    }
    sort(lol.begin(), lol.end());

    bool possible;
    int rep = 0;
    do {
      memset(cnt, 0, sizeof(cnt));
      memset(has, false, sizeof(has));
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
          mat[i][j] = lol[i].second[j];
          ++cnt[i][mat[i][j]];
        }
      for (int j = 0; j < m; ++j)
        has[j][mat[0][j]] = true;

      possible = true;
      for (int i = 1; i < n; ++i)
      {
        for (int j = 0; j < m; ++j)
        {
          bool added = false;
          for (int a = 0; a < n; ++a)
          {
            if (!has[j][a] && cnt[i][a] > 0)
            {
              has[j][a] = true, --cnt[i][a];
              mat[i][j] = a;
              DEBUG printf("add %d at column %d row %d\n", a + 1, j, i);
              added = true;
              break;
            }
          }
          possible &= added;
        }
      }
      ++rep;
    } while (!possible && next_permutation(lol.begin(), lol.end()) && rep < maxRep);

    if (possible) {
      printf("Yes\n");
      print_mat();
    } else {
      printf("No\n");
    }
  }
  return 0;
}
