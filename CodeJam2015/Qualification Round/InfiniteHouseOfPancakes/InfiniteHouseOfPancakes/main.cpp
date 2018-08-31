#include <iostream>
#include <queue>
#include <limits.h>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int D;
		cin >> D;

		int P[1001] = {};

		for (int i = 0; i < D; i++) {
			cin >> P[i];
		}

		int minimalAnswer = INT_MAX;

		for (int x = 1; x <= 1000; x++) {
			// what it means that we have x second to be done after moving? It means that each plate is not bigger than x and
			// that we must divide each plate optimally into empty plates.
			int moves = x;
			for (int i = 0; i < D; i++) {
				moves += (P[i] + x - 1) / x - 1;
			}

			if (moves < minimalAnswer)
				minimalAnswer = moves;
		}

		cout << "Case #" << t << ": " << minimalAnswer << endl;
	}

	return 0;
}