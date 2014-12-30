/**
 * https://oj.leetcode.com/problems/rotate-list/
 *
 * Given a list, rotate the list to the right by k places, where k is non-negative.
 *
 * For example:
 * Given 1->2->3->4->5->NULL and k = 2,
 * return 4->5->1->2->3->NULL.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
    	int num = 0;
    	ListNode ** mm = &head;
    	while (*mm) {
    		mm = &(*mm)->next;
    		num ++;
    	}
    	if (num == 0) {
    		return head;
    	}

    	k %= num;

    	int skip = num - k;

    	ListNode ** node = &head;
    	for (int i = 0; i < skip; i++) {
    		node = &(*node)->next;
    	}

    	*mm = head;
    	head = *node;
    	*node = NULL;
    	return head;
    }
};

