/**
 * https://oj.leetcode.com/problems/valid-sudoku/
 *
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
 *
 * The Sudoku board could be partially filled, where empty cells are filled with the character '.'.
 *
 *
 * A partially filled sudoku which is valid.
 *
 * Note:
 * A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated. 
 */

class Solution {
public:
	bool isValidSudoku(vector<vector<char> > &board) {
		char checker[3][9][10] = {};
		enum {E_ROW, E_COL, E_CELL};

		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				char ch = board[i][j];
				if (ch == '.') {
					continue;
				}
				ch -= '0';
				int index = (i / 3) * 3 + (j / 3);

				if (checker[E_ROW][i][ch] == 1 ||
					checker[E_COL][j][ch] == 1 ||
					checker[E_CELL][index][ch] == 1) {
					return false;
				}

				checker[E_ROW][i][ch] = 1;
				checker[E_COL][j][ch] =1;
				checker[E_CELL][index][ch] = 1;
			}
		}

		return true;
	}
};

