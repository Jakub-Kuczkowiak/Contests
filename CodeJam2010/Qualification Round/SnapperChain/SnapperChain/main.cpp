#include <iostream>
#include <math.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N, K;
		cin >> N >> K;

		long long num = pow(2, N);
		K = K % num;

		if (K == num - 1) {
			cout << "Case #" << t << ": ON" << endl;
		}
		else {
			cout << "Case #" << t << ": OFF" << endl;
		}
	}

	int N, K;



	return 0;
}