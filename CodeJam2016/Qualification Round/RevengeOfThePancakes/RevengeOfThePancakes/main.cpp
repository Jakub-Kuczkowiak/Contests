#include <iostream>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		string pancakes;
		cin >> pancakes;

		int answer = 0;
		bool bPrefixFlipped = false;
		for (int i = pancakes.size() - 1; i >= 0; i--) {
			if ((pancakes[i] == '-' && !bPrefixFlipped) || (pancakes[i] == '+' && bPrefixFlipped)) {
				answer++;
				bPrefixFlipped = !bPrefixFlipped;
			}
		}

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}