#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<int> bags(N);

		int xorSum = 0;
		int sum = 0;
		int min = INT_MAX;
		for (int i = 0; i < N; i++) {
			cin >> bags[i];
			xorSum ^= bags[i];
			sum += bags[i];

			if (bags[i] < min) {
				min = bags[i];
			}
		}

		if (xorSum != 0) {
			cout << "Case #" << t << ": NO" << endl;
			continue;
		}

		sum -= min;

		cout << "Case #" << t << ": " << sum << endl;
	}

	return 0;
}