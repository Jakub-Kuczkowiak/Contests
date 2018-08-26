#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<int> arr(N);

		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}

		vector<int> copyArr = arr;
		sort(copyArr.begin(), copyArr.end());

		int toSort = N;
		for (int i = 0; i < N; i++) {
			if (arr[i] == copyArr[i])
				toSort--;
		}

		cout << "Case #" << t << ": " << toSort << endl;
	}

	return 0;
}