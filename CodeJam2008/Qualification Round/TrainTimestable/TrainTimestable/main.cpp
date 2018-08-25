#include <iostream>
#include <set>
#include <string>

using namespace std;

enum Type {
	Arrival = 0,
	Departure = 1
};

enum Station {
	A,
	B
};

class Event
{
public:
	int time;
	Type type;
	Station station;

	Event(int time, Type type, Station station) {
		this->time = time;
		this->type = type;
		this->station = station;
	}

private:

};

int main() {
	int N;
	cin >> N;

	for (int t = 1; t <= N; t++) {
		int T;
		int NA, NB;
		cin >> T >> NA >> NB;

		struct event_compare {
			bool operator() (const Event& e1, const Event& e2) const {
				if (e1.time == e2.time) {
					return e1.type < e2.type;
				}
				return e1.time < e2.time;
			}
		};

		multiset<Event, event_compare> events;
	
		for (int i = 0; i < NA; i++) {
			string timeArrive, timeDeparture;
			cin >> timeArrive >> timeDeparture;
			
			int time = (timeArrive[0] - '0') * 10 + timeArrive[1] - '0';
			time *= 60;
			time = time + (timeArrive[3] - '0') * 10 + timeArrive[4] -'0';

			events.insert(Event(time, Departure, A));
			time = (timeDeparture[0] - '0') * 10 + timeDeparture[1] - '0';
			time *= 60;
			time = time + (timeDeparture[3] - '0') * 10 + timeDeparture[4] - '0';
			time += T;

			events.insert(Event(time, Arrival, B));
		}

		for (int i = 0; i < NB; i++) {
			string timeArrive, timeDeparture;
			cin >> timeArrive >> timeDeparture;

			int time = (timeArrive[0] - '0') * 10 + timeArrive[1] - '0';
			time *= 60;
			time = time + (timeArrive[3] - '0') * 10 + timeArrive[4] - '0';

			events.insert(Event(time, Departure, B));
			time = (timeDeparture[0] - '0') * 10 + timeDeparture[1] - '0';
			time *= 60;
			time = time + (timeDeparture[3] - '0') * 10 + timeDeparture[4] - '0';
			time += T;

			events.insert(Event(time, Arrival, A));
		}

		int ATrains = 0, BTrains = 0;
		int A_av = 0, B_av = 0;

		for (auto evnt = events.begin(); evnt != events.end(); evnt++) {
			if (evnt->station == A) {
				if (evnt->type == Arrival) {
					A_av++;
				}
				else {
					if (A_av > 0) A_av--;
					else ATrains++;
				}
			}
			else {
				if (evnt->type == Arrival) {
					B_av++;
				}
				else {
					if (B_av > 0) B_av--;
					else BTrains++;
				}
			}
		}

		cout << "Case #" << t << ": " << ATrains << " " << BTrains << endl;
	}

	return 0;
}