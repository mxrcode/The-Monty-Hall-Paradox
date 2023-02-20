// This file is distributed as an optional file, it is not related to the main project and is compiled separately.

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>

using namespace std;

std::random_device rd;
mt19937_64 engine(rd());
uniform_int_distribution<int> rand_door(0, 2);

int main(int argc, char* argv[])
{

	cout << "# EXAMPLE: 3door_auto.exe NUMBER_OF_GAMES CHANGE_OF_MIND(SET false OR true) " << endl << endl;

	if (argc != 3) {
		cout << "Need more arguments!" << endl;
		return -1;
	}

	long number_of_games;
	try {
		number_of_games = stol(argv[1]);
	}
	catch (const invalid_argument& e) {
		cerr << "Error in arguments, NUMBER_OF_GAMES: " << argv[1] << endl;
		return 1;
	}

	bool change_of_mind;
	try {
		change_of_mind = (argv[2] == "true") ? true : false;
	}
	catch (const invalid_argument& e) {
		cerr << "Error in arguments, CHANGE_OF_MIND(SET false OR true):" << argv[2] << endl;
		return 1;
	}

	long games_count = 0;
	long wins_count = 0;

	vector<bool> door_list;

	for (long i = 0; i < number_of_games; i++) {

		door_list = { 0,0,0 };
		door_list[rand_door(engine)] = 1; // win_door

		int selected_door = rand_door(engine);

		int checked_door = 0;

		for (bool x = 1; x;)
		{
			int t = rand_door(engine);

			if (door_list[t] != 1 && t != selected_door) {
				checked_door = t;
				x = 0;
			}
		}

		games_count++;

		if (change_of_mind) {
			int untouched_door;
			for (int c = 0; c < door_list.size(); c++)
			{
				if (c != selected_door && c != checked_door) {
					untouched_door = c;
				}
			}

			if (door_list[untouched_door] == 1) {
				wins_count++;
			}
		}
		else {
			if (door_list[selected_door] == 1) {
				wins_count++;
			}
		}
	}

	cout << "change_of_mind:\t" << change_of_mind << endl;
	cout << "games_count:\t" << games_count << endl;
	cout << "wins_count:\t" << wins_count << endl;
	cout << "win_rate:\t% " << (wins_count / (double)games_count)*100.0 << endl;

	return 0;
}
