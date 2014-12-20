/**
 * https://oj.leetcode.com/problems/sudoku-solver/
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * Empty cells are indicated by the character '.'.
 *
 * You may assume that there will be only one unique solution. 
 *
 */

struct Checker {
	int c[10];
	Checker() {memset(c, 0, 10 * sizeof(int));}
};

class Solution {
public:
	bool solveSudoku(vector<vector<char> > &board,
		vector<Checker> & col,
		vector<Checker> & row,
		vector<Checker> & cel,
		int in_i, int in_j) {

		if (in_i == board.size() - 1 && in_j >= board[0].size()) {
			return true;
		}

		for (int i = in_i; i < board.size(); i++) {
			int j_begin = 0;
			if (i == in_i) {
				j_begin = in_j;
			}
			for (int j = j_begin; j < board[i].size(); j++) {
				char ch = board[i][j];
				if (ch != '.') {
					continue;
				}
				Checker check;
				for (int k = 1; k < 10; k++) {
					if (row[i].c[k] == 1) {
						check.c[k] = 1;
					}
				}
				for (int k = 1; k < 10; k++) {
					if (col[j].c[k] == 1) {
						check.c[k] = 1;
					}
				}
				int index = (i / 3) * 3 + (j / 3);
				for (int k = 1; k < 10; k++) {
					if (cel[index].c[k] == 1) {
						check.c[k] = 1;
					}
				}

				for (int k = 1; k < 10; k++) {
					if (check.c[k] == 0) {
						board[i][j] = '0' + k;
						row[i].c[k] = 1;
						col[j].c[k] = 1;
						cel[index].c[k] = 1;
						bool ret = solveSudoku(board, col, row, cel, i, j+1);
						if (ret) {
							return true;
						}
						board[i][j] = '.';
						row[i].c[k] = 0;
						col[j].c[k] = 0;
						cel[index].c[k] = 0;
					}
				}
				return false;
			}
		}

		return true;
	}

	void solveSudoku(vector<vector<char> > &board) {
		vector<Checker> col(9);
		vector<Checker> row(9);
		vector<Checker> cel(9);

		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				char ch = board[i][j];
				if (ch == '.') {
					continue;
				}
				ch -= '0';
				row[i].c[ch] = 1;
				col[j].c[ch] = 1;

				int index = (i / 3) * 3 + (j / 3);
				cel[index].c[ch] = 1;
			}
		}

		solveSudoku(board, col, row, cel, 0, 0);
	}
};

