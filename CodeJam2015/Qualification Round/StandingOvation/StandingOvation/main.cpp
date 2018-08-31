#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int S;
		cin >> S;

		string input;
		cin >> input;

		int T[1002] = {};

		for (int i = 0; i <= S; i++) {
			T[i] = input[i] - '0';
		}

		int answer = 0;
		int sum = T[0];
		for (int i = 1; i <= S; i++) {
			if (T[i] == 0) continue;

			if (sum < i) {
				answer += (i - sum);
				sum += (i - sum);
			}

			sum += T[i];
		}
		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}