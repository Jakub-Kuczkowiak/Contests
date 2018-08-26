#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		long long n, A, B, C, D, x, y, M;
		cin >> n >> A >> B >> C >> D >> x >> y >> M;

		unsigned long long points[3][3] = {};
		points[x % 3][y % 3]++;

		for (int i = 1; i < n; i++) {
			x = (A * x + B) % M;
			y = (C * y + D) % M;

			points[x % 3][y % 3]++;
		}

		unsigned long long count = 0;
		for (int x0 = 0; x0 < 3; x0++) {
			for (int y0 = 0; y0 < 3; y0++) {
				if (points[x0][y0] == 0) continue;

				for (int x1 = 0; x1 < 3; x1++) {
					for (int y1 = 0; y1 < 3; y1++) {
						if (points[x1][y1] == 0) continue;

						if (x1 * 3 + y1 < 3 * x0 + y0) continue;

						for (int x2 = 0; x2 < 3; x2++) {
							for (int y2 = 0; y2 < 3; y2++) {
								if (points[x2][y2] == 0) continue;

								if (x2 * 3 + y2 < 3 * x1 + y1) continue;

								if ((x0 + x1 + x2) % 3 != 0) continue;
								if ((y0 + y1 + y2) % 3 != 0) continue;

								if (x0 == x1 && y0 == y1) { // first and second point the same
									if (x0 == x2 && y0 == y2) { // 3 points same
										count += (points[x0][y0] * (points[x0][y0] - 1) * (points[x0][y0] - 2)) / 6;
									}
									else { // 2 points same
										count += (points[x0][y0] * (points[x0][y0] - 1) * points[x2][y2]) / 2;
									}
								}
								else { // max 2 point ssame
									if (x0 == x2 && y0 == y2) { // 2 points same
										count += (points[x0][y0] * points[x1][y1] * (points[x0][y0] - 1)) / 2;
									}
									else if (x1 == x2 && y1 == y2) { // 2 points same
										count += (points[x0][y0] * points[x1][y1] * (points[x1][y1] - 1)) / 2;
									}
									else { // no same points
										count += (points[x0][y0] * points[x1][y1] * points[x2][y2]);
									}
								}
							}
						}
					}
				}
			}
		}

		cout << "Case #" << t << ": " << count << endl;
	}

	return 0;
}