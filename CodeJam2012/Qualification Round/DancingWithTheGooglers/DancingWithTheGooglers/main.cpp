#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		int S;
		cin >> S;

		int p;
		cin >> p;

		int sums[101] = {};
		for (int i = 0; i < N; i++) {
			cin >> sums[i];
		}

		int answer = 0;
		// we go through each triplet
		for (int i = 0; i < N; i++) {
			if (sums[i] % 3 == 0) {
				int max = sums[i] / 3;

				if (max >= p) {
					answer++;
				}
				else if (S > 0 && max + 1 >= p && sums[i] > 1) {
					answer++;
					S--;
				}
			}
			else if (sums[i] % 3 == 1) {
				int max = (sums[i] / 3) + 1;

				if (max >= p) {
					answer++;
				}
			}
			else {
				int max = (sums[i] / 3) + 1;

				if (max >= p) {
					answer++;
				}
				else if (S > 0 && max + 1 >= p && sums[i] > 1) {
					answer++;
					S--;
				}
			}
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}