/**
 * https://oj.leetcode.com/problems/maximum-gap/
 *
 * Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
 * Try to solve it in linear time/space.
 * Return 0 if the array contains less than 2 elements.
 * You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range.
 */

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	struct Cell {
		int min;
		int max;
		Cell():min(-1), max(-1) {}
	};

	int maximumGap(vector<int> &num) {
		if (num.size() < 2) {
			return 0;
		}
		int e_min = num[0];
		int e_max = num[0];

		for (size_t i = 1; i < num.size(); i++) {
			if (e_min > num[i]) {
				e_min = num[i];
			}
			if (e_max < num[i]) {
				e_max = num[i];
			}
		}
		double gap = double(e_max - e_min) / (num.size() + 1);
		vector<Cell> bucket(num.size() + 1);

		for (size_t i = 0; i < num.size(); i++) {
			int index = (num[i] - e_min) / gap;
			if (index == bucket.size()) {
				index = bucket.size() - 1;
			}

			if (bucket[index].min == -1) {
				bucket[index].min = num[i];
				bucket[index].max = num[i];
			} else {
				if (bucket[index].min > num[i]) {
					bucket[index].min = num[i];
				} else if (bucket[index].max < num[i]) {
					bucket[index].max = num[i];
				}
			}
		}

		int max_gap = 0;
		int last = bucket[0].max;
		for (int i = 1; i <= num.size(); i++) {
			if (bucket[i].min == -1) {
				continue;
			}
			if (bucket[i].min - last > max_gap) {
				max_gap = bucket[i].min - last;
			}
			last = bucket[i].max;
		}

		return max_gap;
	}
};

int main() {
	vector<int> input;
	input.push_back(1);
	input.push_back(10000000);
	cout << Solution().maximumGap(input) << endl;
	return 0;
}