#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int n;
		cin >> n;

		vector<long long> a(n), b(n);
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}

		for (int i = 0; i < n; i++) {
			cin >> b[i];
		}

		sort(a.begin(), a.end());
		sort(b.begin(), b.end());

		long long value = 0;
		for (int i = 0; i < n; i++) {
			value += a[i] * b[n - 1 - i];
		}

		cout << "Case #" << t << ": " << value << endl;
	}

	return 0;
}