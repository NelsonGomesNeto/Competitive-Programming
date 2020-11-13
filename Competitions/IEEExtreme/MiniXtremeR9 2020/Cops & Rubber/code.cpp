#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); }
  void print(char sep) { printf("%d %d%c", i, j, sep); }
  bool invalid() { return i < 0 || j < 0 || i >= 20 || j >= 20; }
  Pos operator+(const Pos &other)
  {
    return Pos{i + other.i, j + other.j};
  }
  bool operator==(const Pos &other)
  {
    return i == other.i && j == other.j;
  }
  int dist(Pos other)
  {
    return abs(i - other.i) + abs(j - other.j);
  }
  // double dist(Pos &other)
  // {
  //   return sqrt((i - other.i)*(i - other.i) + (j - other.i)*(j - other.j));
  // }
};
char op; Pos robot, polices[3];
// Assuming everybody can stay still
int di[9] = { 0, 1, 0,  0, -1, 1,  1, -1, -1};
int dj[9] = { 0, 0, 1, -1,  0, 1, -1,  1, -1};

struct RobotMovement
{
  int found; double distanceSum; int k;
  bool operator<(const RobotMovement &other) const
  {
    return found < other.found || (found == other.found && distanceSum > other.distanceSum);
  }
};
void tryAllRobot()
{
  vector<RobotMovement> movements;
  for (int k = 0; k < 9; k++)
  {
    if (k >= 1 && k <= 4) continue;
    Pos robotNewPos = robot + Pos{di[k], dj[k]};
    if (robotNewPos.invalid()) continue;
    RobotMovement rm = RobotMovement{0, 0, k};
    for (int i = 0; i < 3; i++)
      for (int d = 0; d < 5; d++)
      {
        Pos aux = polices[i] + Pos{di[d], dj[d]};
        if (aux.invalid()) continue;
        rm.found += robotNewPos == aux;
        rm.distanceSum += robotNewPos.dist(aux);
      }
    rm.distanceSum -= pow(robotNewPos.dist(Pos{10, 10}), 4);
    movements.push_back(rm);
  }
  sort(movements.begin(), movements.end());
  if (movements[0].found)
    for (int k = 1; k <= 4; k++)
    {
      if (k >= 1 && k <= 4) continue;
      Pos robotNewPos = robot + Pos{di[k], dj[k]};
      if (robotNewPos.invalid()) continue;
      RobotMovement rm = RobotMovement{0, 0, k};
      for (int i = 0; i < 3; i++)
        for (int d = 0; d < 5; d++)
        {
          Pos aux = polices[i] + Pos{di[d], dj[d]};
          if (aux.invalid()) continue;
          rm.found += robotNewPos == aux;
          rm.distanceSum += robotNewPos.dist(aux);
        }
      rm.distanceSum -= pow(robotNewPos.dist(Pos{10, 10}), 4);
      movements.push_back(rm);
    }
  sort(movements.begin(), movements.end());
  robot = robot + Pos{di[movements[0].k], dj[movements[0].k]};
  robot.print('\n');
}

// Andar em trio
struct PoliceMovement
{
  int found; double distanceSum; int a[3];
  bool operator<(const PoliceMovement &other) const
  {
    return found > other.found || (found == other.found && distanceSum < other.distanceSum);
  }
};
vector<PoliceMovement> policeMovements;
void fillPoliceMovements(int p = 0, PoliceMovement curr = PoliceMovement{0, 0, 0, 0, 0})
{
  if (p == 3)
  {
    curr.found = curr.distanceSum = 0;
    for (int k = 0; k < 9; k++)
    {
      Pos robotNewPos = robot + Pos{di[k], dj[k]};
      if (robotNewPos.invalid()) continue;
      bool found = false;
      for (int i = 0; i < 3; i++)
      {
        if (robotNewPos == polices[i])
          found = true;
        curr.distanceSum += robotNewPos.dist(polices[i]);
      }
      curr.found += found;
    }
    policeMovements.push_back(curr);
    return;
  }

  Pos aux = polices[p];
  for (int d = 0; d < 5; d++)
  {
    polices[p] = aux + Pos{di[d], dj[d]};
    if (polices[p].invalid()) continue;
    curr.a[p] = d;
    fillPoliceMovements(p + 1, curr);
  }
  polices[p] = aux;
}

void tryAllPolices()
{
  policeMovements.clear();

  fillPoliceMovements();

  sort(policeMovements.begin(), policeMovements.end());
  for (int i = 0; i < 3; i++)
    polices[i] = polices[i] + Pos{di[policeMovements[0].a[i]], dj[policeMovements[0].a[i]]};
  for (int i = 0; i < 3; i++)
    polices[i].print(i == 2 ? '\n' : ' ');
}

int main()
{
  while (scanf(" %c", &op) != EOF)
  {
    robot.read();
    for (int i = 0; i < 3; i++) polices[i].read();

    if (op == 'R') tryAllRobot();
    else tryAllPolices();
  }
  return 0;
}