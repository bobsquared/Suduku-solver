#include <iostream>
#include <string>
#include <fstream>
#include "VOArray.h"
#include "POArray.h"
#include <ctime>

using namespace std;

typedef struct Coordinates {

	int width;
	int length;

};

bool addTrivial(int **, POArray<Coordinates> *);



int** initBoard(string filename) {


	ifstream myfile(filename);

	string s[9];
	int lineBoard[9][9];
	int index = 0, index2 = 0;
	if (myfile.is_open()){

	

		string line;
		while (getline(myfile, line)) {
			s[index] = line;
			index++;

		}
		myfile.close();
		

	}
	else {
		cout << "SHIT\n";
	}

	index = 0;
	for (int i = 0; i < 9; i++) {

		for (int k = 0; k < s[i].size(); k++) {

			if (isdigit(s[i][k]) != 0) {
				string c = "";
				c += s[i][k];
				lineBoard[index2][index] = stoi(c);
				index++;
			}

		}
	
	}
	

	
	int** board = new int*[9];

	for (int i = 0; i < 9; i++) {
		board[i] = new int[9];



		for (int k = 0; k < 9; k++) {
			//cout << lineBoard[i][k] << endl;
			board[i][k] = lineBoard[i][k];

		}
	}

	
	return board;

}

void deleteBoard(int** board) {


	for (int i = 0; i < 9; i++) {
		delete[] board[i];
	}

	delete[] board;


}

void printBoard(int** board) {

	for (int i = 0; i < 9; i++) {

		for (int k = 0; k < 9; k++) {
			cout << board[i][k] << " ";
			if (k % 3 == 2) {
				cout << " ";
			}
		}
		cout << endl;
		if (i % 3 == 2) {
			cout << endl;
		}

	}

}

VOArray<int>* quadrantCheck(int **board, int width, int height) {

	int h, w;
	int ret = 1, count = 9;

	if (height < 3 && width < 3) {
		h = 0;
		w = 0;
	}

	else if (height < 3 && width < 6) {
		h = 0;
		w = 3;
	}

	else if (height < 3 && width < 9) {
		h = 0;
		w = 6;
	}

	else if (height < 6 && width < 3) {
		h = 3;
		w = 0;
	}

	else if (height < 6 && width < 6) {
		h = 3;
		w = 3;
	}

	else if (height < 6 && width < 9) {
		h = 3;
		w = 6;
	}

	else if (height < 9 && width < 3) {
		h = 6;
		w = 0;
	}

	else if (height < 9 && width < 6) {
		h = 6;
		w = 3;
	}

	else if (height < 9 && width < 9) {
		h = 6;
		w = 6;
	}

	VOArray<int> *numLeft = new VOArray<int>;
	for (int i = h; i < h + 3; i++) {

		for (int k = w; k < w + 3; k++) {

			if (board[i][k] != 0) {

				try {
					numLeft->Search(board[i][k]);
		
				}
				catch(const char*e){
					numLeft->Insert(board[i][k]);
				}
					
			
			}
		}
	}

	return numLeft;

}






void print(int i) {

	cout << i << endl;

}




VOArray<int>* checkSquare(int **board, int width, int height) {

	VOArray<int>* qc = quadrantCheck(board, width, height);

	for (int i = 0; i < 9; i++) {


		if (board[i][width] != 0) {

			try {
				int pp = qc->Search(board[i][width]);
			}
			catch (const char*e) {
				qc->Insert(board[i][width]);
			}

		}


		if (board[height][i] != 0) {

			try {
				qc->Search(board[height][i]);
			}
			catch (const char*e) {
				qc->Insert(board[height][i]);
			}

		}
	}

	return qc;

}

int countNumber(int **board, int number) {

	int ret = 0;

	for (int i = 0; i < 9; i++) {

		for (int k = 0; k < 9; k++) {

			if (board[i][k] == number) {
				ret++;
			}

		}
	}

	return ret;

}


int factsCheck(int **board, int x, int y, Coordinates *temp, int index, Coordinates *ret, int number) {

	for (int i = x; i < x + 3; i++) {

		for (int k = y; k < y + 3; k++) {

			if (board[i][k] == number) {
				return 0;
			}

		}

	}


	int count = 0;

	int hw[3][3];

	int indexh = 0;
	int indexw = 0;

	for (int i = 0; i < 3; i++) {

		for (int k = 0; k < 3; k++) {

			if (board[i + x][k + y] == 0) {
				hw[i][k] = 0;
			}
			else {
				hw[i][k] = 1;
			}
		}
	}

	for (int i = 0; i < 3; i++) {

		for (int k = 0; k < 3; k++) {

			if (hw[i][k] == 0) {

				for (int l = 0; l < index; l++) {

					if (temp[l].width == k + y || temp[l].length == i + x) {
						hw[i][k] = 1;
					}
					
				}	

			}

		}

	}

	for (int i = 0; i < 3; i++) {

		for (int k = 0; k < 3; k++) {

			if (hw[i][k] == 0) {
				count++;
				ret->length = i + x;
				ret->width = k + y;
			}
		}
	}

	

	return count;

}

bool checkColumn(int **board, POArray<Coordinates> *reta, int col) {

	VOArray<int> vals = VOArray<int>();
	Coordinates coo;
	bool check = false;

	int count = 0;

	for (int k = 0; k < 9; k++) {

		if (board[col][k] == 0) {
			count++;
			coo.length = col;
			coo.width = k;
		}
		else {
			vals.Insert(board[col][k]);
		}

	}


	if (count == 1) {

		for (int k = 1; k < 10; k++) {

			try {
				vals.Search(k);
			}
			catch (const char*e) {

				if (board[coo.length][coo.width] == 0) {
					check = true;
				}



			}
			if (check) {
				board[coo.length][coo.width] = k;
				reta->Insert(coo);
				break;
			}

		}

	}

	return check;
}

bool checkRow(int **board, POArray<Coordinates> *reta, int row) {

	VOArray<int> vals = VOArray<int>();
	Coordinates coo;
	bool check = false;

	int count = 0;

	for (int k = 0; k < 9; k++) {

		if (board[k][row] == 0) {
			count++;
			coo.length = k;
			coo.width = row;
		}
		else {
			vals.Insert(board[k][row]);
		}

	}


	if (count == 1) {

		for (int k = 1; k < 10; k++) {

			try {
				vals.Search(k);
			}
			catch (const char*e) {

				if (board[coo.length][coo.width] == 0) {
					check = true;
				}



			}
			if (check) {
				board[coo.length][coo.width] = k;
				reta->Insert(coo);
				break;
			}

		}

	}

	return check;
}


bool addFacts(int **board, POArray<Coordinates> *reta) {

	bool check = false;
	for (int x = 1; x < 10; x++) {

		Coordinates *temp = new Coordinates[9];
		int index = 0;
		int count = 0;

		for (int i = 0; i < 9; i++) {

			for (int k = 0; k < 9; k++) {

				if (board[i][k] == x) {
					Coordinates c;
					c.width = k;
					c.length = i;
					temp[index] = c;
					index++;
				}

			}

		}

		int q[9];
		Coordinates ret[9];


		q[0] = factsCheck(board, 0, 0, temp, index, &ret[0], x);
		q[1] = factsCheck(board, 0, 3, temp, index, &ret[1], x);
		q[2] = factsCheck(board, 0, 6, temp, index, &ret[2], x);
		q[3] = factsCheck(board, 3, 0, temp, index, &ret[3], x);
		q[4] = factsCheck(board, 3, 3, temp, index, &ret[4], x);
		q[5] = factsCheck(board, 3, 6, temp, index, &ret[5], x);
		q[6] = factsCheck(board, 6, 0, temp, index, &ret[6], x);
		q[7] = factsCheck(board, 6, 3, temp, index, &ret[7], x);
		q[8] = factsCheck(board, 6, 6, temp, index, &ret[8], x);

		for (int i = 0; i < 9; i++) {

			if (q[i] == 1) {
				board[ret[i].length][ret[i].width] = x;
				reta->Insert(ret[i]);
				check = true;
			}

		}

		delete[] temp;


	}

	
	if (check) {
		check = addFacts(board, reta);
		check = addTrivial(board, reta);
	}

	return check;


}

bool addTrivial(int **board, POArray<Coordinates> *reta) {

	bool check;
	for (int i = 0; i < 9; i++) {

		bool check2 = false;
		check = checkColumn(board, reta, i);

		if (check2) {
			check = true;
		}

	}

	for (int i = 0; i < 9; i++) {

		bool check2 = false;
		check = checkRow(board, reta, i);

		if (check2) {
			check = true;
		}

	}

	if (check) {
		check = addTrivial(board, reta);
		check = addFacts(board, reta);
	}

	return check;

}

bool checkTable(int **board) {


	for (int i = 0; i < 9; i++) {

		VOArray<int> vals = VOArray<int>();

		for (int k = 0; k < 9; k++) {

			if (board[i][k] != 0) {

				try {
					vals.Search(board[i][k]);
					return false;
				}
				catch (const char*e) {
					vals.Insert(board[i][k]);
				}

			}

		}

	}

	for (int i = 0; i < 9; i++) {

		VOArray<int> vals = VOArray<int>();

		for (int k = 0; k < 9; k++) {

			if (board[k][i] != 0) {

				try {
					vals.Search(board[k][i]);
					return false;
				}
				catch (const char*e) {
					vals.Insert(board[k][i]);
				}

			}

		}

	}

	return true;
}


bool dfs(int **board, int *count) {

	*count += 1;
	int max = -1;

	VOArray<int> *retVO = new VOArray<int>;
	POArray<Coordinates> *coordinate = new POArray<Coordinates>;

	bool ret = false;
	int width;
	int height;

	//Add trivial solutions so that searching would be easier


	bool check = addFacts(board, coordinate);
	bool checkC = addTrivial(board, coordinate);


	if (checkTable(board)) {

		for (int i = 0; i < 9; i++) {

			for (int k = 0; k < 9; k++) {


				if (board[i][k] == 0) {
					VOArray<int>* retVO2 = checkSquare(board, k, i);
					if (retVO2->ElementCount() > max) {
						max = retVO2->ElementCount();
						retVO = retVO2;
						width = k;
						height = i;
					}

				}

			}
		}

		if (max == -1) {
			return true;
		}

		if (retVO->ElementCount() != 9) {

			for (int k = 1; k < 10; k++) {


				int max2 = 0;
				int index = 0;

				for (int i = 1; i < 10; i++) {

					try {
						retVO->Search(i);
					}
					catch (const char*e) {

						int c = countNumber(board, i);

						if (c > max2) {
							index = i;
						}

					}
				}

				if (retVO->ElementCount() == 9) {
					break;
				}

				board[height][width] = index;
				ret = dfs(board, count);
				retVO->Insert(index);

				if (ret) {
					break;
				}
				else {
					board[height][width] = 0;
				}
			}


		}
	}

	if (!check && !ret) {
		for (int i = 0; i < coordinate->ElementCount(); i++) {
			Coordinates *fin = coordinate->Search(i);
			board[fin->length][fin->width] = 0;

		}
	}

	delete retVO;
	delete coordinate;

	return ret;

}



int main() {

	int** board = initBoard("test.txt");
	int count = 0;
	printBoard(board);

	cout << "---------------------------------------------------" << endl;
	clock_t start;
	start = clock();
	dfs(board, &count);
	clock_t endc;
	endc = clock();
	cout << "---------------------------------------------------" << endl;
	printBoard(board);
	cout << endl << "Time: " << (endc - start) / (double)(CLOCKS_PER_SEC) << "s ---- count: " << count  << endl;

	deleteBoard(board);





	//TERMINATE
	string endString;
	bool end = false;
	while (!end) {
		cout << "Type anything and press enter to terminate: ";
		cin >> endString;
		end = true;
	}

	return 0;
}