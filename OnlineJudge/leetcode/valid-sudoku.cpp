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

struct Checker {
	int c[10];
	Checker() {memset(c, 0, 10 * sizeof(int));}
};

class Solution {
public:
	bool isValidSudoku(vector<vector<char> > &board) {
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
				if (col[i].c[ch] == 1) {
					return false;
				}
				if (row[j].c[ch] == 1) {
					return false;
				}

				int index = (i / 3) * 3 + (j / 3);
				if (cel[index].c[ch] == 1) {
					return false;
				}

				col[i].c[ch] = 1;
				row[j].c[ch] = 1;
				cel[index].c[ch] = 1;
			}
		}

		return true;
	}
};

