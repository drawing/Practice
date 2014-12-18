/**
 * https://oj.leetcode.com/problems/merge-sorted-array/
 *
 * Given two sorted integer arrays A and B, merge B into A as one sorted array.
 *
 * Note:
 * You may assume that A has enough space (size that is greater or equal to m + n) to hold additional elements from B. The number of elements initialized in A and B are m and n respectively.
 *
 */

#include <string.h>

class Solution {
public:
	void merge(int A[], int m, int B[], int n) {
		memmove(A + n, A, m * sizeof(int));
		int i = n;
		int j = 0;
		int index = 0;
		while (i < m+n || j < n) {
			bool first = true;
			if (i >= m+n) {
				first = false;
			} else if (j < n) {
				if (A[i] > B[j]) {
					first = false;
				}
			}
			if (first) {
				A[index++] = A[i++];
			} else {
				A[index++] = B[j++];
			}
		}
	}
};
