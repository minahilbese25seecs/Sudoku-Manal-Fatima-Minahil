#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
void solved();
bool box_check(int[][9], int, int, int, int);
bool rows_check(int[][9], int, int, int, int);
bool column_check(int[][9], int, int, int, int);
void display(int[][9], int);
void add(int[][9], int, int, int);
bool checker(int[][9], int, int, int, int);
bool board_result(int sudoku[][9], int size);
void generate(int sudoku[][9], int size, int verified_sudoku[][9]);
void clues(int no_of_clues, int[][9]);
bool win(int[][9]);
bool userfilled[9][9] = { 0 };

int main() {
	srand(time(0));
	int choice = 1, row_d, column_d, remove;
	int row, column, value, points = 100;
	int sudoku[9][9] = {};
	string difficulty;
	int verified_sudoku[9][9] = {}; //sudoku is the solved one and verified_sudoku is the one checked if it can be solved and then has 0s and 1s
	//this 25 can be changed
	generate(sudoku, 9, verified_sudoku); // generates 0-9 every box randomlythen calls the board_result function to see if can be solved has recursion 
	//just displays the board
	cout << "\033[33m~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~:) WELCOME TO SUDOKU ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ \033[0m" << endl;
	cout << "Please Choose Your Difficulty Level... (\033[32measy\033[0m/\033[34mmedium\033[0m/\033[31mhard\033[0m)" << endl;
	cin >> difficulty;
	if (difficulty == "hard") {
		clues(15, verified_sudoku);
	}
	else if (difficulty == "easy") {
		clues(30, verified_sudoku);
	}
	else {
		clues(20, verified_sudoku);
	}
	cout << "On each wrong try, You Lose \033[31m10 Points\033[0m...\nIf your points reach 0, You \033[31mF A I L\033[0m." << endl;

	display(verified_sudoku, 9);

	while (choice == 1) {
		cout << "\033[35mPoints: \033[0m" <<"\033[35m"<< points<<"\033[0m" << endl;
		cout << "Enter the value you want to add and at which position." << endl;
		cout << "Value:";
		cin >> value;
		cout << "Row:";
		cin >> row;
		cout << "Column:";
		cin >> column;
		if (verified_sudoku[row][column] != 0) {
			cout << "This is a fixed value! You cannot change it.." << endl;
			continue;
		}
		if (checker(verified_sudoku, 9, value, row, column)) { //checker checks if in original solved sudoku and add adds to verified_sudoku that has 0s and 1s
			cout << "Input successful." << endl;
			add(verified_sudoku, row, column, value);
			display(verified_sudoku, 9);
			if (win(verified_sudoku)) {
				cout << "\n CONGRATULATIONS! YOU COMPLETED THE SUDOKU! \n";
				cout << "\033[35mTotal Score: \033[0m" <<"\033[35m"<< points<<"\033[0m" << endl;
				cout << "\033[33m===================== YOU WIN! ========================\033[0m" << endl;
				return 0;
			}

		}
		else {  // can there be if and else but theres another if thats not related with the inital one 
			cout << "\033[31mWrong!\033[0m" << endl;
			points -= 10;
			cout << "\033[35mPoints = \033[0m" <<"\033[35m"<< points<<"\033[0m" << endl;
			if (points <= 0) { // if points less or equal to 0 then quit
				cout << "\033[31mYou lost.\033[0m\nBetter luck next time!\n" << endl;
				cout << "\033[33m===================== Thank you for playing! ========================\033[0m";
				return 0;
			}
		}
		cout << "Do you want to remove a number at a certain position? (1 for yes/ 0 for no)" << endl;
		cin >> remove;
		if (remove == 1) {
			cout << "Enter row and column of the position." << endl;
			cin >> row_d >> column_d;
			verified_sudoku[row_d][column_d] = 0;
			cout << "\033[31mEntry removed!\033[0m" << endl;
			points -= 5;
		}
		cout << "Do you wish to continue? (press 1 for yes)" << endl;
		cin >> choice;
		if (choice != 1) {
			points -= 20;
		}
	}
	cout << "\033[32mCorrect solution was:\033[0m" << endl;
	display(sudoku, 9);
	cout << "\033[35mTotal Score: \033[0m" <<"\033[35m"<< points<<"\033[0m" << endl;
	cout << "\033[33m===================== Thank you for playing! ========================\033[0m" << endl;
}

bool rows_check(int sudoku[][9], int size, int value, int row, int column) {
	for (int i = 0; i < size; i++) {
		if (value == sudoku[row][i]) {
			//cout<<value<<" already exists in the row"<<endl;
			return false;
		}
	}
	return true;
}

bool column_check(int sudoku[][9], int size, int value, int row, int column) {
	for (int i = 0; i < size; i++) {
		if (value == sudoku[i][column]) {
			//	cout<<value<<"already exists in the column"<<endl;
			return false;
		}
	}
	return true;
}

bool box_check(int sudoku[][9], int size, int value, int row, int column) {
	int origin_row = (row / 3) * 3;
	int origin_column = (column / 3) * 3;

	for (int i = origin_row; i < origin_row + 3; i++) {
		for (int j = origin_column; j < origin_column + 3; j++) {  // it was first/3 so it would always stop at wrong 
			if (value == sudoku[i][j]) {
				//		cout<<value<<" already exists in 3x3 box"<<endl;
				return false;
			}
		}
	}
	return true;
}


bool checker(int sudoku[][9], int size, int value, int row, int column) {
	return box_check(sudoku, 9, value, row, column) && rows_check(sudoku, 9, value, row, column) && column_check(sudoku, 9, value, row, column);
}

void display(int sudoku[][9], int size) {
	cout << "\033[36mColumn#\033[0m ";
	for (int i = 0; i < 9; i++) {
		if ((i + 1) % 3 == 0)
			cout <<"\033[36m"<< i<<"\033[0m"<< "   ";
		else
			cout <<"\033[36m"<< i<<"\033[0m" << "  ";
	}
	cout << endl;
	cout << "\033[36m       -----------------------------\033[0m";
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << "\033[36mRow#\033[0m" <<"\033[36m"<< i<<"\033[36m" << "\033[36m  |\033[0m";
		for (int j = 0; j < size; j++) {
			if (j == size - 1) {
				if (userfilled[i][j] == true) {
					cout << "\033[32m" << sudoku[i][j] << "\033[0m";
				}
				else {
					cout << "\033[31m" << sudoku[i][j] << "\033[0m";
				}
			}
				
			else {
				if (userfilled[i][j] == true) {
					cout <<"\033[32m"<<sudoku[i][j]<<"\033[0m"<< "  ";
				}
				else {
					cout << "\033[31m" << sudoku[i][j] << "\033[0m" << "  ";
				}
			}
			if ((j + 1) % 3 == 0)
				cout << "\033[36m|\033[0m";
		}
		if ((i + 1) % 3 == 0) {
			cout << endl;
			cout << "\033[36m       -----------------------------\033[0m";
		}
		cout << endl;
	}
}

void add(int verified_sudoku[][9], int row, int column, int value) {
	verified_sudoku[row][column] = value;
	userfilled[row][column] = true;
}


bool board_result(int sudoku[][9], int size) {  //recursive backtracking solver to solve sudoku
	//finds empty cell and places digits checks validity
	for (int row = 0; row < size; row++) {
		for (int column = 0; column < size; column++) {
			if (sudoku[row][column] == 0) {
				for (int number = 1; number <= size; number++) {
					if (checker(sudoku, 9, number, row, column)) {
						//	verified_sudoku[row][column]=sudoku[row][column];    //to store the solvable solution before it solves itself
						sudoku[row][column] = number;
						if (board_result(sudoku, 9)) {
							return true;
						}
						//else {    not needed since it already is 0
						//above this is true to if all true then it will break and return true
						sudoku[row][column] = 0;
						//}
					}
				}
				return false;
			}
		}
	}
	return true;
}
void generate(int sudoku[][9], int size, int verified_sudoku[][9]) {
	//board_result(sudoku,9, verified_sudoku);  // solves 
	for (int row = 0; row < size; row++) {
		for (int column = 0; column < size; column++) {
			//this is for all vlaues restarting to 0
			sudoku[row][column] = 0;
			verified_sudoku[row][column] = 0;
		}
	}
	board_result(sudoku, 9);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			verified_sudoku[i][j] = sudoku[i][j];
		}
	}

}

void clues(int no_of_clues, int sudoku[][9]) {
	int empty = 81 - no_of_clues;
	int row, column;
	for (int i = 0; i < empty; i++) {
		row = rand() % 9;
		column = rand() % 9;
		if (sudoku[row][column] != 0) {
			sudoku[row][column] = 0;
		}
	}
}
bool win(int board[][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == 0)
				return false;
		}
	}
	return true;
}