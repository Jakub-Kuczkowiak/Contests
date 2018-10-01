#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++)
	{
		string N;
		cin >> N;

		// find first incorrect index
		int lastDigit = N[0] - '0';
		int i;
		bool bIncorrect = false;
		for (i = 1; i < N.size(); i++) {
			int currentDigit = N[i] - '0';
			if (currentDigit < lastDigit) {
				bIncorrect = true;
				break;
			}

			lastDigit = currentDigit;
		}

		if (N.size() == 1 || (i == N.size())) {
			cout << "Case #" << t << ": " << N << endl;
			continue;
		}

		int nextDigit = N[i] - '0';
		int j;
		for (j = i - 1; j >= 0; j--) {
			int currentDigit = N[j] - '0';
			if (currentDigit >= nextDigit) {
				N[j] = N[j] - 1;
			}
			else {
				break;
			}

			nextDigit = currentDigit;
		}

		for (int k = j + 2; k < N.size(); k++) {
			N[k] = '9';
		}

		int k;
		for (k = 0; k < N.size(); k++) {
			if (N[k] != '0') break;
		}

		string B;
		for (int l = k; l < N.size(); l++) {
			B += N[l];
		}

		cout << "Case #" << t << ": " << B << endl;
	}

	return 0;
}