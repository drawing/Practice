#include <iostream>

using namespace std;

template<typename ... Types>
struct Tuple {};

template<typename ... Types>
int Size() {
	return sizeof...(Types);
}


void Print() {
}

template<typename T, typename ... Types>
void Print(T t, Types... other) {
	cout << t << endl;
	Print(other...);
}


template <typename ... Types> struct TestTuple{};
template <typename T, typename ... Types>
struct TestTuple<T, Types...> : public TestTuple<Types...>
{
	T value;
};

template <typename T>
struct TestTuple<T>
{
	T value;
};

int main()
{
	Tuple <int, char> t1;

	cout << Size<int, int, char>() << endl;

	Print(1, 2, 3, 10, 'a', "is string");

	TestTuple<int, string> t2;
	return 0;
}

