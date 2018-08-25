#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	int L, D, N;

	cin >> L >> D >> N;
	vector<string> dict(D);

	for (int i = 0; i < D; i++) {
		cin >> dict[i];
	}

	for (int i = 1; i <= N; i++) {
		// each query here
		string query;
		cin >> query;

		vector<vector<char>> queryPattern = vector<vector<char>>(L);

		int letter = 0;
		for (int j = 0; j < query.size(); j++) {
			if (query[j] == '(') {
				int k = j + 1;
				while (query[k] != ')') {
					queryPattern[letter].push_back(query[k]);
					k++;
				}

				j = k;
			}
			else {
				queryPattern[letter].push_back(query[j]);
			}

			letter++;
		}

		int count = 0;

		for (int j = 0; j < D; j++) {
			// check for for each word if it is in this pattern
			bool bProperWord = true;
			for (int k = 0; k < L; k++) { // check for each letter if it fits into pattern
				bool bLetterFits = false;
				for (int s = 0; s < queryPattern[k].size(); s++) {
					if (queryPattern[k][s] == dict[j][k]) {
						bLetterFits = true;
						break;
					}
				}

				if (!bLetterFits) {
					bProperWord = false;
					break;
				}
			}

			if (bProperWord)
				count++;
		}

		cout << "Case #" << i << ": " << count << endl;
	}

	return 0;
}