#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
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

int X, Y;

struct State
{
	State* prevState;
	int n;
	long long x, y;
};

long long heuro(State* state) {
	int answer = (abs(state->x - X) + abs(state->y - Y)); //* state->n;
	return answer;
}

class Compare {
public:
	bool operator() (State* a, State* b) {
		long long ha = heuro(a);
		long long hb = heuro(b);

		//if (ha == hb)
			//return a->n > b->n;

		return ha > hb;
	}
}compare;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		cin >> X >> Y;

		// let's do BFS
		priority_queue<State*, vector<State*>, Compare> pq;
		State* startState = new State;
		startState->n = 1;
		startState->prevState = nullptr;
		startState->x = startState->y = 0;
		pq.push(startState);

		State* finalState = nullptr;
		while (!pq.empty()) {
			State* st = pq.top();
			pq.pop();

			if (st->x == X && st->y == Y) {
				// end state
				finalState = st;
				break;
			}

			// find all new states
			State* up = new State;
			up->n = st->n + 1;
			up->prevState = st;
			up->x = st->x;
			up->y = st->y + st->n;

			State* down = new State;
			down->n = st->n + 1;
			down->prevState = st;
			down->x = st->x;
			down->y = st->y - st->n;

			State* left = new State;
			left->n = st->n + 1;
			left->prevState = st;
			left->x = st->x - st->n;
			left->y = st->y;

			State* right = new State;
			right->n = st->n + 1;
			right->prevState = st;
			right->x = st->x + st->n;
			right->y = st->y;

			pq.push(up);
			pq.push(down);
			pq.push(left);
			pq.push(right);
		}

		string answer;
		while (finalState->prevState != nullptr) {
			if (finalState->x == finalState->prevState->x) {
				if (finalState->y < finalState->prevState->y) {
					answer += 'S';
				}
				else {
					answer += 'N';
				}
			}
			else {
				if (finalState->x < finalState->prevState->x) {
					answer += 'E';
				}
				else {
					answer += 'W';
				}
			}

			finalState = finalState->prevState;
		}

		reverse(answer.begin(), answer.end());

		cout << "Case #" << t << ": " << answer << endl;
	}

	return 0;
}