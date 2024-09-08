#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxM = 2e5; int n, m;
struct Block
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
  bool operator<(const Block &other) const { return j < other.j; }
};
Block blocks[maxM];
vector<lli> eachRow[2];

string puzzle[2], compressedPuzzle[2]; int sz;
// kind = {==0: aligned, > 0: up in front, < 0: down in front}
/*
  With this delta I can know the up-j and down-j
*/
const int maxSz = 5*maxM, maxDelta = 7;
const int midDelta = maxDelta >> 1;
int memo[maxSz + 1][maxDelta];
int solve(int i = 0, int delta = 0)
{
  int above = i, down = i + delta;

  if (above > sz || down > sz) return false;
  if (above == sz && down == sz) return above == sz && down == sz;
  int &ans = memo[i][delta + midDelta];
  if (ans != -1) return ans;

  ans = false;
  // move with #
  if (above < sz && delta - 1 >= -midDelta && puzzle[0][above] == '#')
    ans = max(ans, solve(above + 1, delta - 1));
  if (down < sz && delta + 1 <= midDelta && puzzle[1][down] == '#')
    ans = max(ans, solve(above, delta + 1));

  // pipe
  if (delta == 0 && puzzle[0][i] == '.' && puzzle[1][i] == '.')
    ans = max(ans, solve(above + 1, 0));

  // up line
  if (delta - 2 >= -midDelta && above + 1 < sz && puzzle[0][above] == '.' && puzzle[0][above + 1] == '.')
    ans = max(ans, solve(above + 2, delta - 2));

  // down line
  if (delta + 2 <= midDelta && down + 1 < sz && puzzle[1][down] == '.' && puzzle[1][down + 1] == '.')
    ans = max(ans, solve(above, delta + 2));

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    eachRow[0].clear(), eachRow[1].clear();
    for (int i = 0; i < m; i++)
    {
      blocks[i].read();
      eachRow[blocks[i].i].push_back(blocks[i].j);
    }
    sort(blocks, blocks+m);

    for (int i = 0; i < 2; i++)
      sort(eachRow[i].begin(), eachRow[i].end());

    puzzle[0].clear(), puzzle[1].clear();
    bool can = true;
    /*
      There's a problem with this compression:
        You also need to compress the multiple ##
        It should be easy, but you need to the that before
    */
    for (int i = 0; i <= m; i++)
    {
      if (i == m)
      {
        int dist = n - blocks[i - 1].j - 1;
        if (dist == 0)
          ;
        else if (dist == 1)
          puzzle[0] += ".";
        else if (dist & 1)
          puzzle[0] += "...";
        else
          puzzle[0] += "..";
      }
      else if (i == 0)
      {
        if (blocks[i].j == 0)
          puzzle[blocks[i].i] += "#";
        else if (blocks[i].j == 1)
          puzzle[blocks[i].i] += ".#";
        else if (blocks[i].j & 1)
          puzzle[blocks[i].i] += "...#";
        else
          puzzle[blocks[i].i] += "..#";
      }
      else
      {
        int dist = blocks[i].j - blocks[i - 1].j;
        if (dist == 1)
          puzzle[blocks[i].i] += "#";
        else if (dist == 2)
          puzzle[blocks[i].i] += ".#";
        else if (dist & 1)
          puzzle[blocks[i].i] += "..#";
        else
          puzzle[blocks[i].i] += "...#";
      }

      int a = i == m ? 0 : blocks[i].i;
      if (puzzle[a].size() < puzzle[!a].size())
        a = !a;
      while (puzzle[!a].size() < puzzle[a].size())
        puzzle[!a] += ".";

      if (i + 1 < m && blocks[i + 1].j == blocks[i].j)
      {
        puzzle[!a][puzzle[!a].size() - 1] = '#';
        i++;
      }
    }

    compressedPuzzle[0].clear(), compressedPuzzle[1].clear();
    for (int i = 0; i < puzzle[0].size(); i++)
    {
      bool compressed = false;
      for (int a = 0; a < 2; a++)
        if (puzzle[a][i] == '#' && puzzle[!a][i] == '.')
        {
          int j = i;
          while (j + 1 < puzzle[0].size() && puzzle[a][j + 1] == '#' && puzzle[!a][j + 1] == '.')
            j++;
          int dist = j - i + 1;
          if (dist > 2)
          {
            if (dist & 1) compressedPuzzle[a] += "###", compressedPuzzle[!a] += "...";
            else compressedPuzzle[a] += "##", compressedPuzzle[!a] += "..";
            compressed = true;
            i = j;
            break;
          }
        }

      if (!compressed)
        for (int a = 0; a < 2; a++)
          if (puzzle[a][i] == '#' && puzzle[!a][i] == '#')
          {
            int j = i;
            while (j + 1 < puzzle[0].size() && puzzle[a][j + 1] == '#' && puzzle[!a][j + 1] == '#')
              j++;
            int dist = j - i + 1;
            if (dist > 2)
            {
              if (dist & 1) compressedPuzzle[a] += "###", compressedPuzzle[!a] += "###";
              else compressedPuzzle[a] += "##", compressedPuzzle[!a] += "##";
              compressed = true;
              i = j;
              break;
            }
          }

      if (!compressed)
        for (int a = 0; a < 2; a++)
          compressedPuzzle[a] += puzzle[a][i];
    }
    for (int a = 0; a < 2; a++)
      puzzle[a] = compressedPuzzle[a];
    sz = puzzle[0].size();

    // puzzle[0].clear();
    // puzzle[1].clear();
    // for (int i = 0; i < n; i++)
    //   puzzle[0] += '.', puzzle[1] += '.';
    // for (int i = 0; i < m; i++)
    //   puzzle[blocks[i].i][blocks[i].j] = '#';
    // sz = puzzle[0].size();

    DEBUG {
      printf("------------- %d\n", sz);
      for (int i = 0; i < 2; i++)
        printf("%s\n", puzzle[i].c_str());
    }

    for (int i = 0; i <= sz; i++)
      for (int a = 0; a < maxDelta; a++)
        memo[i][a] = -1;
    int ans = solve();
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}