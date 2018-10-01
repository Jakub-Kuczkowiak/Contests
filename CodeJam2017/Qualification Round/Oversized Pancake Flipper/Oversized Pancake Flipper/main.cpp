#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		string S;
		cin >> S;
		int K;
		cin >> K;

		int flips = 0;
		for (int i = 0; i <= S.size() - K; i++) {
			if (S[i] == '-') {
				flips++;
				// flip K next
				for (int j = 0; j < K; j++) {
					if (S[i + j] == '-') S[i + j] = '+';
					else S[i + j] = '-';
				}
			}
		}

		bool bSuccess = true;
		for (int i = 0; i < S.size(); i++) {
			if (S[i] == '-') {
				cout << "Case #" << t << ": IMPOSSIBLE" << endl;
				bSuccess = false;
				break;
			}
		}

		if (bSuccess)
			cout << "Case #" << t << ": " << flips << endl;
	}

	return 0;
}