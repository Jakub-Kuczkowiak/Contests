#include <iostream>

using namespace std;

class Elem
{
public:
	long long sum;
	int newIndex;
};

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int R, k, N;
		cin >> R >> k >> N;

		int G[1002] = {};

		for (int i = 0; i < N; i++) {
			cin >> G[i];
		}

		Elem PreSum[1002] = {};
		long long sum = 0;
		int j;
		for (j = 0; j < N; j++) {
			if (sum + G[j] <= k)
				sum += G[j];
			else
				break;
		}
		PreSum[0].sum = sum;
		PreSum[0].newIndex = j % N;

		for (int i = 1; i < N; i++) {
			PreSum[i].sum = PreSum[i - 1].sum - G[i - 1];
			int j;
			bool bFirstTime = true;
			for (j = PreSum[i - 1].newIndex; bFirstTime || (j != i); j = (j + 1) % N) {
				bFirstTime = false;
				if (PreSum[i].sum + G[j] <= k)
					PreSum[i].sum += G[j];
				else
					break;
			}

			PreSum[i].newIndex = j % N;
		}

		long long answer = 0;
		int index = 0;
		for (int i = 0; i < R; i++) {
			answer += PreSum[index].sum;
			index = PreSum[index].newIndex;
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}