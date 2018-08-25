#include <iostream>
#include <limits.h>

using namespace std;

struct node
{
	int altitude;
	int label;
	node* parent;
	int i;
	int j;
};

node* getParent(node* n) {
	if (n->parent == nullptr) {
		return n;
	}

	n->parent = getParent(n->parent);
	return n->parent;
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int H, W;
		cin >> H >> W;

		node map[100][100] = {};

		char answer[100][100] = {};

		int labelling = 0;
		char lastChar = 'a';

		char labels[100 * 100] = {};

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				node n;
				cin >> n.altitude;
				n.parent = nullptr;
				n.label = labelling++;
				n.i = i;
				n.j = j;
				map[i][j] = n;
			}
		}

		// loop through each
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				// check for all neighbours and connect to them
				int min = INT_MAX;
				int minI = -1;
				int minJ = -1;
				if (i > 0)
					if (map[i - 1][j].altitude < min) {
						min = map[i - 1][j].altitude;
						minI = i - 1;
						minJ = j;
					}

				if (j > 0) {
					if (map[i][j - 1].altitude < min) {
						min = map[i][j - 1].altitude;
						minI = i;
						minJ = j - 1;
					}
				}

				if (j < W - 1)
					if (map[i][j + 1].altitude < min) {
						min = map[i][j + 1].altitude;
						minI = i;
						minJ = j + 1;
					}

				if (i < H - 1)
					if (map[i + 1][j].altitude < min) {
						min = map[i + 1][j].altitude;
						minI = i + 1;
						minJ = j;
					}


				if (map[minI][minJ].altitude < map[i][j].altitude) {
					map[i][j].parent = getParent(&map[minI][minJ]);
				}
			}
		}

		// loop again
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				node* n = getParent(&map[i][j]);
				if (labels[n->label] == 0) {
					labels[n->label] = lastChar;
					answer[i][j] = lastChar;
					lastChar++;
				}
				else {
					answer[i][j] = labels[n->label];
				}
			}
		}

		// print the answer
		cout << "Case #" << t << ":" << endl;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cout << answer[i][j] << " ";
			}

			cout << endl;
		}
	}

	return 0;
}