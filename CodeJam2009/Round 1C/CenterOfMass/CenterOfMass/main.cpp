#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string> // is needed in gcc?
#include <math.h>
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

struct Firework
{
	int x, y, z, vx, vy, vz;
};

double distance(double x, double y, double z) {
	double d = x * x + y * y + z * z;
	return pow(d, 1 / 2.0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;
		vector<Firework> fireworks(N);
		int sumX = 0, sumY = 0, sumZ = 0;
		double velocityX= 0, velocityY = 0, velocityZ = 0;
		for (int i = 0; i < N; i++) {
			cin >> fireworks[i].x >> fireworks[i].y >> fireworks[i].z;
			cin >> fireworks[i].vx >> fireworks[i].vy >> fireworks[i].vz;
			velocityX += fireworks[i].vx;
			velocityY += fireworks[i].vy;
			velocityZ += fireworks[i].vz;
			sumX += fireworks[i].x;
			sumY += fireworks[i].y;
			sumZ += fireworks[i].z;
		}

		velocityX /= (double)N;
		velocityY /= (double)N;
		velocityZ /= (double)N;

		double centerX = sumX / (double)N, centerY = sumY / (double)N, centerZ = sumZ / (double)N;

		if (velocityX == 0 && velocityY == 0 && velocityZ == 0) {
			double d = distance(centerX, centerY, centerZ);
			double zero = 0;
			printf("Case #%d: %.8f %.8f\n", t, d, zero);
			continue;
		}
		
		// to calculate formula we use
		// d^2(t) = (x0 + VxT)^2 + ... + (z0 + VzT)^2 and take derivative at t and solve equation for 0

		double minTime = centerX * velocityX + centerY * velocityY + centerZ * velocityZ;
		minTime = -minTime;
		minTime /= (velocityX * velocityX + velocityY * velocityY + velocityZ * velocityZ);

		if (minTime < 0) minTime = 0;

		centerX += velocityX * minTime;
		centerY += velocityY * minTime;
		centerZ += velocityZ * minTime;

		double d = distance(centerX, centerY, centerZ);

		printf("Case #%d: %.8f %.8f\n", t, d, minTime);
	}

	return 0;
}