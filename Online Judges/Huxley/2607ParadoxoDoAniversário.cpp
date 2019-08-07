#include <bits/stdc++.h>
#define lli long long int
using namespace std;

vector<string> days[13][32];
char months[13][50] = {"", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

int main()
{
  int n; scanf("%d", &n);
  while (n --)
  {
    string s; int d, m;
    cin >> s >> d >> m;
    days[m][d].push_back(s);
  }

  bool has = false;
  for (int i = 1; i <= 12; i ++)
    for (int j = 1; j <= 31; j ++)
      if (days[i][j].size() > 1)
      {
        printf("Dia %d de %s: ", j, months[i]);
        cout << days[i][j][0];
        for (int k = 1; k < days[i][j].size(); k ++)
          cout << ", " << days[i][j][k];
        printf("\n");
        has = true;
      }
  if (!has) printf("Ninguem faz aniversario no mesmo dia\n");

  return(0);
}