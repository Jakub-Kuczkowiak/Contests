#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

using namespace std;

int scoreboard[100][100] = {};
double wp[100] = {};
double owp[100] = {};
double owwp[100] = {};

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int n;
		cin >> n;

		memset(scoreboard, 0, sizeof(scoreboard));
		memset(wp, 0, sizeof(wp));
		memset(owp, 0, sizeof(owp));
		memset(owwp, 0, sizeof(owwp));

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				char c;
				cin >> c;
				if (c == '1' || c == '0') {
					scoreboard[i][j] = c - '0';
				}
				else {
					scoreboard[i][j] = -1;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			// for each team
			int gamesPlayed = 0;
			int gamesWon = 0;
			for (int j = 0; j < n; j++) {
				if (scoreboard[i][j] == -1) {

				}
				else if (scoreboard[i][j] == 1) {
					gamesPlayed++;
					gamesWon++;
				}
				else {
					gamesPlayed++;
				}
			}

			wp[i] = (double)gamesWon / (double)gamesPlayed;
		}

		for (int i = 0; i < n; i++) {
			// for each team

			// go through all teams
			double sum = 0;
			int opponentsNumber = 0;
			for (int j = 0; j < n; j++) {
				if (j == i) continue;
				if (scoreboard[i][j] == -1) continue;
				opponentsNumber++;

				int gamesPlayed = 0;
				int gamesWon = 0;
				for (int k = 0; k < n; k++) {
					if (scoreboard[j][k] == -1 || k == i) {

					}
					else if (scoreboard[j][k] == 1) {
						gamesPlayed++;
						gamesWon++;
					}
					else {
						gamesPlayed++;
					}
				}

				sum += (double)gamesWon / (double)gamesPlayed;
				//cout << sum << endl;
			}

			owp[i] = (sum / (double)(opponentsNumber));
		}

		for (int i = 0; i < n; i++) {
			// for each team
			int opponentsNumber = 0;
			double sum = 0;
			for (int j = 0; j < n; j++) {
				if (j == i) continue;
				if (scoreboard[i][j] == -1) continue;
				opponentsNumber++;

				sum += owp[j];
			}

			owwp[i] = (sum / (double)(opponentsNumber));
		}

		cout << "Case #" << t << ": " << endl;

		for (int i = 0; i < n; i++) {
			double rpi = 0.25 * wp[i] + 0.5 * owp[i] + 0.25 * owwp[i];
			printf("%.9f\n", rpi);
		}

		/*for (int i = 0; i < n; i++) {
			cout << i << ": " << "WP = " << wp[i] << " , OWP = " << owp[i] << " , OWWP = " << owwp[i] << endl;
		}*/
	}

	return 0;
}