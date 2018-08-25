#include <iostream>
#include <string>

using namespace std;

string strFind = "welcome to code jam";

int main() {
	int N;
	cin >> N;

	string dump;
	getline(cin, dump);

	int dp[501][19] = {};

	for (int t = 1; t <= N; t++) {
		int answer = 0;

		for (int i = 0; i < 501; i++) {
			for (int j = 0; j < 19; j++) {
				dp[i][j] = 0;
			}
		}

		string querry;
		getline(cin, querry);

		for (int j = strFind.size() - 1; j >= 0; j--) {
			dp[querry.size() - 1][j] = 0; // substrings with querry suffix being last letter and ending m
		}

		dp[querry.size() - 1][strFind.size() - 1] = (querry[querry.size() - 1] == 'm');

		for (int i = querry.size() - 2; i >= 0; i--)
			dp[i][strFind.size() - 1] = dp[i + 1][strFind.size() - 1] + (querry[i] == 'm');

		for (int i = querry.size() - 2; i >= 0; i--) {
			for (int j = strFind.size() - 2; j >= 0; j--) {
				if (querry[i] == strFind[j])
					dp[i][j] = (dp[i + 1][j + 1] + dp[i + 1][j]) % 10000;
				else
					dp[i][j] = (dp[i + 1][j]) % 10000;
			}
		}

		cout << "Case #" << t << ": ";
		if (dp[0][0] >= 1000) {
			cout << dp[0][0];
		}
		else if (dp[0][0] >= 100) {
			cout << "0" << dp[0][0];
		}
		else if (dp[0][0] >= 10) {
			cout << "00" << dp[0][0];
		}
		else {
			cout << "000" << dp[0][0];
		}

		cout << endl;
	}

	return 0;
}