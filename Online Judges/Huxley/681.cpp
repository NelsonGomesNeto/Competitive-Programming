// UVa 920 - Sunny Mountains

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

struct point {
	double x, y;
};

bool operator <(point a, point b) {
	return a.x > b.x;
}

int main() {
	int t;
	for (cin >> t; t; t--) {
		point p[100];
		// input
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> p[i].x >> p[i].y;
		sort(p, p + n);
		// calc
		double biggest_y = 0, sol = 0;
		for (int i = 1; i < n; i++) {
			if (p[i].y > biggest_y && p[i].y > p[i - 1].y) {
				double dx = p[i].x - p[i - 1].x;
				double dy = p[i].y - p[i - 1].y;
				double h = sqrt(dx * dx + dy * dy);
				double sunny_y = p[i].y - biggest_y;
				double sunny = sunny_y * h / dy;
				sol += sunny;
			}
			biggest_y = max(biggest_y, p[i].y);
		}
		// output
		printf("%.2f\n", sol);
	}
	return 0;
}
