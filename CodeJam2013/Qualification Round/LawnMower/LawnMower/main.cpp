#include <iostream>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N, M;
		cin >> N >> M;

		int board[101][101] = {};
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> board[i][j];
			}
		}

		// find maximum for each row and column
		int rowsMax[101] = {};
		int columnsMax[101] = {};

		for (int i = 0; i < N; i++) {
			rowsMax[i] = -1;
			for (int j = 0; j < M; j++) {
				if (board[i][j] > rowsMax[i])
					rowsMax[i] = board[i][j];
			}
		}

		for (int i = 0; i < M; i++) {
			columnsMax[i] = -1;
			for (int j = 0; j < N; j++) {
				if (board[j][i] > columnsMax[i])
					columnsMax[i] = board[j][i];
			}
		}

		// for each field we check

		bool lost = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				int field = board[i][j]; // desired height
				if (rowsMax[i] > field && columnsMax[j] > field) {
					lost = true;
					break;
				}
			}

			if (lost)
				break;
		}

		if (lost) {
			cout << "Case #" << t << ": NO" << endl;
		}
		else {
			cout << "Case #" << t << ": YES" << endl;
		}
	}

	return 0;
}