#include <bits/stdc++.h>
int DEBUG = 0, QQQ = 0;
using namespace std;

double getNorm(int p1[2], int p2[2])
{
  return(sqrt(pow(p2[1] - p1[1], 2) + pow(p2[0] - p1[0], 2)));
}

double getAngle(int p1[2], int p2[2])
{
  if (atan2(abs(p2[1] - p1[1]), abs(p2[0] - p1[0])) == 0) return(round(1000000 * 2 * atan(1)) / 1000000);
  return(round(1000000 * abs(atan2(abs(p2[1] - p1[1]), abs(p2[0] - p1[0])))) / 1000000);
}

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int size; scanf("%d", &size);
    int coordinates[size][2];
    for (int i = 0; i < size; i ++)
      scanf("%d %d", &coordinates[i][0], &coordinates[i][1]);

    map<double, vector<double> > mostAppearing;
    double theAngle = (size - 2) * (180/size), theNorm = 0;
    theAngle = round(1000000 * (theAngle * M_PI / 180.0)) / 1000000;
    if (DEBUG) printf("The angle %lf\n", theAngle);
    int isColinear = 0, isNotSameSize = 0;
    for (int i = 0; i < size; i ++)
    {
      map<double, int> colinear;
      for (int j = 0; j < size; j ++)
      {
        if (i != j)
        {
          if (mostAppearing.count(getAngle(coordinates[i], coordinates[j])) == 0)
            mostAppearing.insert({getAngle(coordinates[i], coordinates[j]), {0, getAngle(coordinates[i], coordinates[j]), getNorm(coordinates[i], coordinates[j])}});
          //if (theAngle == getAngle(coordinates[i], coordinates[j])) printf("%lf %lf\n", mostAppearing[getAngle(coordinates[i], coordinates[j])][2], getNorm(coordinates[i], coordinates[j]));
          if (theAngle == getAngle(coordinates[i], coordinates[j]) && mostAppearing[getAngle(coordinates[i], coordinates[j])][2] != getNorm(coordinates[i], coordinates[j]))
          {
            //printf("HOLYFOCK %lf %lf\n", mostAppearing[getAngle(coordinates[i], coordinates[j])][2], getNorm(coordinates[i], coordinates[j]));
            isNotSameSize = 1;
            break;
          }
          mostAppearing[getAngle(coordinates[i], coordinates[j])][0] ++;
          if (colinear.count(getAngle(coordinates[i], coordinates[j])) == 0)
            colinear.insert({getAngle(coordinates[i], coordinates[j]), 0});
          else
          {
            //isColinear = 1;
            //break;
          }
        }
      }
    }
    if (DEBUG)
    {
      for (auto i : mostAppearing)
        printf("%lf %lf %lf\n", i.second[0], i.second[1], i.second[2]);
    }
    if (isColinear)
    {
      if (DEBUG) printf("Colinear\n");
      printf("NO\n");
    }
    else
    {
      if (isNotSameSize || (mostAppearing.count(theAngle) == 0)) // || (mostAppearing.count(theAngle) > 0 and mostAppearing[theAngle][0] != size))
      {
        if (DEBUG) printf("Sides diff\n");
        printf("NO\n");
      }
      else
        printf("YES\n");
    }
    tests --;
  }
  return(0);
}