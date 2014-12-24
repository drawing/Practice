
#include <iostream>
#include <vector>

using namespace std;

class Elem {
public:
	Elem(const char * name) : name(strdup(name)) {
		cout << "Create One Elem: " << name << endl;
	}
	Elem(const Elem & other) {
		free(name);
		name = strdup(other.name);
		cout << "Create Elem By Other: " << name << endl;
	}
	Elem(Elem && rf) {
		free(name);
		name = rf.name;
		rf.name = nullptr;
		cout << "Create Elem By R-Refer: " << name << endl;
	}
public:
	char * name;
};

bool is_right_reference(Elem & elem)
{
	return false;
}
bool is_right_reference(Elem && elem)
{
	return true;
}

int main()
{
	string one = "TestOne String";
	string two = std::move(one);

	cout << "One:" << one << endl;
	cout << "Two:" << two << endl;

	Elem elem("one");
	cout << is_right_reference(Elem("temp")) << endl;
	cout << is_right_reference(elem) << endl;
	cout << is_right_reference(std::move(elem)) << endl;

	Elem elem1 = elem;
	Elem elem2 = std::move(elem);

	cout << (long)elem.name << endl;
	return 0;
}

