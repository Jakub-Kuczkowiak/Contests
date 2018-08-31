#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int M[4][4] = {};

		int row1, row2;
		cin >> row1;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> M[i][j];
			}
		}

		cin >> row2;
		int M2[4][4] = {};

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cin >> M2[i][j];
			}
		}

		row1--; row2--;

		int count = 0;
		int same = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (M[row1][i] == M2[row2][j]) {
					count++;
					same = M[row1][i];
				}
			}
		}

		if (count == 0) {
			cout << "Case #" << t << ": Volunteer cheated!" << endl;
		}
		else if (count == 1) {
			cout << "Case #" << t << ": " << same << endl;
		}
		else {
			cout << "Case #" << t << ": Bad magician!" << endl;
		}
	}

	return 0;
}