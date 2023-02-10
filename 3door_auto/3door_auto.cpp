#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>

using namespace std;

mt19937_64 engine(time(nullptr));

int main(int argc, char* argv[])
{

	cout << "# EXAMPLE: 3door_auto.exe NUMBER_OF_GAMES CHANGE_OF_MIND(SET false OR true) " << endl << endl;

	if (argc != 3) {
		cout << "Need more arguments!" << endl;
		return -1;
	}

	istringstream iss_com(argv[1]);
	long number_of_games;
	if (!(iss_com >> number_of_games)) {
		cerr << "Error in arguments, NUMBER_OF_GAMES: " << argv[1] << endl;
		return 1;
	}

	stringstream ss_nog(argv[2]);
	bool change_of_mind;
	if (!(ss_nog >> boolalpha >> change_of_mind)) {
		cerr << "Error in arguments: CHANGE_OF_MIND(SET false OR true)" << endl;
		return 1;
	}

	long games_count = 0;
	long wins_count = 0;

	vector<bool> door_list;

	for (long i = 0; i < number_of_games; i++) {
		door_list = { 0,0,0 };

		uniform_int_distribution<int> win_door(0, 2);
		door_list[win_door(engine)] = 1;

		uniform_int_distribution<int> t_selected_door(0, 2);
		int selected_door = t_selected_door(engine);

		int checked_door = 0;

		for (bool x = 1; x;)
		{
			uniform_int_distribution<int> t_checked_door(0, 2);
			int t = t_checked_door(engine);

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