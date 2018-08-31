#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		double C, F, X;
		cin >> C >> F >> X;

		double currentSpeed = 2;

		double minTime = X / currentSpeed;
		double time = C / currentSpeed;

		while (time < minTime) {
			currentSpeed += F;
			double thisTime = time + (X / currentSpeed);

			if (thisTime < minTime) {
				minTime = thisTime;
			}

			time += (C / currentSpeed);
		}

		
		cout << setprecision(51) << "Case #" << t << ": " << minTime << endl;
	}

	return 0;
}