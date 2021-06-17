
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;
void create(int& n, int nColors, vector <vector <int>>& kartka);
void show(int n, vector <vector <int>>& kartka);
void Solve(int n, int nColors, vector <vector <int>>& kartka, vector <int>& chosencolors, int checkedSize, bool& solved);
bool check(int given, vector <int>& chosencolors);
void changeColors(int n, int& nColors, vector <int>& chosencolors, vector <vector <int>>& kartka);
int main() {

	bool solved = false;
	int n = 0;
	int nColors = 0;
	vector<int> chosencolors; //  list of chosen colors
	chosencolors.resize(0);
	int choice = 0;

	vector <vector <int>> kartka; // creating kartka
	kartka.resize(1);
	kartka[0].resize(1);


	int option = 0;

	while (option != 6) {
		cout << "1)Create new kartka\n2)Show kartka\n3)Solve\n4)Change Colors options\n5)Show chosen colors\n6)Exit\n";
		cin >> option;


		switch (option) {
		case 1:
			create(n, nColors, kartka);
			break;
		case 2:
			show(n, kartka);
			break;
		case 3:
			for (int i = kartka.size(); i > 0; i--) {
				Solve(n, nColors, kartka, chosencolors, i, solved);
				if (solved) break;
			}
			break;
		case 4:
			changeColors(n, nColors, chosencolors, kartka);
			break;
		case 5:
			cout << "CHOSEN COLORS ARE:\n";
			for (int i = 0; i < chosencolors.size(); i++) {
				cout << chosencolors[i] << "  ";
			}
			cout << endl;
			break;
		default:
			cout << "Wrong option!" << endl;
			break;
		}
	}

	return 0;
}

void create(int& n, int nColors, vector <vector <int>>& kartka) {
	if (nColors == 0) { cout << "No colors chosen! Can't create kartka" << endl; return; }
	int choice = 0;
	cout << "Do you want to change the size of kartka?" << endl;
	cin >> choice;

	if (choice > 0) {
		n = choice;
		kartka.resize(choice);
		for (int i = 0; i < choice; i++) {
			kartka[i].resize(choice);
		}
	}
	srand(5);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			kartka[i][k] = rand() % nColors;
		}
	}
}
void show(int n, vector <vector <int>>& kartka) {
	if (n < 1) { cout << "Kartka is not created yet" << endl; return; }
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			cout << kartka[i][k] << " ";
		}
		cout << endl;
	}
}
void Solve(int n, int nColors, vector <vector <int>>& kartka, vector <int>& chosencolors, int checkedSize, bool& solved) {
	if (checkedSize == 1) {
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {
				if (check(kartka[k][i], chosencolors)) cout << "GOOD SQUARE!!! SIZE: " << checkedSize << "   " << k << " and " << i << endl;

			}
		}
	}
	else {
		int shiftx = 0, shifty = 0;

		bool good = true;
		for (int i = 0; i < n - checkedSize + 1; i++) {
			for (int k = 0; k < n - checkedSize + 1; k++) {
				good = true;
				shiftx = 0, shifty = 0;


				do {
					good = check(kartka[k + shiftx][i + shifty], chosencolors);
					shiftx++;
				} while (shiftx != checkedSize && good);
				shiftx--;
				shifty++;
				if (good) do {
					good = check(kartka[k + shiftx][i + shifty], chosencolors);
					shifty++;
				} while (shifty != checkedSize && good);

				shiftx = 0, shifty = 0;
				shifty++;

				if (good)  do {
					good = check(kartka[k + shiftx][i + shifty], chosencolors);
					shifty++;
				} while (shifty != checkedSize && good);

				shifty--;
				if (good)  do {
					good = check(kartka[k + shiftx][i + shifty], chosencolors);
					shiftx++;
				} while (shiftx != checkedSize && good);


				if (good) { cout << "GOOD SQUARE!!! SIZE: " << checkedSize << "   " << k << " and " << i << endl; solved = true; }
			}
		}
	}
}
bool check(int given, vector <int>& chosencolors) {
	bool curr = false;
	for (int i = 0; i < chosencolors.size(); i++) {
		if (chosencolors[i] == given) {
			curr = true;
		}
	}
	if (curr == false) return false; else return true;
}
void changeColors(int n, int& nColors, vector <int>& chosencolors, vector <vector <int>>& kartka) {
	int choice = 0;
	cout << "How many colors do you want to be on kartka? Enter 0 if you do not want to change current number" << endl;
	cin >> choice;

	if (choice > 0) {
		nColors = choice;
		srand(time(NULL));
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {
				kartka[i][k] = rand() % nColors;
			}
		}
	}
	cout << "Do you want to change  chosen  colors? Enter 0 if no, Enter 1 if yes" << endl;
	cin >> choice;
	if (choice) {
		chosencolors.resize(0);
		cout << "Max number of colors - " << nColors << endl;
		while (choice != -1 && chosencolors.size() != nColors) {

			cout << "Choose color" << endl;
			cin >> choice;
			if (choice == -1)break;
			bool repeat = false;

			for (int i = 0; i < chosencolors.size(); i++) {
				if (chosencolors[i] == choice) repeat = true;
			}
			if (repeat == true) cout << "This color was chosen before" << endl;
			else chosencolors.push_back(choice);
		}
	}


}
//Some changes in code were made