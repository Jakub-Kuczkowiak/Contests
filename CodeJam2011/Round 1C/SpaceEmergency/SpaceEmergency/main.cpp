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

int main() {
	//ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		long long L, time, N, C;
		cin >> L >> time >> N >> C;
		priority_queue<double> edges;
		vector<long long> c(C);
		for (int i = 0; i < C; i++) {
			cin >> c[i];
		}

		long long sum = 0;
		for (int i = 0; i < N; i++) {
			//edges.push(-c[i % C]);
			sum += c[i % C];
		}

		// check where we get in time 'time'
		double dist = 0.5 * time;
		int i;
		for (i = 0; i < N; i++) {
			if (dist - c[i % C] < 0) {
				break;
			}

			dist = dist - c[i % C];
		}

		if (i == N) {
			// that means that we can't benefit from any edges
			cout << "Case #" << t << ": " << sum * 2 << endl;
			continue;
		}

		// now we know what station we are at
		// push that partial edge
		edges.push(c[i % C] - dist);

		for (int j = i + 1; j < N; j++) {
			edges.push(c[j % C]);
		}

		// now we make see how much we benefit from L largest stations
		double earnedSum = 0;
		while (!edges.empty() && L > 0) {
			double edge = edges.top();
			edges.pop();

			L--;
			earnedSum += edge;
		}

		cout << "Case #" << t << ": ";
		printf("%.0f\n", sum * 2 - earnedSum);

		//cout << "Case #" << t << ": " << sum * 2 - earnedSum << endl;
	}

	return 0;
}