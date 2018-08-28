#include <iostream>
#include <string>

using namespace std;

int main() {
	char mapping[256] = {};
	mapping[32] = ' ';
	mapping[97] = 'y';
	mapping[98] = 'h';
	mapping[99] = 'e';
	mapping[100] = 's';
	mapping[101] = 'o';
	mapping[102] = 'c';
	mapping[103] = 'v';
	mapping[104] = 'x';
	mapping[105] = 'd';
	mapping[106] = 'u';
	mapping[107] = 'i';
	mapping[108] = 'g';
	mapping[109] = 'l';
	mapping[110] = 'b';
	mapping[111] = 'k';
	mapping[112] = 'r';
	mapping[113] = 'z';//
	mapping[114] = 't';
	mapping[115] = 'n';
	mapping[116] = 'w';
	mapping[117] = 'j';
	mapping[118] = 'p';
	mapping[119] = 'f';
	mapping[120] = 'm';
	mapping[121] = 'a';
	mapping[122] = 'q';

	/*string text = "de kr kd eoya kw aej tysr re ujdr lkgc jv";
	string textTranslated = "so it is okay if you want to just give up";

	for (int i = 0; i < text.size(); i++) {
		mapping[text[i]] = textTranslated[i];
	}

	for (int i = 0; i < 256; i++) {
		if (mapping[i] != 0) {
			cout << "mapping[" << i << "] = '" << mapping[i] << "';" << endl;
		}
	}*/

	int T;
	cin >> T;

	string dump;
	getline(cin, dump);

	for (int t = 1; t <= T; t++) {
		string G;
		getline(cin, G);

		for (int i = 0; i < G.size(); i++) {
			G[i] = mapping[G[i]];
		}

		cout << "Case #" << t << ": " << G << endl;
	}

	return 0;
}