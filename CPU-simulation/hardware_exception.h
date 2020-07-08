#include <iostream>
#include <string>

using namespace std;

class HardwareException { // exception class with step, msg what it is;
	string step;
	string msg;
public:
	HardwareException(string step = "", string msg = "") {
		this->step = step;
		this->msg = msg;
	}
	void what() { // print step
		cout << this->step << " step, " << this->msg << endl;
		exit(0);
	}
};