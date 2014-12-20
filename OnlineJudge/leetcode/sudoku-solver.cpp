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

class Solution {
public:
	char checker[3][9][10];
	enum {E_ROW, E_COL, E_CELL};

	bool solveSudoku(vector<vector<char> > &board, int in_i, int in_j)
	{
		if (in_i == board.size() - 1 && in_j >= board[0].size()) {
			return true;
		}

		for (int i = in_i; i < board.size(); i++) {
			int j_begin = (i == in_i) ? in_j : 0;

			for (int j = j_begin; j < board[i].size(); j++) {
				char ch = board[i][j];
				if (ch != '.') {
					continue;
				}

				int index = (i / 3) * 3 + (j / 3);

				for (int k = 1; k < 10; k++) {
					if (checker[E_ROW][i][k] == 0 &&
						checker[E_COL][j][k] == 0 &&
						checker[E_CELL][index][k] == 0)
					{
						board[i][j] = '0' + k;
						checker[E_ROW][i][k] = 1;
						checker[E_COL][j][k] = 1;
						checker[E_CELL][index][k] = 1;
						bool ret = solveSudoku(board, i, j+1);
						if (ret) {
							return true;
						}
						board[i][j] = '.';
						checker[E_ROW][i][k] = 0;
						checker[E_COL][j][k] = 0;
						checker[E_CELL][index][k] = 0;
					}
				}
				return false;
			}
		}

		return true;
	}

	void solveSudoku(vector<vector<char> > &board) {
		memset(checker, 0, sizeof(checker));
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				char ch = board[i][j];
				if (ch == '.') {
					continue;
				}
				ch -= '0';
				int index = (i / 3) * 3 + (j / 3);

				checker[E_ROW][i][ch] = 1;
				checker[E_COL][j][ch] =1;
				checker[E_CELL][index][ch] = 1;
			}
		}

		solveSudoku(board, 0, 0);
	}
};

