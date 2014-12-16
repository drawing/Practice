/**
 * https://oj.leetcode.com/problems/lru-cache/
 *
 *  Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
 *
 *  get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 *  set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
 *
 */

#include <map>
#include <iostream>

using namespace std;

class LRUCache {
public:
	LRUCache(int capacity) {
		_capacity = capacity;
		_seq = 0;
	}

	int get(int key) {
		if (_data.find(key) == _data.end()) {
			return -1;
		}

		int seq = _seq ++;
		Node node = _data[key];

		_access.erase(node.seq);
		node.seq = seq;

		_data[key] = node;
		_access[seq] = key;

		return node.val;
	}

	void set(int key, int value) {
		int seq = _seq ++;
		if (_data.find(key) == _data.end()) {

			if (_data.size() >= _capacity) {
				map<int, int>::iterator i = _access.begin();
				int dseq = i->first;
				int dkey = i->second;
				
				_data.erase(dkey);
				_access.erase(dseq);
			}

			Node node;
			node.val = value;
			node.seq = seq;

			_data[key] = node;
			_access[seq] = key;
		} else {
			Node node = _data[key];
			_access.erase(node.seq);

			node.val = value;
			node.seq = seq;
			_data[key] = node;
			_access[seq] = key;
		}
	}

private:
	int _capacity;
	int _seq;

	struct Node {
		int val;
		int seq;
	};

	map<int, Node> _data;
	map<int, int> _access;
};


int main()
{
	LRUCache cache(2);
	cache.set(2, 1);
	cache.set(1, 1);
	cout << cache.get(2) << endl;
	cache.set(4, 1);
	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;
	return 0;
}