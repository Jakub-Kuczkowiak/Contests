#include <iostream>
#include <vector>

using namespace std;

enum Color {
	Orange,
	Blue
};

class Event
{
public:
	Color color;
	int button;
};


int main() {
	int T;
	cin >> T;

	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;

		vector<Event> events(N);

		for (int i = 0; i < N; i++) {
			char colour;
			cin >> colour;

			int button;
			cin >> button;

			Event evnt;
			evnt.button = button;
			if (colour == 'O') {
				evnt.color = Orange;
			}
			else {
				evnt.color = Blue;
			}

			events[i] = evnt;
		}

		int orangePosition = 1;
		int bluePosition = 1;

		Event lastEvent = events[0];
		int time = lastEvent.button - 1 + 1;
		int additionalTime = time;

		if (events[0].color == Orange) {
			orangePosition = events[0].button;
		}
		else {
			bluePosition = events[0].button;
		}

		for (int i = 1; i < N; i++) {
			Color currentColor = events[i].color;
			int currentPosition = (events[i].color == Orange ? orangePosition : bluePosition);

			if (currentColor == lastEvent.color) {
				int distanceTime = abs(currentPosition - events[i].button) + 1;
				time += distanceTime;
				additionalTime += distanceTime;
			}
			else {
				// use one time movement bonus
				int distanceTime = abs(currentPosition - events[i].button) -  additionalTime;
				if (distanceTime <= 0) {
					distanceTime = 1;
				}
				else {
					distanceTime += 1;
				}

				time += distanceTime;
				additionalTime = distanceTime;
			}

			lastEvent = events[i];

			if (currentColor == Orange) {
				orangePosition = events[i].button;
			}
			else {
				bluePosition = events[i].button;	
			}
		}

		cout << "Case #" << t << ": " << time << endl;
	}

	return 0;
}