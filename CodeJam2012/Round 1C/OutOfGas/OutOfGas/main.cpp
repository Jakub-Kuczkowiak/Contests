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

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		long double D;
		int N, A;
		cin >> D >> N >> A;

		vector<long double> times(N);
		vector<long double> positions(N);
		for (int i = 0; i < N; i++) {
			//cin >> times[i] >> positions[i];
			scanf("%Lf%Lf", &times[i],&positions[i]);
		}

		vector<long double> acceleration(A);
		for (int i = 0; i < A; i++) {
			//cin >> acceleration[i];
			scanf("%Lf", &acceleration[i]);
		}

		// find if it contains description of time
		// to finish in the end
		if (positions[N - 1] > D) {
			// calculate time
			long double speed = (positions[N - 1] - positions[N - 2]) / (long double)(times[N - 1] - times[N - 2]);
			long double time = times[N - 2] + (D - positions[N - 2]) / speed;
			positions.pop_back();
			positions.push_back(D);
			times.pop_back();
			times.push_back(time);
		}

		cout << "Case #" << t << ": " << endl;

		// for each acceleration
		for (long double acc : acceleration) {
			// now find how much time is needed for each
			long double maxTime = 0;
			for (int i = 0; i < N; i++) {
				// s = at^2 / 2 + v0*t, but v0 = 0, so s = at^2 / 2
				// therefore time required is
				// t = sqrt(2s/a)
				long double timeRequired = pow((2 * positions[i]) / acc, 0.5);
				if (timeRequired < times[i]) { // means we reach destination faster than car and have to wait
					long double wait = times[i] - timeRequired;
					if (wait > maxTime)
						maxTime = wait;
				}
			}

			// required time is
			long double timeRequired = pow((2 * D) / acc, 0.5) + maxTime;

			printf("%.7Lf\n", timeRequired);
		}
	}

	return 0;
}