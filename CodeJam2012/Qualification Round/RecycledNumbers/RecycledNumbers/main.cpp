#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int getLen(int number) {
	int length = 0;
	while (number > 0) {
		number /= 10;
		length++;
	}

	return length;
}

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int A, B;
		cin >> A >> B;

		long long answer = 0;

		vector< pair<int, int> > answers;

		for (int i = A; i < B; i++) {
			int aSize = getLen(i);

			int newPair = i;
			for (int j = 0; j < aSize - 1; j++) {
				// we search all possible pairs
				int remainder = newPair % 10;
				newPair = newPair / 10;
				newPair = newPair + remainder * pow(10, aSize - 1);

				if (remainder != 0 && newPair > i && newPair <= B) {
					answer++;

					answers.push_back(pair<int, int>(i, newPair));
				}

				if (newPair == i) break;
			}
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}