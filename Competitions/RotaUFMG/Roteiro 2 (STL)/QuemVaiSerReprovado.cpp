#include <bits/stdc++.h>
using namespace std;

bool comp(const pair<int, string> &a, const pair<int, string> &b)
{
  return(a.first == b.first ? a.second > b.second : a.first < b.first);
}

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t) printf("\n");

    pair<int, string> people[n];
    string name; int grade;//string name[n]; int grade[n];
    for (int i = 0; i < n; i ++)
    {
      cin >> name >> grade;
      people[i].first = grade; people[i].second = name;
    }
    sort(people, people+n, comp);

    printf("Instancia %d\n", ++ t);
    cout << people[0].second << endl;
  }
  return(0);
}