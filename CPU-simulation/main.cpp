#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const char* command[] = { "ADD", "SUB", "MUL", "DIV" };
enum COMMAND { ADD, SUB, MUL, DIV };

class HardwareException {
	string step;
	string msg;
public:
	HardwareException(string step = "", string msg = "");
	string getStep();
	string getMsg();
	void setMsg(string msg);
	void what(); // print step
};

class CPU {
	string instruction; // user input instruction
	int op1, op2; // operand
	string cmd; // instruction code (ADD SUB MUL DIV)
	void fetch() throw(HardwareException); // read commands from keyboard
	void decode() throw(HardwareException); // determine what the command code is
	void execute() throw(HardwareException); // execute commands according to command code
public:
	void run(); // CPU simulation, call fetch -> decode -> execute
	static int stringToInt(string x) throw(string);
};

void CPU::fetch() {
	getline(cin, this->instruction);

	if (this->instruction.empty())
		throw ("Fetch", "no command line");
}

void CPU::decode() {
	stringstream split(this->instruction);
	bool isExist = false;

	split >> this->cmd >> this->op1 >> this->op2;

	for (int i = 0; i < 4; i++) {
		if (!this->cmd.compare(*(command + i))) {
			isExist = true;
		}
	}

	if (!isExist) {
		throw ("decode", "invalid command line");
	}


}

void CPU::execute() {
	if (!this->cmd.compare("ADD")) { // 0 return if equal

	}
	else if (!this->cmd.compare("SUB")) {

	}
	else if (!this->cmd.compare("MUL")) {

	}
	else if (!this->cmd.compare("DIV")) {

	}
	else {
		throw "";
	}
}

void CPU::run() {
	this->fetch();
}

int CPU::stringToInt(string x) {

}

int main() {
	CPU computer;

	computer.run();

	return 0;
}