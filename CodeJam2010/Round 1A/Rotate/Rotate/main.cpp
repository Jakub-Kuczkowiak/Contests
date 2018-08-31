#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <string> // is needed in gcc?
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

void printBoard(char board[50][50], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << board[i][j];
		}

		cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N, K;
		cin >> N >> K;

		char board[50][50] = {};
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				char c;
				cin >> c;
				board[i][j] = c;
			}
		}

		/*printBoard(board, N);
		cout << endl;*/

		// rotate
		char rotateBoard[50][50] = {};
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				rotateBoard[i][j] = board[N - j - 1][i];
			}
		}

		/*printBoard(rotateBoard, N);
		cout << endl;*/

		// gravity
		for (int j = 0; j < N; j++) {
			// for each column
			// walk once and collect information
			char column[51] = {};
			for (int i = N - 1; i >= 0; i--) {
				column[i] = rotateBoard[i][j];
			}

			int columIndex = N - 1;
			int i = N - 1;
			for (; i >= 0; i--) {
				while (columIndex >= 0 && column[columIndex] == '.') columIndex--;

				if (columIndex < 0) {
					break;
				}

				rotateBoard[i][j] = column[columIndex--];
			}

			for (int rest = i; rest >= 0; rest--) {
				rotateBoard[rest][j] = '.';
			}
		}

		/*printBoard(rotateBoard, N);
		cout << endl;*/

		// now checking here.
		bool redWin = false;
		bool blueWin = false;

		// check each row
		for (int i = 0; i < N; i++) {
			for (int j = 0; j + K - 1 < N; j++) {
				int count = 0;
				for (int k = 0; k < K; k++) {
					if (rotateBoard[i][j + k] == 'R') count++;
					else if (rotateBoard[i][j + k] == 'B') count--;
				}

				if (count == K) {
					redWin = true;
				}
				else if (count == -K) {
					blueWin = true;
				}
			}
		}

		// check each column
		for (int i = 0; i + K - 1 < N; i++) {
			for (int j = 0; j < N; j++) {
				int count = 0;
				for (int k = 0; k < K; k++) {
					if (rotateBoard[i + k][j] == 'R') count++;
					else if (rotateBoard[i + k][j] == 'B') count--;
				}

				if (count == K) {
					redWin = true;
				}
				else if (count == -K) {
					blueWin = true;
				}
			}
		}

		// check each diagonal \ /
		for (int i = 0; i + K - 1 < N; i++) {
			for (int j = 0; j + K - 1 < N; j++) {
				int count = 0;
				for (int k = 0; k < K; k++) {
					if (rotateBoard[i + k][j + k] == 'R') count++;
					else if (rotateBoard[i + k][j + k] == 'B') count--;
				}

				if (count == K) {
					redWin = true;
				}
				else if (count == -K) {
					blueWin = true;
				}
			}
		}

		for (int i = N - 1; i - K + 1 >= 0; i--) {
			for (int j = 0; j + K - 1 < N; j++) {
				int count = 0;
				for (int k = 0; k < K; k++) {
					if (rotateBoard[i - k][j + k] == 'R') count++;
					else if (rotateBoard[i - k][j + k] == 'B') count--;
				}

				if (count == K) {
					redWin = true;
				}
				else if (count == -K) {
					blueWin = true;
				}
			}
		}

		cout << "Case #" << t << ": ";
		if (blueWin && redWin) {
			cout << "Both";
		}
		else if (blueWin && !redWin) {
			cout << "Blue";
		}
		else if (!blueWin && redWin) {
			cout << "Red";
		}
		else {
			cout << "Neither";
		}

		cout << endl;
	}

	return 0;
}