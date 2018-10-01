#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
#include <cstring> // one of string can be removed; cstring contains memset
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define REP(i, n) for((i)=0; (i)<(int)(n); (i)++)
#define foreach(c, itr) for(__typeof((c).begin()) itr=(c).begin(); itr!=(c).end(); itr++)

using namespace std;

char Arr[50][50];

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int R, C;
		cin >> R >> C;
		
		memset(Arr, 0, sizeof(Arr));

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cin >> Arr[i][j];
			}
		}

		// from top
		bool bImpossible = false;
		for (int i = 0; i < R; i++) {
			// from left
			for (int j = 0; j < C; j++) {
				if (Arr[i][j] == '#') {
					// we not try to make it red
					if (i == R - 1 || j == C - 1) {
						bImpossible = true;
						break;
					}

					if (Arr[i + 1][j] != '#' || Arr[i][j + 1] != '#' || Arr[i + 1][j + 1] != '#') {
						bImpossible = true;
						break;
					}

					Arr[i][j] = Arr[i + 1][j + 1] = '/';
					Arr[i + 1][j] = Arr[i][j + 1] = '\\';
				}
			}

			if (bImpossible) break;
		}

		cout << "Case #" << t << ": " << endl;

		if (bImpossible) {
			cout << "Impossible" << endl;
		}
		else {
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					cout << Arr[i][j];
				}

				cout << endl;
			}
		}
	}

	return 0;
}