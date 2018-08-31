#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string> // is needed in gcc?
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

class Tree {
public:
	Tree* yesTree;
	Tree* noTree;
	double weight;
	string feature;
};

int parseBracket(string desc, int index, char bracket) {
	for (int i = index; i < desc.size(); i++) {
		if (desc[i] == bracket) {
			return i + 1;
		}
	}
}

int parseValue(string desc, int index, double& dVal) {
	for (int i = index; i < desc.size(); i++) {
		if (desc[i] == ' ' || desc[i] == '\n') {
			continue;
		}

		int startIndex = i;
		int j;
		string value;
		for (j = startIndex; (desc[j] >= '0' && desc[j] <= '9') || desc[j] == '.'; j++) {
			value += desc[j];
		}

		dVal = stod(value);
		return j;
	}
}

int parseChars(string desc, int index) {
	while (desc[index] == ' ' || desc[index] == '\n') index++;
	return index;
}

int parseFeature(string desc, int index, string& feature) {
	while (desc[index] >= 'a' && desc[index] <= 'z') {
		feature += desc[index];
		index++;
	}

	return index;
}

int parseTree(string desc, int index, Tree* tree) {
	index = parseBracket(desc, index, '(');
	double value;
	index = parseValue(desc, index, value);
	tree->weight = value;

	index = parseChars(desc, index);
	if (desc[index] >= 'a' && desc[index] <= 'z') {
		string feature;
		index = parseFeature(desc, index, feature);

		Tree* yes = new Tree();
		Tree* no = new Tree();
		index = parseTree(desc, index, yes);
		index = parseTree(desc, index, no);

		tree->yesTree = yes;
		tree->noTree = no;
		tree->feature = feature;
	}
	else {
		tree->yesTree = nullptr;
		tree->noTree = nullptr;
	}

	index = parseBracket(desc, index, ')');

	return index;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int lines; cin >> lines;

		string puff;
		getline(cin, puff);

		string treeDesc = "";
		for (int i = 0; i < lines; i++) {
			string line;
			getline(cin, line);

			treeDesc += line;
		}

		Tree* tree = new Tree;
		parseTree(treeDesc, 0, tree);

		int animal;
		cin >> animal;

		cout << "Case #" << t << ": " << endl;

		Tree* copyPtr = tree;

		for (int i = 0; i < animal; i++) {
			tree = copyPtr;

			string name;
			cin >> name;
			int f;
			cin >> f;
			unordered_set<string> features;
			
			for (int j = 0; j < f; j++) {
				string feature;
				cin >> feature;
				features.insert(feature);
			}

			double probability = 1;
			while (true) {
				probability = probability * tree->weight;
				if (tree->yesTree == nullptr) break;

				if (features.find(tree->feature) != features.end()) {
					// there exists such a feature so we go to yes
					tree = tree->yesTree;
				}
				else {
					tree = tree->noTree;
				}
			}

			printf("%f\n", probability);
		}

		getline(cin, puff);
	}

	return 0;
}