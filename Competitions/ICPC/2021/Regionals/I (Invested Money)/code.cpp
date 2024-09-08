#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int today, n;
const vector<string> days = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
lli d[maxN];
char ds[4];

lli daysToWait[maxN];

int getDay(string s)
{
  for (int i = 0; i < days.size(); ++i)
    if (s == days[i])
      return i;
  assert(false);
  return -1;
}

bool isWeekend(lli day)
{
  return day % 7 >= 5;
}
void move30Days(lli& depositDay, lli& daysToToday)
{
  depositDay += 30;
  depositDay %= 7;
  if (isWeekend(depositDay))
  {
    daysToToday -= 7 - depositDay;
    depositDay = 0;
  }
  daysToToday -= 30;
}
lli calcDaysToWait(lli day)
{
  // Which day of the week the deposit was made
  lli depositDay = ((today - day) % 7 + 7) % 7;
  assert(!isWeekend(depositDay));
  lli daysToToday = day;

  // It will only loop safely when it's a monday
  // So while it's not: move it around until it is
  while (depositDay != 0 && daysToToday >= 32)
    move30Days(depositDay, daysToToday);

  // It's a monday, so it will look safely.
  // The loop is: monday, wednesday, friday, sunday
  // Notice that we can't access the bank on sunday, so we add wait for an
  // extra day and finally go back to monday after exactly 91 days.
  if (depositDay == 0 && daysToToday >= 30)
    daysToToday %= 91;

  while (daysToToday >= 32)
    move30Days(depositDay, daysToToday);

  DEBUG printf("\t%lld %lld\n", day, daysToToday);
  assert((depositDay + daysToToday) % 7 == today);

  lli waitingDays = 30 - daysToToday;
  // Wait might end on a weekend
  if (daysToToday > 30)
  {
    depositDay += 30;
    depositDay %= 7;
    daysToToday -= 30;
    if (isWeekend(depositDay))
      waitingDays = 7 - depositDay;
    else
      waitingDays = 30 - daysToToday;
  }
  if (daysToToday == 0)
    waitingDays = 0;
  if (day == 0)
    waitingDays = 30;

  lli withdrawDay = today + waitingDays;
  withdrawDay %= 7;
  if (isWeekend(withdrawDay))
    waitingDays += 7 - withdrawDay;
  return waitingDays;
}

int main()
{
  while (~scanf(" %s %d", ds, &n))
  {
    today = getDay(string(ds));
    for (int i = 0; i < n; ++i)
      scanf("%lld", &d[i]);

    for (int i = 0; i < n; ++i)
      daysToWait[i] = calcDaysToWait(d[i]);

    lli ans = *min_element(daysToWait, daysToWait+n);
    printf("%lld\n", ans);
  }
  return 0;
}