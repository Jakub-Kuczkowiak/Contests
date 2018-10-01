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
#define foreach(c, itr) for(__typeof((c).begin()) itr = (c).begin(); itr != (c).end(); itr++)

using namespace std;

int ways[1001][1001] = {};
vector< vector<int> > children;

void DFS(int startVertex, int v) {
	if (v != startVertex) {
		ways[startVertex][v]++;
		if (ways[startVertex][v] > 1) return; // this speeds up dramatically because we don't want to traverse same path more than once!
	}

	for (int i = 0; i < children[v].size(); i++) {
		// visit each child
		DFS(startVertex, children[v][i]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;
		children = vector< vector<int>>(N + 1);

		memset(ways, 0, sizeof(ways));

		for (int i = 1; i <= N; i++) {
			int M;
			cin >> M;

			for (int j = 0; j < M; j++) {
				int a;
				cin >> a;
				children[i].push_back(a);
			}
		}

		for (int i = 1; i <= N; i++) {
			DFS(i, i);
		}

		bool success = false;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (i != j) {
					if (ways[i][j] > 1) {
						success = true;
					}
				}
			}
		}

		cout << "Case #" << t << ": " << (success ? "Yes" : "No") << endl;
	}

	return 0;
}