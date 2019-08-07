#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

long double pitagoras(long double co, long double ca)
{
	return(sqrt(pow(co, 2) + pow(ca, 2)));
}

int main() {
	int tests; scanf("%d", &tests);
	while (tests > 0)
	{
		int mountains; scanf("%d", &mountains);
		vector<pair<int, int> > m;
		int i, x, y;
		for (i = 0; i < mountains; i ++)
		{
			scanf("%d %d", &x, &y);
			m.push_back(make_pair(x, y));
		}
		//m.push_back(make_pair(x,0));
		sort(m.begin(), m.end());

		int high = 0; long double total = 0;
		for (i = mountains - 2; i >= 0; i --) {

			if (m[i].second > high)
			{
				long double ca = m[i].second - m[i + 1].second;
				long double co = m[i + 1].first - m[i].first;
				long double H = pitagoras(co, ca);
				long double y = m[i].second - high;
				/*long double x = 0;
				if (ca != 0)
					x = (y * co) / ca;*/
				total += (y * H) / ca;
				high = m[i].second;
			}
		}

		printf("%.2Lf\n", total);

		tests --;
	}
}
/*
ca - y
H - h
h = (y * H) / ca*/
