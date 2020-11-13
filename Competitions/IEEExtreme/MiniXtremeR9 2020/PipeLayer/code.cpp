#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
int n, m;
struct Pos
{
  int i, j;
  bool operator<(const Pos &other) const
  {
    return i < other.i || (i == other.i && j < other.i);
  }
  bool operator==(const Pos &other) const
  {
    return i == other.i && j == other.j;
  }
  Pos operator+(const Pos &other)
  {
    return Pos{i + other.i, j + other.j};
  }
  bool valid()
  {
    return i >= 0 && j >= 0 && i < n && j < m;
  }
  void print() { printf("%d %d\n", i, j); }
};
struct Movement
{
  Pos pos, firstNeeded; int dist;
};
vector<Movement> movements;
int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
Movement findDist(Pos origin, Pos destination, vector<string> &board)
{
  queue<Movement> q; q.push({origin, {0, 0}, 0});
  Pos any = origin;
  while (!q.empty())
  {
    Movement u = q.front(); q.pop();
    if (u.pos == destination)
      return u;
    for (int k = 0; k < 4; k++)
    {
      Pos middle = u.pos + Pos{di[k], dj[k]};
      Pos newPos = u.pos + Pos{2*di[k], 2*dj[k]};
      if (!middle.valid()) continue;
      if ((k == 0 || k == 1) && board[middle.i][middle.j] == '|') continue;
      if ((k == 2 || k == 3) && board[middle.i][middle.j] == '-') continue;
      int newDist = u.dist + (board[middle.i][middle.j] == '.');
      any = middle;
      q.push({newPos, (board[middle.i][middle.j] == '.') ? middle : u.firstNeeded, newDist});
    }
  }
  return Movement{origin, any, inf};
}

void nextMove(char player, vector <string> board)
{
  n = board.size(), m = board[0].size();

  bool empty = true;
  for (int i = 0; i < board.size(); i++)
    for (int j = 0; j < board[0].size(); j++)
      if ((player == 'b' && board[i][j] == '|')
        || (player == 'r' && board[i][j] == '-'))
        empty = false;
  if (empty)
  {
    if (player == 'r') printf("1 1\n");
    else printf("11 11\n");
  }
  else
  {
    if (player == 'b')
    {
      Movement best = {{0, 0}, {0, 0}, inf};
      for (int j = 1; j < m; j += 2)
        for (int jj = 1; jj < m; jj += 2)
        {
          Movement d = findDist(Pos{0, j}, Pos{12, jj}, board);
          if (d.dist < inf)
          {
            char aux = board[d.firstNeeded.i][d.firstNeeded.j];
            Movement opbest = {{0, 0}, {0, 0}, inf};
            for (int i = 1, ii = 1; i <= 1; i += 2)
              // for (int ii = 1; ii < n; ii += 2)
              {
                Movement opd = findDist(Pos{i, 0}, Pos{ii, 12}, board);
                if (opd.dist < opbest.dist)
                  opbest = opd;
              }
            board[d.firstNeeded.i][d.firstNeeded.j] = aux;
            d.dist -= opbest.dist / 2;
          }
          if (d.dist < best.dist)
            best = d;
        }
      best.firstNeeded.print();
    }
    else
    {
      Movement best = {{0, 0}, {0, 0}, inf};
      for (int i = 1; i < n; i += 2)
        for (int ii = 1; ii < n; ii += 2)
        {
          Movement d = findDist(Pos{i, 0}, Pos{ii, 12}, board);
          if (d.dist < inf)
          {
            char aux = board[d.firstNeeded.i][d.firstNeeded.j];
            Movement opbest = {{0, 0}, {0, 0}, inf};
            for (int j = 1, jj = 1; j <= 1; j += 2)
              // for (int jj = 1; jj < m; jj += 2)
              {
                Movement opd = findDist(Pos{0, j}, Pos{12, jj}, board);
                if (opd.dist < opbest.dist)
                  opbest = opd;
              }
            board[d.firstNeeded.i][d.firstNeeded.j] = aux;
            d.dist -= opbest.dist / 2;
          }
          if (d.dist < best.dist)
            best = d;
        }
      best.firstNeeded.print();
    }
  }
}

int main(void) {

    char player;
    vector <string> board;

    cin >> player;

    for(int i=0; i<13; i++) {
        string s; cin >> s;
        board.push_back(s);
    }
  
    nextMove(player,board);

    return 0;
}
