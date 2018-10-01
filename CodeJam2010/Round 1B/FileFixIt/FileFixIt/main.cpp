#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits.h> // INT_MAX
#include <math.h> // pow in g++
#include <string> // is needed in gcc?
//#include <bits/stdc++.h> // contains all headers instead (only on g++)

#define PRIME_MOD (1000000007) // should add to library

using namespace std;

struct Node
{
	unordered_map<string, Node*> nodes;
};

int createNode(Node* node, string& directory, int index) {
	if (index >= directory.size()) return 0;

	string parse;
	while (index < directory.size() && directory[index] != '/') {
		parse += directory[index];
		index++;
	}

	index++; // to miss /

	auto nextNode = node->nodes.find(parse);
	if (nextNode == node->nodes.end()) {
		Node* newNode = new Node();
		node->nodes[parse] = newNode;
		return createNode(newNode, directory, index) + 1;
	}
	else {
		return createNode(nextNode->second, directory, index);
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N, M;
		cin >> N >> M;

		Node* root = new Node();

		for (int i = 0; i < N; i++) {
			string directory;
			cin >> directory;

			createNode(root, directory, 1);
		}

		int count = 0;
		for (int i = 0; i < M; i++) {
			string directory;
			cin >> directory;

			count += createNode(root, directory, 1);
		}

		cout << "Case #" << t << ": " << count << endl;
	}

	return 0;
}