#include <iostream>
#include <string>

using namespace std;

char board[4][4] = {};

bool isWinner(char winner) {
	for (int i = 0; i < 4; i++) { // rows
		int sum = 0;
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == winner || board[i][j] == 'T') sum++;
		}

		if (sum == 4) return true;
	}

	for (int i = 0; i < 4; i++) { // columns
		int sum = 0;
		for (int j = 0; j < 4; j++) {
			if (board[j][i] == winner || board[j][i] == 'T') sum++;
		}

		if (sum == 4) return true;
	}

	// left diagonal
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		if (board[i][i] == winner || board[i][i] == 'T') sum++;
	}
	if (sum == 4) return true;

	// right
	sum = 0;
	for (int i = 0; i < 4; i++) {
		if (board[3 - i][i] == winner || board[3 - i][i] == 'T') sum++;
	}

	if (sum == 4) return true;

	return false;
}

int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		
		bool isFull = true;
		for (int i = 0; i < 4; i++) {
			string line;
			cin >> line;

			for (int j = 0; j < 4; j++) {
				board[i][j] = line[j];
				if (board[i][j] == '.') isFull = false;
			}
		}

		cout << "Case #" << t << ": ";

		// check if O wins
		if (isWinner('O')) {
			cout << "O won";
		}
		else if (isWinner('X')) {
			cout << "X won";
		}
		else if (isFull) {
			cout << "Draw";
		}
		else {
			cout << "Game has not completed";
		}

		cout << endl;
	}

	return 0;
}