#include <iostream>
#include <vector>
using namespace std;

void printBoard(vector<vector<int>> const &board);
int* findEmpty(vector<vector<int>> const &board);
bool valid(vector<vector<int>> const board, int num, int row, int col);
bool solve(vector<vector<int>> &board);

int main() {
	int choose;
	vector<vector<int>> board = {
		{7, 8, 0, 4, 0, 0, 1, 2, 0},
		{6, 0, 0, 0, 7, 5, 0, 0, 9},
		{0, 0, 0, 6, 0, 1, 0, 7, 8},
		{0, 0, 7, 0, 4, 0, 2, 6, 0},
		{0, 0, 1, 0, 5, 0, 9, 3, 0},
		{9, 0, 4, 0, 6, 0, 0, 0, 5},
		{0, 7, 0, 3, 0, 0, 0, 1, 2},
		{1, 2, 0, 0, 0, 7, 4, 0, 0},
		{0, 4, 9, 2, 0, 6, 0, 0, 7}
	};
	vector<vector<int>> preset1 = {
	{7, 8, 0, 4, 0, 0, 1, 2, 0},
	{6, 0, 0, 0, 7, 5, 0, 0, 9},
	{0, 0, 0, 6, 0, 1, 0, 7, 8},
	{0, 0, 7, 0, 4, 0, 2, 6, 0},
	{0, 0, 1, 0, 5, 0, 9, 3, 0},
	{9, 0, 4, 0, 6, 0, 0, 0, 5},
	{0, 7, 0, 3, 0, 0, 0, 1, 2},
	{1, 2, 0, 0, 0, 7, 4, 0, 0},
	{0, 4, 9, 2, 0, 6, 0, 0, 7}
	};
	vector<vector<int>> preset2 = {
	{0, 9, 0, 0, 3, 0, 1, 5, 0},
	{2, 1, 8, 7, 0, 5, 0, 0, 6},
	{0, 0, 0, 0, 0, 6, 0, 0, 4},
	{9, 0, 0, 0, 7, 8, 4, 0, 0},
	{1, 8, 5, 4, 2, 0, 7, 6, 0},
	{3, 7, 0, 0, 6, 0, 0, 2, 8},
	{0, 0, 1, 0, 0, 0, 0, 7, 0},
	{0, 0, 9, 0, 5, 7, 0, 0, 1},
	{8, 0, 7, 0, 0, 3, 0, 4, 0}
	};
	vector<vector<int>> preset3 = {
	{9, 0, 0, 8, 3, 0, 1, 5, 7},
	{5, 0, 3, 1, 0, 6, 2, 8, 0},
	{1, 0, 0, 7, 4, 0, 0, 9, 0},
	{0, 0, 0, 0, 5, 0, 8, 3, 0},
	{3, 0, 1, 0, 0, 4, 6, 7, 2},
	{2, 0, 0, 0, 1, 3, 0, 0, 9},
	{0, 0, 2, 0, 7, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 6, 0},
	{0, 3, 4, 0, 6, 0, 9, 2, 0}
	};

	while (true) {
		cout << endl;
		cout << "Please select: (If you select to solve a board without setting one, default board will be solved)." << endl;
		cout << "1. Set board" << endl;
		cout << "2. Solve board" << endl;
		cout << "0. Exit" << endl;
		cin >> choose;

		switch (choose) {
			case 1:
				cout << "Select a preset: " << endl;
				cout << "Preset 1:" << endl;
				printBoard(preset1);
				cout << endl;

				cout << "Preset 2:" << endl;
				printBoard(preset2);
				cout << endl;

				cout << "Preset 3:" << endl;
				printBoard(preset3);
				cout << endl;

				cout << endl;
				cout << "Please select a preset (1-3): (Any other input to go back to main menu)" << endl;
				cin >> choose;

				switch (choose) {
				case 1:
					board = preset1;
					break;
				case 2:
					board = preset2;
					break;
				case 3:
					board = preset3;
					break;
				}
				break;

			case 2:
				cout << "Solving..." << endl;

				solve(board);
				printBoard(board);
				break;
			case 0:
				exit(0);

			default:
				cout << "Invalid input. Please select a number between 1-3." << endl;
		}
	}
	return 0;
}

void printBoard(vector<vector<int>> const &board) {
	int i, j;

	for (i = 1; i <= board.size(); i++) {
		for (j = 1; j < board.at(i - 1).size(); j++) {
			cout << board[i - 1][j - 1] << "  ";

			if (j % 3 == 0) {
				cout << "|  ";
			}
		}
		cout << endl;
		if (i % 3 == 0) {
			cout << "- - - - - - - - - - - - - - -" << endl;
		}
	}
}

// find if spot is empty and if it is return it's coordinates as an array
int* findEmpty(vector<vector<int>> const &board) {
	int i, j;
	int emptyLocation[2] = {-1, -1};

	for (i = 0; i < board.size(); i++) {
		for (j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) {
				emptyLocation[0] = i;
				emptyLocation[1] = j;
				return emptyLocation;
			}
		}
	}
	return emptyLocation;
}

// check if a number is valid in specific coordinate (if there isn't the same number
// in the same row, column or 3x3 section)
bool valid(vector<vector<int>> const board, int num, int row, int col) {
	int i, j, temp;

	// check row
	for (i = 0; i < board.size(); i++) {
		if (board[i][col] == num && i != col) {
			return false;
		}
	}

	// check column
	for (i = 0; i < board.size(); i++) {
		if (board[row][i] == num && i != row) {
			return false;
		}
	}

	// get to the (0,0) of the section (top left corner)
	if (col % 3 != 0) {
		temp = col % 3;
		col = col - temp;
	}

	if (row % 3 != 0) {
		temp = row % 3;
		row = row - temp;
	}

	// check 3x3 section
	for (i = row; i < row + 3; i++) {
		for (j = col; j < col + 3; j++) {
			if (board[i][j] == num && i != row && j != col) {
				return false;
			}
		}
	}
	return true;
}

bool solve(vector<vector<int>> &board) {
	int *find = findEmpty(board);
	int row, col, i;
	
	if (find[0] == -1) {
		return true;
	}

	row = find[0];
	col = find[1];

	for (i = 1; i <= 9; i++) {
		if (valid(board, i, row, col)) {
			board[row][col] = i;

			if (solve(board)) {
				return true;
			}
			board[row][col] = 0;
		}
	}
	return false;

}