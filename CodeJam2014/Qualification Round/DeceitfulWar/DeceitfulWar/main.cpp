#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<double> Ken(N);
		vector<double> Naomi(N);

		for (int i = 0; i < N; i++) {
			cin >> Ken[i];
		}

		for (int i = 0; i < N; i++) {
			cin >> Naomi[i];
		}

		// war
		sort(Ken.begin(), Ken.end());
		sort(Naomi.begin(), Naomi.end());

		vector<double> KenCopy = Naomi;
		vector<double> NaomiCopy = Ken;

		int z = 0;

		for (int i = 0; i < N; i++) { // for each Ken's
			bool bLoss = false;
			for (auto it = Naomi.begin(); it != Naomi.end(); it++){
				if (*it > Ken[i]) {
					Naomi.erase(it);
					bLoss = true;
					break;
				}
			}

			if (!bLoss) {
				z++;
			}
		}

		int d = 0;

		for (int i = 0; i < N; i++) { // for each Naomi's
			if (NaomiCopy[i] < KenCopy[0]) {
				// we remove with last
				KenCopy.erase(--KenCopy.end());
			}
			else {
				KenCopy.erase(KenCopy.begin());
				d++;
			}
		}

		cout << "Case #" << t << ": " << d << " " << z << endl;
	}

	return 0;
}