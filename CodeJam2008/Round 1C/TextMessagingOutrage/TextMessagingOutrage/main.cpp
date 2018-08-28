#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string> // is needed in gcc?

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int P, K, L;
		cin >> P >> K >> L;

		vector<int> freq(L);
		for (int i = 0; i < L; i++) {
			cin >> freq[i];
		}

		sort(freq.begin(), freq.end(), greater<int>());
		long long cost = 0;
		int index = 0;
		int multiplier = 1;
		while (index < freq.size()) {
			for (int i = 0; i < K && index < freq.size(); i++) {
				cost = cost + freq[index] * multiplier;
				index++;
			}

			multiplier++;
		}

		cout << "Case #" << t << ": " << cost << endl;
	}

	return 0;
}