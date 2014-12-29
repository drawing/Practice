
#include <string>
#include <iostream>

using namespace std;

void send_msg(string msg, function<void(int)> succ) {
	succ(0);
}

int main()
{
	string msg = "test message";
	send_msg(msg, [=](int code) {
			cout << code << endl;
			cout << msg << endl;
			});
	return 0;
}

