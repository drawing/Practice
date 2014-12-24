
/**
 * Hash Implement
 *
 * std::unordered_set
 * std::unordered_map
 * std::unordered_multiset
 * std::unordered_multimap
 *
 * template<
 * 	class Key,
 * 	class Hash = std::hash<Key>,
 * 	class KeyEqual = std::equal_to<Key>,
 * 	class Allocator = std::allocator<Key>
 * > class unordered_set;
 */

#include <unordered_set>
#include <iostream>

using namespace std;

int main()
{
	unordered_set<int> st;

	cout << st.max_load_factor() << endl;
	cout << st.load_factor() << endl;
	cout << st.bucket_count() << endl;
	cout << st.max_bucket_count() << endl;
	cout << st.max_load_factor() << endl;

	st.insert(2);
	st.insert({1, 2, 3, 5, 6});

	for (int i = 0; i < 47; i++) {
		st.insert(i);
	}

	cout << st.max_load_factor() << endl;
	cout << st.load_factor() << endl;
	cout << st.bucket_count() << endl;
	cout << st.max_bucket_count() << endl;
	cout << st.max_load_factor() << endl;

	cout << st.bucket_size(0) << endl;

	st.rehash(100); // real 103

	return 0;
}

