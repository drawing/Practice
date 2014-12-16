
/**
 * https://oj.leetcode.com/problems/add-two-numbers/
 *
 * You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    	int carry_over = 0;
    	ListNode * head = NULL;
    	ListNode * tail = NULL;

    	while (l1 || l2) {
    		int left = 0;
    		int right = 0;
    		if (l1) {
    			left = l1->val;
    			l1 = l1->next;
    		}
    		if (l2) {
    			right = l2->val;
    			l2 = l2->next;
    		}

    		int total = left + right + carry_over;

    		carry_over = total / 10;
    		total %= 10;

    		ListNode * node = new ListNode(total);
    		if (head == NULL) {
    			head = node;
    			tail = head;
    		} else {
    			tail->next = node;
    			tail = tail->next;
    		}
    	}
    	if (carry_over != 0) {
    		ListNode * node = new ListNode(carry_over);
			tail->next = node;
			tail = tail->next;
    	}

    	return head;
    }
};
