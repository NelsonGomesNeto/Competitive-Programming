#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<lli> program;
void read()
{
  program.clear();
  lli opcode; char end = '0';
  while (scanf("%lld%c", &opcode, &end) != EOF && end == ',')
  {
    program.push_back(opcode);
    end = '0';
  }
  program.push_back(opcode);
}

void execute(int at)
{
  if (program[at] == 1)
    program[program[at + 3]] = program[program[at + 1]] + program[program[at + 2]];
  else if (program[at] == 2)
    program[program[at + 3]] = program[program[at + 1]] * program[program[at + 2]];
}
void run()
{
  int at = 0;
  while (program[at] != 99)
  {
    DEBUG printf("at: %d - %lld\n", at, program[0]);
    execute(at);
    at += 4;
  }
}

int main()
{
  read();
  for (int i = 0; i < program.size(); i += 4)
  {
    for (int j = 0; i + j < program.size() && j < 4; j ++)
      printf("%lld ", program[i + j]);
    printf("\n");
  }
  vector<lli> aux = program;

  int i, j;
  for (i = 0; i < 100 && program[0] != 19690720; i ++)
    for (j = 0; j < 100 && program[0] != 19690720; j ++)
    {
      program = aux;
      program[1] = i, program[2] = j;
      run();
      printf("%d %d (%d) - %lld\n", i, j, 100*i + j, program[0]);
    }

  return 0;
}